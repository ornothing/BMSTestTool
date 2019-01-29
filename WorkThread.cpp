#include <QString>
#include <QDebug>
#include <QList>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "WorkThread.h"
#include "databasedefine.h"
#include "historyrecorddefine.h"
#include "systemdefine.h"

#define FRAME_DATA_LEN 8

extern SQLInfo g_SQLInfo;
extern bool g_DBConnectionFlag;
extern bool g_CurrentTimeFlag;
extern int g_OpenOfflineFileFlag;

CANThread::CANThread(int deviceType, int deviceIndex, int channelIndex, bool openAll)
{
    m_deviceType = deviceType;
    m_deviceIndex = deviceIndex;
    m_channelIndex = channelIndex;
    m_OpenTwoChannel = openAll;
    ConnectToDatabase();
    InitBMSHisoryRecord();
    InitBMUHisoryRecord();
}


void CANThread::run()
{
    int CANBufflen_0 = 0;
    int CANBufflen_1 = 0;
    int i = 0;
    VCI_CAN_OBJ CANBuff_0[50];
    VCI_CAN_OBJ CANBuff_1[50];
    static uint64_t recvCount = 0;

    while(1)
    {
        memset(CANBuff_0, 0 ,sizeof(CANBuff_0));

        if (m_OpenTwoChannel)
        {
            memset(CANBuff_1, 0 ,sizeof(CANBuff_1));
            CANBufflen_0 = VCI_Receive(m_deviceType, m_deviceIndex, 0, CANBuff_0, 50, 100);
            CANBufflen_1 = VCI_Receive(m_deviceType, m_deviceIndex, 1, CANBuff_1, 50, 100);
        }
        else
        {
            CANBufflen_0 = VCI_Receive(m_deviceType, m_deviceIndex, m_channelIndex, CANBuff_0, 50, 100);
        }

        if ((CANBufflen_0 > 0) || (CANBufflen_1 > 0))
        {
            if (m_OpenTwoChannel)
            {
                for (i=0; i<CANBufflen_1; i++)
                {
                    ParseCANData(CANBuff_1[i]);
                    recvCount++;
                    emit RecvCount(recvCount);//发送数据给主线程
                }
            }
            for (i=0; i<CANBufflen_0; i++)
            {
                ParseCANData(CANBuff_0[i]);
                recvCount++;
                emit RecvCount(recvCount);//发送数据给主线程
            }
            if (m_OpenTwoChannel)
            {
                VCI_ClearBuffer(m_deviceType, m_deviceIndex, 0);
                VCI_ClearBuffer(m_deviceType, m_deviceIndex, 1);
            }
            else
            {
                VCI_ClearBuffer(m_deviceType, m_deviceIndex, m_channelIndex);
            }
        }

        usleep(100000);  //100ms
    }
}


void CANThread::ConnectToDatabase()
{
    m_canDB = QSqlDatabase::addDatabase("QMYSQL", "CANSQL");
    m_canDB.setHostName(g_SQLInfo.hostName);
    m_canDB.setDatabaseName(g_SQLInfo.dbName);
    m_canDB.setUserName(g_SQLInfo.userName);
    m_canDB.setPassword(g_SQLInfo.password);
    if (!m_canDB.open())
    {
#ifdef DEBUG_MODE
        qDebug() << m_canDB.lastError();
#endif
        g_DBConnectionFlag = false;
        emit ErrorInfo(QString("%1:%2").arg("CANThread::ConnectToDatabase").arg(m_canDB.lastError().text()));//发送数据给主线程
        return;
    }
}


ValueThread::ValueThread()
{
    ConnectToDatabase();
    g_CurrentTimeFlag = false;
}


void ValueThread::run()
{
    while(1)
    {
        SaveAllAverageValueToDB();
        usleep(100000);
    }
}


void ValueThread::ConnectToDatabase()
{
    m_historyDB = QSqlDatabase::addDatabase("QMYSQL", "HistorySQL");
    m_historyDB.setHostName(g_SQLInfo.hostName);
    m_historyDB.setDatabaseName(g_SQLInfo.dbName);
    m_historyDB.setUserName(g_SQLInfo.userName);
    m_historyDB.setPassword(g_SQLInfo.password);
    if (!m_historyDB.open())
    {
#ifdef DEBUG_MODE
        qDebug() << m_historyDB.lastError();
#endif
        g_DBConnectionFlag = false;
        emit ErrorInfo(QString("%1:%2").arg("ValueThread::ConnectToDatabase").arg(m_historyDB.lastError().text()));
        return;
    }
}
