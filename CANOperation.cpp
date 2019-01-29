#include <unistd.h>
#include <QMessageBox>
#include "cansqlsettingwidget.h"

extern bool g_CanConnectionFlag;

void CANSQLSettingWidget::OnConncetCAN()
{
    int canOpenFlag = 0;
    QVariant typeData = m_devTypeCombo->currentData();
    m_devType = typeData.toInt();
    m_dispalyCAN->append(tr("设备类型：%1").arg(m_devType));

    QVariant devIndexData = m_devIndexCombo->currentData();
    m_devIndex = devIndexData.toInt();
    m_dispalyCAN->append(tr("设备索引：%1").arg(m_devIndex));

    QVariant channelData = m_channelCombo->currentData();
    m_channelIndex = channelData.toInt();
    m_dispalyCAN->append(tr("通道索引：%1").arg(m_channelIndex));

    if (m_connectionFlag == 1)
    {
        m_connectionFlag = 0;
        usleep(100000);
        VCI_CloseDevice(m_devType, m_devIndex);
        return;
    }

    VCI_INIT_CONFIG init_config;

    QVariant baudData = m_baudCombo->currentData();
    int baudRate = baudData.toInt();
    GetTimeCode(baudRate);
    init_config.Timing0 = m_time0;
    init_config.Timing1 = m_time1;
    m_dispalyCAN->append(tr("定时器0：%1").arg(m_time0));
    m_dispalyCAN->append(tr("定时器1：%1").arg(m_time1));
    init_config.AccCode = 0x00000000;
    init_config.AccMask = 0xffffffff;

    QVariant modeData = m_modeCombo->currentData();
    init_config.Mode = modeData.toInt();
    init_config.Filter = 0;   // 0/1：接收所有帧型；2：只接受标准帧；3：只接受扩展帧。

    //打开设备
    if(VCI_OpenDevice(m_devType, m_devIndex, 0) != STATUS_OK)
    {
        VCI_CloseDevice(m_devType, m_devIndex);
        QMessageBox::information(this, "警告", "打开设备设备失败!");
        return;
    }
    m_dispalyCAN->append("设备打开成功");


    bool openAllCAN = m_openAllCANBox->isChecked();

    if (openAllCAN)
    {
        canOpenFlag = StartCAN(m_devType, m_devIndex, 0, init_config);
        canOpenFlag = StartCAN(m_devType, m_devIndex, 1, init_config);
        if (canOpenFlag == -1)
            return;
        usleep(100000);
    }
    else
    {
        canOpenFlag = StartCAN(m_devType, m_devIndex, m_channelIndex, init_config);
        if (canOpenFlag == -1)
            return;
    }

    m_connectionFlag = 1;

    m_recvCANthread = new CANThread(m_devType, m_devIndex, m_channelIndex, openAllCAN);
    m_recvCANthread->start();

    connect(m_recvCANthread, SIGNAL(RecvCount(uint64_t)), this, SLOT(UpdateUI(uint64_t)), Qt::QueuedConnection);
    connect(m_recvCANthread, SIGNAL(ErrorInfo(QString)), this, SLOT(PinrtErrorInfo(QString)), Qt::QueuedConnection);

    m_canConnectBut->setDisabled(true);
    m_canDisconnectBut->setDisabled(false);
    g_CanConnectionFlag = true;
}


void CANSQLSettingWidget::PinrtErrorInfo(QString errorstring)
{
    m_dispalyCAN->append(QString("<font color='red'>%1</font>").arg(errorstring));
}


void CANSQLSettingWidget::UpdateUI(uint64_t count)
{
    m_dispalyCAN->append(QString("<font color='green'>接收：帧%1---成功</font>").arg(count));
}


void CANSQLSettingWidget::OnDisconnectCAN()
{
    if (m_connectionFlag == 1)
    {
        VCI_CloseDevice(m_devType, m_devIndex);
        m_connectionFlag = 0;
        g_CanConnectionFlag = false;

        m_recvCANthread->terminate();
        m_recvCANthread->wait();
        delete m_recvCANthread;   //销毁子线程
        m_recvCANthread = NULL;
        m_dispalyCAN->append("设备已断开");
        m_canConnectBut->setDisabled(false);
        m_canDisconnectBut->setDisabled(true);
    }
}


void CANSQLSettingWidget::OnCANSend()
{
    if (m_connectionFlag == 0)
        return;

    VCI_CAN_OBJ frameinfo;
    memset(&frameinfo, 0, sizeof(frameinfo));
    char szFrameID[9];
    memset(szFrameID, '0', 9);
    unsigned char FrameID[4];
    memset(FrameID, 0 ,4);
    unsigned char Data[8];
    char szData[25];
    BYTE datalen = 0;

    QString m_EditSendFrmID;
    QString m_EditSendData;

    m_EditSendFrmID = m_sendID->text();
    m_EditSendData = m_sendData->text();

    if (m_EditSendFrmID.isEmpty()||
            m_EditSendData.isEmpty())   //update
    {
        QMessageBox::information(this, "提醒", "请输入发送ID和发送数据!");
        return;
    }

    if (m_EditSendFrmID.length()>8)   //这里的8是随意给定的长度吗？CAN的标准帧ID是11位，扩展帧是29位。注意是位，不是字节。
    {
        QMessageBox::information(this, "提醒", "ID长度超过8字节，请重新输入! ");
        return;
    }

    if (m_EditSendData.length()>24)
    {
        QMessageBox::information(this, "提醒", "数据长度超过24字节，请重新输入! ");
        return;
    }

    //这个ID最终在CAN帧格式中是按位填充。因此在数组中存放时，若按照位的填充方式，应该从低位开始填充，低位对应的数组右边。
    std::string str = m_EditSendFrmID.toStdString();
    const char* ch = str.c_str();

    strcpy(&szFrameID[8 - m_EditSendFrmID.length()], ch);
    Str2Data((unsigned char*)szFrameID, FrameID, 4, 0);   //ID长度---4

    std::string str1 = m_EditSendData.toStdString();
    const char* ch1 = str1.c_str();

    datalen = (m_EditSendData.length() + 1) / 3;
    strcpy(szData, ch1);   //update
    Str2Data((unsigned char*)szData, Data, datalen, 1);

    frameinfo.SendType = 0;
    frameinfo.DataLen = datalen;
    memcpy(&frameinfo.Data, Data, datalen);

    frameinfo.RemoteFlag = 0;   //update
    frameinfo.ExternFlag = 0;   //update
    if (frameinfo.ExternFlag == 1)
    {
        frameinfo.ID = ((DWORD)FrameID[0] << 24) + ((DWORD)FrameID[1] << 16) + ((DWORD)FrameID[2] << 8) +
                ((DWORD)FrameID[3]);
    }
    else
    {
        frameinfo.ID = ((DWORD)FrameID[2] << 8) + ((DWORD)FrameID[3]);
    }

    Transmit(false, frameinfo);
}


void CANSQLSettingWidget::GetTimeCode(int baud)
{
    switch (baud)
    {
    case 10:
        m_time0 = 0x31;
        m_time1 = 0x1C;
        break;
    case 20:
        m_time0 = 0x18;
        m_time1 = 0x1C;
        break;
    case 50:
        m_time0 = 0x09;
        m_time1 = 0x1C;
        break;
    case 100:
        m_time0 = 0x04;
        m_time1 = 0x1C;
        break;
    case 200:
        m_time0 = 0x81;
        m_time1 = 0xFA;
        break;
    case 250:
        m_time0 = 0x01;
        m_time1 = 0x1C;
        break;
    case 500:
        m_time0 = 0x00;
        m_time1 = 0x1C;
        break;
        m_time0 = 0x00;
    case 800:
        m_time1 = 0x16;
        break;
    case 1000:
        m_time0 = 0x00;
        m_time1 = 0x14;
        break;
    default:
        break;
    }
}


int CANSQLSettingWidget::StartCAN(int devType, int devIndex, int canIndex, VCI_INIT_CONFIG config)
{
    //初始化通道设备
    if (VCI_InitCAN(devType, devIndex, canIndex, &config) != STATUS_OK)
    {
        QMessageBox::information(this, "警告", tr("串口%1初始化失败!").arg(canIndex));
        m_dispalyCAN->append(QString("串口%1初始化失败").arg(canIndex));
        VCI_CloseDevice(devType, devIndex);
        return -1;
    }
    m_dispalyCAN->append(QString("串口%1初始化成功").arg(canIndex));

    //打开设备通道
    if (VCI_StartCAN(devType, devIndex, canIndex) == STATUS_OK)
    {
        m_dispalyCAN->append(tr("串口%1启动成功").arg(canIndex));
    }
    else
    {
        QMessageBox::information(this, "警告", tr("串口%1启动失败!").arg(canIndex));
        m_dispalyCAN->append(QString("串口%1启动失败").arg(canIndex));
        VCI_CloseDevice(devType, devIndex);
        return -1;
    }
    return 0;
}


int CANSQLSettingWidget::Str2Data(unsigned char *str, unsigned char *data, int len, int flag)
{
    unsigned char cTmp = 0;
    int i = 0;
    for (int j = 0; j<len; j++)
    {
        if (Char2Int(str[i++], &cTmp))
            return 1;
        data[j] = cTmp;
        if (Char2Int(str[i++], &cTmp))
            return 1;
        data[j] = (data[j] << 4) + cTmp;   //<<4是因为十六进制标示的01,02两个数字占一个char型。char型有8位，因此一个数字占4位。
        if (flag == 1)
            i++;
    }
    return 0;
}


int CANSQLSettingWidget::Char2Int(unsigned char chr, unsigned char *cint)
{
    unsigned char cTmp;
    cTmp = chr - 48;   //0---ASCII
    if (cTmp <= 9)
    {
        *cint = cTmp;
        return 0;
    }
    cTmp = chr - 65;   //A---ASCII
    if (cTmp <= 5)
    {
        *cint = (cTmp + 10);
        return 0;
    }
    cTmp = chr - 97;   //a---ASCII
    if (cTmp <= 5)
    {
        *cint = (cTmp + 10);
        return 0;
    }
    return 1;
}


void CANSQLSettingWidget::Transmit(bool successFlag, VCI_CAN_OBJ frameinfo)
{
    static uint64_t SendCount = 0;
    int flag = 0;
    if (!successFlag)
    {
        flag = VCI_Transmit(m_devType, m_devIndex, m_channelIndex, &frameinfo, 1);

        if ((flag!=1) && (successFlag==false))
        {
            Transmit(false, frameinfo);
        }
        else
        {
            SendCount++;
            m_dispalyCAN->append(tr("<font color='red'>发送：帧%1---成功</font>").arg(SendCount));
        }
    }
}





