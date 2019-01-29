#include "bmuinfowidget.h"

extern QList<UINT> g_BMURecvedList;
extern BMUData g_BMUSavedData;
extern BMUUIData g_GetCANBMUData[MAX_BMU_NUMBER];

void BMUInfoWidget::UpdateWidget()
{
    UINT id;
    while(!g_BMURecvedList.isEmpty())
    {
        id = g_BMURecvedList.takeFirst();
        SetBMUWidget(id);
    }
}

void BMUInfoWidget::SetBMUWidget(UINT id)
{
    UINT getID = 0;
    getID = id >> 4;

    switch (getID)
    {
    /** BMU基本参数 **/
    case 0x18FF01B:
    case 0x18FF02B:
    case 0x18FF10B:
    case 0x18FF20B:

    /** 模组配置 **/
    case 0x18FF60B:

    /** 软硬件版本 **/
    case 0x18FF70B:

    /** 单芯电压 **/
    case 0x18FF40B:
    case 0x18FF41B:
    case 0x18FF42B:
    case 0x18FF43B:

    /** 单体温度 **/
    case 0x18FF50B:
        SetBMUBasicPara(id);
        break;

    /** 均衡状态 **/
    case 0x18FF30B:
        SetBMUBalance(id);
        break;

    /** BMU状态 **/
    case 0x18FF00B:
        SetBMUStatus(id);
        break;

    default:
        break;
    }
}


void BMUInfoWidget::SetBMUStatus(UINT id)
{
    unsigned int index = 0;
    index = id & 0x0000000f;

    if (index == g_BMUSavedData.currentIndex)
    {
        OnlineBMUStatus();
        SetStatusValue(index);
    }

    g_BMUSavedData.Signal[index].sig0x18FF00Bx = RECV_SIGNAL_SUCCESSFUL;
    g_BMUSavedData.Timeout[index].sig0x18FF00Bx = RECV_SIGNAL_SUCCESSFUL;
}


void BMUInfoWidget::SetCellBalMode(UINT index)
{
    switch(g_GetCANBMUData[index].bmuBalStatus.cellBalMode)
    {
    case 0:
        m_cellBalMode->setText("空闲");
        break;
    case 1:
        m_cellBalMode->setText("自动均衡");
        break;
    case 2:
        m_cellBalMode->setText("手动均衡");
        break;
    default:
        m_cellBalMode->setText(QString("%1(错误)").arg(g_GetCANBMUData[index].bmuBalStatus.cellBalMode));
        break;
    }
}

void BMUInfoWidget::SetCellBalSt(UINT index)
{
    switch(g_GetCANBMUData[index].bmuBalStatus.cellBalSt)
    {
    case 0:
        m_cellBalSt->setText("空闲");
        break;
    case 1:
        m_cellBalSt->setText("预启动自动均衡");
        break;
    case 2:
        m_cellBalSt->setText("自动均衡中");
        break;
    case 3:
        m_cellBalSt->setText("预启动休息");
        break;
    case 4:
        m_cellBalSt->setText("休息中");
        break;
    case 5:
        m_cellBalSt->setText("均衡完成");
        break;
    case 6:
        m_cellBalSt->setText("预启动手动均衡");
        break;
    case 7:
        m_cellBalSt->setText("手动均衡中");
        break;
    case 8:
        m_cellBalSt->setText("均衡终止");
        break;
    default:
        m_cellBalSt->setText(QString("%1(错误)").arg(g_GetCANBMUData[index].bmuBalStatus.cellBalSt));
        break;
    }
}


void BMUInfoWidget::SetBMUBalance(UINT id)
{
    int i = 0;
    unsigned int index = 0;
    index = id & 0x0000000f;

    if (index == g_BMUSavedData.currentIndex)
    {
        m_cellBalMode->setEnabled(true);
        m_cellBalSt->setEnabled(true);
        m_cellBalMode->setStyleSheet("background-color:white");
        m_cellBalSt->setStyleSheet("background-color:white");
        SetCellBalMode(index);
        SetCellBalSt(index);

        for (i=0; i<MAX_CELL_VOLT_NUMBER; i++)
        {
            m_cellInBal[i]->setEnabled(true);

            if (g_GetCANBMUData[index].bmuBalStatus.cellInBal[i])
                m_cellInBal[i]->setStyleSheet("background-color:red");
            else
                m_cellInBal[i]->setStyleSheet("background-color:#32CD32");
        }
    }
    g_BMUSavedData.Signal[index].sig0x18FF30Bx = RECV_SIGNAL_SUCCESSFUL;
    g_BMUSavedData.Timeout[index].sig0x18FF30Bx = RECV_SIGNAL_SUCCESSFUL;
}


void BMUInfoWidget::SetBMUBasicPara(UINT id)
{
    unsigned int index = 0;
    index = id & 0x0000000f;
    UINT partID = 0;
    partID = id >> 4;

    switch (partID)
    {
    /** BMU基本参数 **/
    case 0x18FF01B:
        if (index == g_BMUSavedData.currentIndex)
        {
            OnlineBMUBasicP1();
            SetBasicP1Value(index);
        }
        g_BMUSavedData.Signal[index].sig0x18FF01Bx = RECV_SIGNAL_SUCCESSFUL;
        g_BMUSavedData.Timeout[index].sig0x18FF01Bx = RECV_SIGNAL_SUCCESSFUL;
        break;

    case 0x18FF02B:
        if (index == g_BMUSavedData.currentIndex)
        {
            OnlineBMUBasicP2();
            m_moudleVolt->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP2.moudleVolt));
            m_boardTemp->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP2.boardTemp));
        }
        g_BMUSavedData.Signal[index].sig0x18FF02Bx = RECV_SIGNAL_SUCCESSFUL;
        g_BMUSavedData.Timeout[index].sig0x18FF02Bx = RECV_SIGNAL_SUCCESSFUL;
        break;

    case 0x18FF10B:
        if (index == g_BMUSavedData.currentIndex)
        {
            OnlineBMUBasicP3();
            SetBasicP3Value(index);
        }
        g_BMUSavedData.Signal[index].sig0x18FF10Bx = RECV_SIGNAL_SUCCESSFUL;
        g_BMUSavedData.Timeout[index].sig0x18FF10Bx = RECV_SIGNAL_SUCCESSFUL;
        break;

    case 0x18FF20B:
        if (index == g_BMUSavedData.currentIndex)
        {
            OnlineBMUBasicP4();
            SetBasicP4Value(index);
        }
        g_BMUSavedData.Signal[index].sig0x18FF20Bx = RECV_SIGNAL_SUCCESSFUL;
        g_BMUSavedData.Timeout[index].sig0x18FF20Bx = RECV_SIGNAL_SUCCESSFUL;
        break;

        /** 模组配置 **/
    case 0x18FF60B:
        if (index == g_BMUSavedData.currentIndex)
        {
            OnlineBMUConfig();
            SetConfigValue(index);
        }
        g_BMUSavedData.Signal[index].sig0x18FF60Bx = RECV_SIGNAL_SUCCESSFUL;
        g_BMUSavedData.Timeout[index].sig0x18FF60Bx = RECV_SIGNAL_SUCCESSFUL;
        break;

        /** 软硬件版本 **/
    case 0x18FF70B:
        if (index == g_BMUSavedData.currentIndex)
        {
            OnlineBMUVersion();
            m_softwareVersion->setText(tr("%1-%2").arg(g_GetCANBMUData[index].bmuVersionInfo.SoftVerH)\
                                       .arg(g_GetCANBMUData[index].bmuVersionInfo.SoftVerL));
            m_hardwareVersion->setText(tr("%1-%2").arg(g_GetCANBMUData[index].bmuVersionInfo.HWVerH)\
                                       .arg(g_GetCANBMUData[index].bmuVersionInfo.HWVerL));
            m_updateDate->setText(tr("%1-%2-%3 %4:00:00").arg(g_GetCANBMUData[index].bmuVersionInfo.UpdateYear)\
                                  .arg(g_GetCANBMUData[index].bmuVersionInfo.UpdateMonth).arg(g_GetCANBMUData[index].bmuVersionInfo.UpdateDay)\
                                  .arg(g_GetCANBMUData[index].bmuVersionInfo.UpdateHour));
        }
        g_BMUSavedData.Signal[index].sig0x18FF70Bx = RECV_SIGNAL_SUCCESSFUL;
        g_BMUSavedData.Timeout[index].sig0x18FF70Bx = RECV_SIGNAL_SUCCESSFUL;
        break;

        /** 单芯电压 **/
    case 0x18FF40B:
        if (index == g_BMUSavedData.currentIndex)
        {
            OnlineBMUCellVolt(0);
            m_cellVolt[0]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[0]));
            m_cellVolt[1]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[1]));
            m_cellVolt[2]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[2]));
            m_cellVolt[3]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[3]));
        }
        g_BMUSavedData.Signal[index].sig0x18FF40Bx = RECV_SIGNAL_SUCCESSFUL;
        g_BMUSavedData.Timeout[index].sig0x18FF40Bx = RECV_SIGNAL_SUCCESSFUL;
        break;

    case 0x18FF41B:
        if (index == g_BMUSavedData.currentIndex)
        {
            OnlineBMUCellVolt(1);
            m_cellVolt[4]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[4]));
            m_cellVolt[5]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[5]));
            m_cellVolt[6]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[6]));
            m_cellVolt[7]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[7]));
        }
        g_BMUSavedData.Signal[index].sig0x18FF41Bx = RECV_SIGNAL_SUCCESSFUL;
        g_BMUSavedData.Timeout[index].sig0x18FF41Bx = RECV_SIGNAL_SUCCESSFUL;
        break;

    case 0x18FF42B:
        if (index == g_BMUSavedData.currentIndex)
        {
            OnlineBMUCellVolt(2);
            m_cellVolt[8]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[8]));
            m_cellVolt[9]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[9]));
            m_cellVolt[10]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[10]));
            m_cellVolt[11]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[11]));
        }
        g_BMUSavedData.Signal[index].sig0x18FF42Bx = RECV_SIGNAL_SUCCESSFUL;
        g_BMUSavedData.Timeout[index].sig0x18FF42Bx = RECV_SIGNAL_SUCCESSFUL;
        break;

    case 0x18FF43B:
        if (index == g_BMUSavedData.currentIndex)
        {
            OnlineBMUCellVolt(3);
            m_cellVolt[12]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[12]));
            m_cellVolt[13]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[13]));
            m_cellVolt[14]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[14]));
            m_cellVolt[15]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[15]));
        }
        g_BMUSavedData.Signal[index].sig0x18FF43Bx = RECV_SIGNAL_SUCCESSFUL;
        g_BMUSavedData.Timeout[index].sig0x18FF43Bx = RECV_SIGNAL_SUCCESSFUL;
        break;

    /** 单体温度 **/
    case 0x18FF50B:
        if (index == g_BMUSavedData.currentIndex)
        {
            OnlineBMUCellTemp();
            m_cellTemp[0]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellTemp.cellTemp[0]));
            m_cellTemp[1]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellTemp.cellTemp[1]));
            m_cellTemp[2]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellTemp.cellTemp[2]));
            m_cellTemp[3]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellTemp.cellTemp[3]));
        }
        g_BMUSavedData.Signal[index].sig0x18FF50Bx = RECV_SIGNAL_SUCCESSFUL;
        g_BMUSavedData.Timeout[index].sig0x18FF50Bx = RECV_SIGNAL_SUCCESSFUL;
        break;

    default:
        break;
    }
}


void BMUInfoWidget::ShowCurrentBMU(UINT index)
{
    UINT oldIndex = g_BMUSavedData.currentIndex;

    BMUButton[oldIndex]->setStyleSheet("background-color:lightgray");
    BMUButton[index]->setStyleSheet("background-color:#6495ED");
    g_BMUSavedData.currentIndex = index;
    SetBMUValue(index);
    SetBMUTimeout(index);
}


void BMUInfoWidget::SetBMUValue(UINT index)
{
    int i = 0;
    /** BMU基本参数 **/
    SetBasicP1Value(index);

    m_moudleVolt->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP2.moudleVolt));
    m_boardTemp->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP2.boardTemp));

    SetBasicP3Value(index);
    SetBasicP4Value(index);

    /** 模组配置 **/
    SetConfigValue(index);

    /** 版本信息 **/
    m_softwareVersion->setText(tr("%1-%2").arg(g_GetCANBMUData[index].bmuVersionInfo.SoftVerH)\
                               .arg(g_GetCANBMUData[index].bmuVersionInfo.SoftVerL));
    m_hardwareVersion->setText(tr("%1-%2").arg(g_GetCANBMUData[index].bmuVersionInfo.HWVerH)\
                               .arg(g_GetCANBMUData[index].bmuVersionInfo.HWVerL));
    m_updateDate->setText(tr("%1-%2-%3 %4:00:00").arg(g_GetCANBMUData[index].bmuVersionInfo.UpdateYear)\
                          .arg(g_GetCANBMUData[index].bmuVersionInfo.UpdateMonth)\
                          .arg(g_GetCANBMUData[index].bmuVersionInfo.UpdateDay)\
                          .arg(g_GetCANBMUData[index].bmuVersionInfo.UpdateHour));

    /** 单芯电压 **/
    for(i=0; i<MAX_CELL_VOLT_NUMBER; i++)
        m_cellVolt[i]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellVolt.cellVolt[i]));

    /** 单芯温度 **/
    for(i=0; i<MAX_CELL_TEMP_NUMBER; i++)
        m_cellTemp[i]->setText(tr("%1").arg(g_GetCANBMUData[index].bmuCellTemp.cellTemp[i]));

    /** 均衡状态 **/
    SetCellBalMode(index);
    SetCellBalSt(index);
    for (i=0; i<MAX_CELL_VOLT_NUMBER; i++)
    {
        if (g_GetCANBMUData[index].bmuBalStatus.cellInBal[i])
            m_cellInBal[i]->setStyleSheet("background-color:red");
        else
            m_cellInBal[i]->setStyleSheet("background-color:#32CD32");
    }

    /** BMU状态 **/
    SetStatusValue(index);
}


void BMUInfoWidget::SetBMUTimeout(UINT index)
{
    /** BMU基本参数 **/
    //0x18FF01Bx
    if (g_BMUSavedData.Timeout[index].sig0x18FF01Bx)
        OnlineBMUBasicP1();
    else
        OfflineBMUBasicP1();

    //0x18FF02Bx
    if (g_BMUSavedData.Timeout[index].sig0x18FF02Bx)
        OnlineBMUBasicP2();
    else
        OfflineBMUBasicP2();

    //0x18FF10Bx
    if (g_BMUSavedData.Timeout[index].sig0x18FF10Bx)
        OnlineBMUBasicP3();
    else
        OfflineBMUBasicP3();

    //0x18FF20Bx
    if (g_BMUSavedData.Timeout[index].sig0x18FF20Bx)
        OnlineBMUBasicP4();
    else
        OfflineBMUBasicP4();

    /** 模组配置 **/
    //0x18FF60Bx
    if (g_BMUSavedData.Timeout[index].sig0x18FF60Bx)
        OnlineBMUConfig();
    else
        OfflineBMUConfig();

    /** 版本信息 **/
    //0x18FF70B
    if (g_BMUSavedData.Timeout[index].sig0x18FF70Bx)
        OnlineBMUVersion();
    else
        OfflineBMUVersion();

    /** 单芯电压 **/
    //0x18FF40B
    if (g_BMUSavedData.Timeout[index].sig0x18FF40Bx)
        OnlineBMUCellVolt(0);
    else
        OfflineBMUCellVolt(0);

    //0x18FF41B
    if (g_BMUSavedData.Timeout[index].sig0x18FF41Bx)
        OnlineBMUCellVolt(1);
    else
        OfflineBMUCellVolt(1);

    //0x18FF42B
    if (g_BMUSavedData.Timeout[index].sig0x18FF42Bx)
        OnlineBMUCellVolt(2);
    else
        OfflineBMUCellVolt(2);

    //0x18FF43B
    if (g_BMUSavedData.Timeout[index].sig0x18FF43Bx)
        OnlineBMUCellVolt(3);
    else
        OfflineBMUCellVolt(3);

    /** 单芯温度 **/
    //0x18FF50B
    if (g_BMUSavedData.Timeout[index].sig0x18FF50Bx)
        OnlineBMUCellTemp();
    else
        OfflineBMUCellTemp();

    /** 均衡状态 **/
    //0x18FF30B
    if (g_BMUSavedData.Timeout[index].sig0x18FF30Bx)
        OnlineBMUBalStatus();
    else
        OfflineBMUBalStatus();

    /** BMU状态 **/
    if (g_BMUSavedData.Timeout[index].sig0x18FF00Bx)
        OnlineBMUStatus();
    else
        OfflineBMUStatus();
}

void BMUInfoWidget::SignalTimeout()
{
    int index  = g_BMUSavedData.currentIndex;
    int i = 0;
    /** BMU基本参数 **/
    if (!g_BMUSavedData.Signal[index].sig0x18FF01Bx)
    {
        OfflineBMUBasicP1();
        g_BMUSavedData.Timeout[index].sig0x18FF01Bx = RECV_SIGNAL_FAIL;
    }

    if (!g_BMUSavedData.Signal[index].sig0x18FF02Bx)
    {
        OfflineBMUBasicP2();
        g_BMUSavedData.Timeout[index].sig0x18FF02Bx = RECV_SIGNAL_FAIL;
    }

    if (!g_BMUSavedData.Signal[index].sig0x18FF10Bx)
    {
        OfflineBMUBasicP3();
        g_BMUSavedData.Timeout[index].sig0x18FF10Bx = RECV_SIGNAL_FAIL;
    }

    if (!g_BMUSavedData.Signal[index].sig0x18FF20Bx)
    {
        OfflineBMUBasicP4();
        g_BMUSavedData.Timeout[index].sig0x18FF20Bx = RECV_SIGNAL_FAIL;
    }

    if (!g_BMUSavedData.Signal[index].sig0x18FF60Bx)
    {
        OfflineBMUConfig();
        g_BMUSavedData.Timeout[index].sig0x18FF60Bx = RECV_SIGNAL_FAIL;
    }

    if (!g_BMUSavedData.Signal[index].sig0x18FF70Bx)
    {
        OfflineBMUVersion();
        g_BMUSavedData.Timeout[index].sig0x18FF70Bx = RECV_SIGNAL_FAIL;
    }

    if (!g_BMUSavedData.Signal[index].sig0x18FF40Bx)
    {
        OfflineBMUCellVolt(0);
        g_BMUSavedData.Timeout[index].sig0x18FF40Bx = RECV_SIGNAL_FAIL;
    }

    if (!g_BMUSavedData.Signal[index].sig0x18FF41Bx)
    {
        OfflineBMUCellVolt(1);
        g_BMUSavedData.Timeout[index].sig0x18FF41Bx = RECV_SIGNAL_FAIL;
    }

    if (!g_BMUSavedData.Signal[index].sig0x18FF42Bx)
    {
        OfflineBMUCellVolt(2);
        g_BMUSavedData.Timeout[index].sig0x18FF42Bx = RECV_SIGNAL_FAIL;
    }

    if (!g_BMUSavedData.Signal[index].sig0x18FF43Bx)
    {
        OfflineBMUCellVolt(3);
        g_BMUSavedData.Timeout[index].sig0x18FF43Bx = RECV_SIGNAL_FAIL;
    }

    if (!g_BMUSavedData.Signal[index].sig0x18FF50Bx)
    {
        OfflineBMUCellTemp();
        g_BMUSavedData.Timeout[index].sig0x18FF50Bx = RECV_SIGNAL_FAIL;
    }

    if (!g_BMUSavedData.Signal[index].sig0x18FF30Bx)
    {
        OfflineBMUBalStatus();
        g_BMUSavedData.Timeout[index].sig0x18FF30Bx = RECV_SIGNAL_FAIL;
    }

    if (!g_BMUSavedData.Signal[index].sig0x18FF00Bx)
    {
        OfflineBMUStatus();
        g_BMUSavedData.Timeout[index].sig0x18FF00Bx = RECV_SIGNAL_FAIL;
    }

    for(i=0; i<MAX_BMU_NUMBER; i++)
    {
        g_BMUSavedData.Signal[i].sig0x18FF01Bx = RECV_SIGNAL_FAIL;
        g_BMUSavedData.Signal[i].sig0x18FF02Bx = RECV_SIGNAL_FAIL;
        g_BMUSavedData.Signal[i].sig0x18FF10Bx = RECV_SIGNAL_FAIL;
        g_BMUSavedData.Signal[i].sig0x18FF20Bx = RECV_SIGNAL_FAIL;
        g_BMUSavedData.Signal[i].sig0x18FF30Bx = RECV_SIGNAL_FAIL;
        g_BMUSavedData.Signal[i].sig0x18FF60Bx = RECV_SIGNAL_FAIL;
        g_BMUSavedData.Signal[i].sig0x18FF70Bx = RECV_SIGNAL_FAIL;
        g_BMUSavedData.Signal[i].sig0x18FF40Bx = RECV_SIGNAL_FAIL;
        g_BMUSavedData.Signal[i].sig0x18FF41Bx = RECV_SIGNAL_FAIL;
        g_BMUSavedData.Signal[i].sig0x18FF42Bx = RECV_SIGNAL_FAIL;
        g_BMUSavedData.Signal[i].sig0x18FF43Bx = RECV_SIGNAL_FAIL;
        g_BMUSavedData.Signal[i].sig0x18FF50Bx = RECV_SIGNAL_FAIL;
        g_BMUSavedData.Signal[i].sig0x18FF00Bx = RECV_SIGNAL_FAIL;
    }
}

void BMUInfoWidget::OnlineBMUBasicP1()
{
    m_soc->setStyleSheet("background-color:white");
    m_soh->setStyleSheet("background-color:white");
    m_battCycle->setStyleSheet("background-color:white");
    m_diffCellVolt->setStyleSheet("background-color:white");
    m_diffCellTemp->setStyleSheet("background-color:white");

    m_soc->setEnabled(true);
    m_soh->setEnabled(true);
    m_battCycle->setEnabled(true);
    m_diffCellVolt->setEnabled(true);
    m_diffCellTemp->setEnabled(true);
}

void BMUInfoWidget::OfflineBMUBasicP1()
{
    m_soc->setStyleSheet("background-color:lightgray");
    m_soh->setStyleSheet("background-color:lightgray");
    m_battCycle->setStyleSheet("background-color:lightgray");
    m_diffCellVolt->setStyleSheet("background-color:lightgray");
    m_diffCellTemp->setStyleSheet("background-color:lightgray");

    m_soc->setEnabled(false);
    m_soh->setEnabled(false);
    m_battCycle->setEnabled(false);
    m_diffCellVolt->setEnabled(false);
    m_diffCellTemp->setEnabled(false);
}

void BMUInfoWidget::OnlineBMUBasicP2()
{
    m_moudleVolt->setStyleSheet("background-color:white");
    m_boardTemp->setStyleSheet("background-color:white");
    m_moudleVolt->setEnabled(true);
    m_boardTemp->setEnabled(true);
}


void BMUInfoWidget::OfflineBMUBasicP2()
{
    m_moudleVolt->setStyleSheet("background-color:lightgray");
    m_boardTemp->setStyleSheet("background-color:lightgray");
    m_moudleVolt->setEnabled(false);
    m_boardTemp->setEnabled(false);
}

void BMUInfoWidget::OnlineBMUBasicP3()
{
    m_maxCellVolt->setStyleSheet("background-color:white");
    m_minCellVolt->setStyleSheet("background-color:white");
    m_avgCellVolt->setStyleSheet("background-color:white");
    m_maxCVNO->setStyleSheet("background-color:white");
    m_minCVNO->setStyleSheet("background-color:white");

    m_maxCellVolt->setEnabled(true);
    m_minCellVolt->setEnabled(true);
    m_avgCellVolt->setEnabled(true);
    m_maxCVNO->setEnabled(true);
    m_minCVNO->setEnabled(true);
}


void BMUInfoWidget::OfflineBMUBasicP3()
{
    m_maxCellVolt->setStyleSheet("background-color:lightgray");
    m_minCellVolt->setStyleSheet("background-color:lightgray");
    m_avgCellVolt->setStyleSheet("background-color:lightgray");
    m_maxCVNO->setStyleSheet("background-color:lightgray");
    m_minCVNO->setStyleSheet("background-color:lightgray");

    m_maxCellVolt->setEnabled(false);
    m_minCellVolt->setEnabled(false);
    m_avgCellVolt->setEnabled(false);
    m_maxCVNO->setEnabled(false);
    m_minCVNO->setEnabled(false);
}

void BMUInfoWidget::OnlineBMUBasicP4()
{
    m_maxCellTemp->setStyleSheet("background-color:white");
    m_minCellTemp->setStyleSheet("background-color:white");
    m_avgCellTemp->setStyleSheet("background-color:white");
    m_maxCTNO->setStyleSheet("background-color:white");
    m_minCTNO->setStyleSheet("background-color:white");

    m_maxCellTemp->setEnabled(true);
    m_minCellTemp->setEnabled(true);
    m_avgCellTemp->setEnabled(true);
    m_maxCTNO->setEnabled(true);
    m_minCTNO->setEnabled(true);
}


void BMUInfoWidget::OfflineBMUBasicP4()
{
    m_maxCellTemp->setStyleSheet("background-color:lightgray");
    m_minCellTemp->setStyleSheet("background-color:lightgray");
    m_avgCellTemp->setStyleSheet("background-color:lightgray");
    m_maxCTNO->setStyleSheet("background-color:lightgray");
    m_minCTNO->setStyleSheet("background-color:lightgray");

    m_maxCellTemp->setEnabled(false);
    m_minCellTemp->setEnabled(false);
    m_avgCellTemp->setEnabled(false);
    m_maxCTNO->setEnabled(false);
    m_minCTNO->setEnabled(false);
}

void BMUInfoWidget::OnlineBMUConfig()
{
    m_cellAH->setStyleSheet("background-color:white");
    m_cellRateVolt->setStyleSheet("background-color:white");
    m_cellNum->setStyleSheet("background-color:white");
    m_tempNum->setStyleSheet("background-color:white");

    m_cellAH->setEnabled(true);
    m_cellRateVolt->setEnabled(true);
    m_cellNum->setEnabled(true);
    m_tempNum->setEnabled(true);
}

void BMUInfoWidget::OfflineBMUConfig()
{
    m_cellAH->setStyleSheet("background-color:lightgray");
    m_cellRateVolt->setStyleSheet("background-color:lightgray");
    m_cellNum->setStyleSheet("background-color:lightgray");
    m_tempNum->setStyleSheet("background-color:lightgray");

    m_cellAH->setEnabled(false);
    m_cellRateVolt->setEnabled(false);
    m_cellNum->setEnabled(false);
    m_tempNum->setEnabled(false);
}

void BMUInfoWidget::OnlineBMUVersion()
{
    m_softwareVersion->setStyleSheet("background-color:white");
    m_hardwareVersion->setStyleSheet("background-color:white");
    m_updateDate->setStyleSheet("background-color:white");

    m_softwareVersion->setEnabled(true);
    m_hardwareVersion->setEnabled(true);
    m_updateDate->setEnabled(true);
}

void BMUInfoWidget::OfflineBMUVersion()
{
    m_softwareVersion->setStyleSheet("background-color:lightgray");
    m_hardwareVersion->setStyleSheet("background-color:lightgray");
    m_updateDate->setStyleSheet("background-color:lightgray");

    m_softwareVersion->setEnabled(false);
    m_hardwareVersion->setEnabled(false);
    m_updateDate->setEnabled(false);
}


void BMUInfoWidget::OnlineBMUCellVolt(int num)
{
    switch (num)
    {
    case 0:
        m_cellVolt[0]->setStyleSheet("background-color:white");
        m_cellVolt[1]->setStyleSheet("background-color:white");
        m_cellVolt[2]->setStyleSheet("background-color:white");
        m_cellVolt[3]->setStyleSheet("background-color:white");
        m_cellVolt[0]->setEnabled(true);
        m_cellVolt[1]->setEnabled(true);
        m_cellVolt[2]->setEnabled(true);
        m_cellVolt[3]->setEnabled(true);
        break;

    case 1:
        m_cellVolt[4]->setStyleSheet("background-color:white");
        m_cellVolt[5]->setStyleSheet("background-color:white");
        m_cellVolt[6]->setStyleSheet("background-color:white");
        m_cellVolt[7]->setStyleSheet("background-color:white");
        m_cellVolt[4]->setEnabled(true);
        m_cellVolt[5]->setEnabled(true);
        m_cellVolt[6]->setEnabled(true);
        m_cellVolt[7]->setEnabled(true);
        break;

    case 2:
        m_cellVolt[8]->setStyleSheet("background-color:white");
        m_cellVolt[9]->setStyleSheet("background-color:white");
        m_cellVolt[10]->setStyleSheet("background-color:white");
        m_cellVolt[11]->setStyleSheet("background-color:white");
        m_cellVolt[8]->setEnabled(true);
        m_cellVolt[9]->setEnabled(true);
        m_cellVolt[10]->setEnabled(true);
        m_cellVolt[11]->setEnabled(true);
        break;

    case 3:
        m_cellVolt[12]->setStyleSheet("background-color:white");
        m_cellVolt[13]->setStyleSheet("background-color:white");
        m_cellVolt[14]->setStyleSheet("background-color:white");
        m_cellVolt[15]->setStyleSheet("background-color:white");
        m_cellVolt[12]->setEnabled(true);
        m_cellVolt[13]->setEnabled(true);
        m_cellVolt[14]->setEnabled(true);
        m_cellVolt[15]->setEnabled(true);
        break;

    default:
        break;
    }
}

void BMUInfoWidget::OfflineBMUCellVolt(int num)
{
    switch(num)
    {
    case 0:
        m_cellVolt[0]->setStyleSheet("background-color:lightgray");
        m_cellVolt[1]->setStyleSheet("background-color:lightgray");
        m_cellVolt[2]->setStyleSheet("background-color:lightgray");
        m_cellVolt[3]->setStyleSheet("background-color:lightgray");
        m_cellVolt[0]->setEnabled(false);
        m_cellVolt[1]->setEnabled(false);
        m_cellVolt[2]->setEnabled(false);
        m_cellVolt[3]->setEnabled(false);
        break;

    case 1:
        m_cellVolt[4]->setStyleSheet("background-color:lightgray");
        m_cellVolt[5]->setStyleSheet("background-color:lightgray");
        m_cellVolt[6]->setStyleSheet("background-color:lightgray");
        m_cellVolt[7]->setStyleSheet("background-color:lightgray");
        m_cellVolt[4]->setEnabled(false);
        m_cellVolt[5]->setEnabled(false);
        m_cellVolt[6]->setEnabled(false);
        m_cellVolt[7]->setEnabled(false);
        break;

    case 2:
        m_cellVolt[8]->setStyleSheet("background-color:lightgray");
        m_cellVolt[9]->setStyleSheet("background-color:lightgray");
        m_cellVolt[10]->setStyleSheet("background-color:lightgray");
        m_cellVolt[11]->setStyleSheet("background-color:lightgray");
        m_cellVolt[8]->setEnabled(false);
        m_cellVolt[9]->setEnabled(false);
        m_cellVolt[10]->setEnabled(false);
        m_cellVolt[11]->setEnabled(false);
        break;

    case 3:
        m_cellVolt[12]->setStyleSheet("background-color:lightgray");
        m_cellVolt[13]->setStyleSheet("background-color:lightgray");
        m_cellVolt[14]->setStyleSheet("background-color:lightgray");
        m_cellVolt[15]->setStyleSheet("background-color:lightgray");
        m_cellVolt[12]->setEnabled(false);
        m_cellVolt[13]->setEnabled(false);
        m_cellVolt[14]->setEnabled(false);
        m_cellVolt[15]->setEnabled(false);
        break;

    default:
        break;
    }
}


void BMUInfoWidget::OnlineBMUCellTemp()
{
    int i = 0;
    for (i=0; i<MAX_CELL_TEMP_NUMBER; i++)
    {
        m_cellTemp[i]->setStyleSheet("background-color:white");
        m_cellTemp[i]->setEnabled(true);
    }
}


void BMUInfoWidget::OfflineBMUCellTemp()
{
    int i = 0;
    for (i=0; i<MAX_CELL_TEMP_NUMBER; i++)
    {
        m_cellTemp[i]->setStyleSheet("background-color:lightgray");
        m_cellTemp[i]->setEnabled(false);
    }
}


void BMUInfoWidget::OnlineBMUBalStatus()
{
    int i = 0;

    m_cellBalMode->setEnabled(true);
    m_cellBalSt->setEnabled(true);
    m_cellBalMode->setStyleSheet("background-color:white");
    m_cellBalSt->setStyleSheet("background-color:white");

    for (i=0; i<MAX_CELL_VOLT_NUMBER; i++)
    {
        m_cellInBal[i]->setEnabled(true);
    }
}


void BMUInfoWidget::OfflineBMUBalStatus()
{
    int i = 0;
    m_cellBalMode->setEnabled(false);
    m_cellBalSt->setEnabled(false);
    m_cellBalMode->setStyleSheet("background-color:lightgray");
    m_cellBalSt->setStyleSheet("background-color:lightgray");

    for (i=0; i<MAX_CELL_VOLT_NUMBER; i++)
    {
        m_cellInBal[i]->setStyleSheet("background-color:lightgray");
        m_cellInBal[i]->setEnabled(false);
    }
}


void BMUInfoWidget::OnlineBMUStatus()
{
    m_afeSample->setEnabled(true);
    m_afeFault->setEnabled(true);
    m_owdSt->setEnabled(true);
    m_msgAlive->setEnabled(true);

    m_lv1CellVoltLow->setEnabled(true);
    m_lv1CellVoltHigh->setEnabled(true);
    m_lv1CellVoltDiff->setEnabled(true);
    m_lv1MoudleVoltLow->setEnabled(true);
    m_lv1MoudleVoltHigh->setEnabled(true);
    m_lv1AmbientTempLow->setEnabled(true);
    m_lv1AmbientTempHigh->setEnabled(true);
    m_lv1ChrgTempLow->setEnabled(true);
    m_lv1ChrgTempHigh->setEnabled(true);
    m_lv1DischrgTempLow->setEnabled(true);
    m_lv1DischrgTempHigh->setEnabled(true);

    m_lv2CellVoltLow->setEnabled(true);
    m_lv2CellVoltHigh->setEnabled(true);
    m_lv2CellVoltDiff->setEnabled(true);
    m_lv2MoudleVoltLow->setEnabled(true);
    m_lv2MoudleVoltHigh->setEnabled(true);
    m_lv2AmbientTempLow->setEnabled(true);
    m_lv2AmbientTempHigh->setEnabled(true);
    m_lv2ChrgTempLow->setEnabled(true);
    m_lv2ChrgTempHigh->setEnabled(true);
    m_lv2DischrgTempLow->setEnabled(true);
    m_lv2DischrgTempHigh->setEnabled(true);

    m_afeSample->setStyleSheet("background-color:white");
    m_afeFault->setStyleSheet("background-color:white");
    m_owdSt->setStyleSheet("background-color:white");
    m_msgAlive->setStyleSheet("background-color:white");
}


void BMUInfoWidget::OfflineBMUStatus()
{
    m_afeSample->setEnabled(false);
    m_afeFault->setEnabled(false);
    m_owdSt->setEnabled(false);
    m_msgAlive->setEnabled(false);

    m_lv1CellVoltLow->setEnabled(false);
    m_lv1CellVoltHigh->setEnabled(false);
    m_lv1CellVoltDiff->setEnabled(false);
    m_lv1MoudleVoltLow->setEnabled(false);
    m_lv1MoudleVoltHigh->setEnabled(false);
    m_lv1AmbientTempLow->setEnabled(false);
    m_lv1AmbientTempHigh->setEnabled(false);
    m_lv1ChrgTempLow->setEnabled(false);
    m_lv1ChrgTempHigh->setEnabled(false);
    m_lv1DischrgTempLow->setEnabled(false);
    m_lv1DischrgTempHigh->setEnabled(false);

    m_lv2CellVoltLow->setEnabled(false);
    m_lv2CellVoltHigh->setEnabled(false);
    m_lv2CellVoltDiff->setEnabled(false);
    m_lv2MoudleVoltLow->setEnabled(false);
    m_lv2MoudleVoltHigh->setEnabled(false);
    m_lv2AmbientTempLow->setEnabled(false);
    m_lv2AmbientTempHigh->setEnabled(false);
    m_lv2ChrgTempLow->setEnabled(false);
    m_lv2ChrgTempHigh->setEnabled(false);
    m_lv2DischrgTempLow->setEnabled(false);
    m_lv2DischrgTempHigh->setEnabled(false);

    m_afeSample->setStyleSheet("background-color:lightgray");
    m_afeFault->setStyleSheet("background-color:lightgray");
    m_owdSt->setStyleSheet("background-color:lightgray");
    m_msgAlive->setStyleSheet("background-color:lightgray");

    m_lv1CellVoltLow->setStyleSheet("background-color:lightgray");
    m_lv1CellVoltHigh->setStyleSheet("background-color:lightgray");
    m_lv1CellVoltDiff->setStyleSheet("background-color:lightgray");
    m_lv1MoudleVoltLow->setStyleSheet("background-color:lightgray");
    m_lv1MoudleVoltHigh->setStyleSheet("background-color:lightgray");
    m_lv1AmbientTempLow->setStyleSheet("background-color:lightgray");
    m_lv1AmbientTempHigh->setStyleSheet("background-color:lightgray");
    m_lv1ChrgTempLow->setStyleSheet("background-color:lightgray");
    m_lv1ChrgTempHigh->setStyleSheet("background-color:lightgray");
    m_lv1DischrgTempLow->setStyleSheet("background-color:lightgray");
    m_lv1DischrgTempHigh->setStyleSheet("background-color:lightgray");

    m_lv2CellVoltLow->setStyleSheet("background-color:lightgray");
    m_lv2CellVoltHigh->setStyleSheet("background-color:lightgray");
    m_lv2CellVoltDiff->setStyleSheet("background-color:lightgray");
    m_lv2MoudleVoltLow->setStyleSheet("background-color:lightgray");
    m_lv2MoudleVoltHigh->setStyleSheet("background-color:lightgray");
    m_lv2AmbientTempLow->setStyleSheet("background-color:lightgray");
    m_lv2AmbientTempHigh->setStyleSheet("background-color:lightgray");
    m_lv2ChrgTempLow->setStyleSheet("background-color:lightgray");
    m_lv2ChrgTempHigh->setStyleSheet("background-color:lightgray");
    m_lv2DischrgTempLow->setStyleSheet("background-color:lightgray");
    m_lv2DischrgTempHigh->setStyleSheet("background-color:lightgray");
}


void BMUInfoWidget::SetAFESample(UINT index)
{
    switch(g_GetCANBMUData[index].bmuStatus.AFESample)
    {
    case 0:
        m_afeSample->setText("正常");
        break;
    case 1:
        m_afeSample->setText("故障");
        break;
    default:
        m_afeSample->setText(QString("%1(错误)").arg(g_GetCANBMUData[index].bmuStatus.AFESample));
        break;
    }
}


void BMUInfoWidget::SetAFEFault(UINT index)
{
    switch(g_GetCANBMUData[index].bmuStatus.AFEFault)
    {
    case 0:
        m_afeFault->setText("正常");
        break;
    case 1:
        m_afeFault->setText("故障");
        break;
    default:
        m_afeFault->setText(QString("%1(错误)").arg(g_GetCANBMUData[index].bmuStatus.AFEFault));
        break;
    }
}


void BMUInfoWidget::SetOWDSt(UINT index)
{
    switch(g_GetCANBMUData[index].bmuStatus.OWDSt)
    {
    case 0:
        m_owdSt->setText("检测中");
        break;
    case 1:
        m_owdSt->setText("正常");
        break;
    case 2:
        m_owdSt->setText("断线");
        break;
    default:
        m_owdSt->setText(QString("%1(错误)").arg(g_GetCANBMUData[index].bmuStatus.OWDSt));
        break;
    }
}


void BMUInfoWidget::SetStatusValue(UINT index)
{
    SetAFESample(index);
    SetAFEFault(index);
    SetOWDSt(index);
    m_msgAlive->setText(tr("%1").arg(g_GetCANBMUData[index].bmuStatus.msgAlive));
    if (g_GetCANBMUData[index].bmuStatus.lv1CellVoltLow)
        m_lv1CellVoltLow->setStyleSheet("background-color:red");
    else
        m_lv1CellVoltLow->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv1CellVoltHigh)
        m_lv1CellVoltHigh->setStyleSheet("background-color:red");
    else
        m_lv1CellVoltHigh->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv1CellVoltDiff)
        m_lv1CellVoltDiff->setStyleSheet("background-color:red");
    else
        m_lv1CellVoltDiff->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv1MoudleVoltLow)
        m_lv1MoudleVoltLow->setStyleSheet("background-color:red");
    else
        m_lv1MoudleVoltLow->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv1MoudleVoltHigh)
        m_lv1MoudleVoltHigh->setStyleSheet("background-color:red");
    else
        m_lv1MoudleVoltHigh->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv1AmbientTempLow)
        m_lv1AmbientTempLow->setStyleSheet("background-color:red");
    else
        m_lv1AmbientTempLow->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv1AmbientTempHigh)
        m_lv1AmbientTempHigh->setStyleSheet("background-color:red");
    else
        m_lv1AmbientTempHigh->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv1ChrgTempLow)
        m_lv1ChrgTempLow->setStyleSheet("background-color:red");
    else
        m_lv1ChrgTempLow->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv1ChrgTempHigh)
        m_lv1ChrgTempHigh->setStyleSheet("background-color:red");
    else
        m_lv1ChrgTempHigh->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv1DischrgTempLow)
        m_lv1DischrgTempLow->setStyleSheet("background-color:red");
    else
        m_lv1DischrgTempLow->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv1DischrgTempHigh)
        m_lv1DischrgTempHigh->setStyleSheet("background-color:red");
    else
        m_lv1DischrgTempHigh->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv2CellVoltLow)
        m_lv2CellVoltLow->setStyleSheet("background-color:red");
    else
        m_lv2CellVoltLow->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv2CellVoltHigh)
        m_lv2CellVoltHigh->setStyleSheet("background-color:red");
    else
        m_lv2CellVoltHigh->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv2CellVoltDiff)
        m_lv2CellVoltDiff->setStyleSheet("background-color:red");
    else
        m_lv2CellVoltDiff->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv2MoudleVoltLow)
        m_lv2MoudleVoltLow->setStyleSheet("background-color:red");
    else
        m_lv2MoudleVoltLow->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv2MoudleVoltHigh)
        m_lv2MoudleVoltHigh->setStyleSheet("background-color:red");
    else
        m_lv2MoudleVoltHigh->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv2AmbientTempLow)
        m_lv2AmbientTempLow->setStyleSheet("background-color:red");
    else
        m_lv2AmbientTempLow->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv2AmbientTempHigh)
        m_lv2AmbientTempHigh->setStyleSheet("background-color:red");
    else
        m_lv2AmbientTempHigh->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv2ChrgTempLow)
        m_lv2ChrgTempLow->setStyleSheet("background-color:red");
    else
        m_lv2ChrgTempLow->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv2ChrgTempHigh)
        m_lv2ChrgTempHigh->setStyleSheet("background-color:red");
    else
        m_lv2ChrgTempHigh->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv2DischrgTempLow)
        m_lv2DischrgTempLow->setStyleSheet("background-color:red");
    else
        m_lv2DischrgTempLow->setStyleSheet("background-color:#32CD32");

    if (g_GetCANBMUData[index].bmuStatus.lv2DischrgTempHigh)
        m_lv2DischrgTempHigh->setStyleSheet("background-color:red");
    else
        m_lv2DischrgTempHigh->setStyleSheet("background-color:#32CD32");
}


void BMUInfoWidget::SetBasicP1Value(UINT index)
{
    m_soc->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP1.SOC));
    m_soh->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP1.SOH));
    m_battCycle->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP1.battCycle));
    m_diffCellVolt->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP1.diffCellVolt));
    m_diffCellTemp->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP1.diffCellTemp));
}

void BMUInfoWidget::SetBasicP3Value(UINT index)
{
    m_maxCellVolt->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP3.maxCellVolt));
    m_minCellVolt->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP3.minCellVolt));
    m_avgCellVolt->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP3.avgCellVolt));
    m_maxCVNO->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP3.maxCVNO));
    m_minCVNO->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP3.minCVNO));
}

void BMUInfoWidget::SetBasicP4Value(UINT index)
{
    m_maxCellTemp->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP4.maxCellTemp));
    m_minCellTemp->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP4.minCellTemp));
    m_avgCellTemp->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP4.avgCellTemp));
    m_maxCTNO->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP4.maxCTNO));
    m_minCTNO->setText(tr("%1").arg(g_GetCANBMUData[index].bmuBasicP4.minCTNO));
}


void BMUInfoWidget::SetConfigValue(UINT index)
{
    m_cellAH->setText(tr("%1").arg(g_GetCANBMUData[index].bmuModuleConfig.cellAH));
    m_cellRateVolt->setText(tr("%1").arg(g_GetCANBMUData[index].bmuModuleConfig.cellRateVolt));
    m_cellNum->setText(tr("%1").arg(g_GetCANBMUData[index].bmuModuleConfig.cellNum));
    m_tempNum->setText(tr("%1").arg(g_GetCANBMUData[index].bmuModuleConfig.tempNum));
}
