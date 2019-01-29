#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include <QSqlDatabase>
#include <QFile>
#include "ControlCAN.h"
#include "widgetdatastructure.h"
#include "historyrecorddefine.h"

void BMSInfoToChart(VCI_CAN_OBJ srcData);
void BMSErrorStatusToChart();
void BMSCellStatusToChart();
void BMSFaultToChart();
void BMUInfoToChart(VCI_CAN_OBJ srcData);
void BMUStatusToChart(VCI_CAN_OBJ srcData);
void BMUBalStatusToChart(VCI_CAN_OBJ srcData);
void GetSelectedData(QString parameter, int bmuNumber, float data);

void GetBMSCellModelData(VCI_CAN_OBJ data);
void GetBMSBasicData(VCI_CAN_OBJ data);
void GetBMSCellConfig(VCI_CAN_OBJ data);
void GetBMSCommand(VCI_CAN_OBJ data);
void GetBMSVersion(VCI_CAN_OBJ data);
void GetBMSErrorStatus(VCI_CAN_OBJ data);
void GetBMSCellStatus(VCI_CAN_OBJ data);
void GetBMSFaultStatus(VCI_CAN_OBJ data);
void GetBMUBasicData(VCI_CAN_OBJ data);
void GetBMUModuleConfig(VCI_CAN_OBJ data);
void GetBMUVersion(VCI_CAN_OBJ data);
void GetBMUCellVolt(VCI_CAN_OBJ data);
void GetBMUCellTemp(VCI_CAN_OBJ data);
void GetBMUStatus(VCI_CAN_OBJ data);
void GetBMUBalStatus(VCI_CAN_OBJ data);

void InitBMSHisoryRecord();
void InitBMUHisoryRecord();


class CANThread : public QThread
{
    Q_OBJECT

public:
    CANThread(int deviceType, int deviceIndex, int channelIndex, bool openAll);

    void run();

    int m_deviceType;
    int m_channelIndex;
    int m_deviceIndex;
    bool m_OpenTwoChannel;
    QSqlDatabase m_canDB;

    void ParseCANData(VCI_CAN_OBJ srcData);
    void GetBMUData(VCI_CAN_OBJ data);
    void BMSInfoToDB(UINT id);
    void BMSErrorToDB(UINT id);
    void BMSStatusToDB(UINT id);
    void BMSFaultToDB(UINT id);

    void BMUInfoToDB(UINT id);
    void BMUStatusToDB(UINT id);
    void BMUBalStatusToDB(UINT id);
    void ConnectToDatabase();
    void SaveToRecentValue(unsigned int id, const char *pName, float value, int type);
    void SaveStatusToHistoryRecord(unsigned int id, QString name, float value, int type);
    void SaveBMSCellModelDataToHistoryBuffer(UINT id);
    void SaveBMSCellBasicParToHistoryBuffer(UINT id);
    void SaveBMSCommandToHistoryBuffer(UINT id);
    void SaveBMSCellErrorToHistoryBuffer(UINT id);
    void SaveBMSCellStatusToHistoryBuffer(UINT id);
    void SaveBMSCellFaultToHistoryBuffer(UINT id);
    void SaveBMUBasicParToHistoryBuffer(UINT id);
    void SaveBMUModuleConfigToHistoryBuffer(UINT id);
    void SaveBMUStatusToHistoryBuffer(UINT id);
    void SaveBMUBalStatusToHistoryBuffer(UINT id);
    void SaveBMUCellVoltToHistoryBuffer(UINT id);
    void SaveBMUCellTempToHistoryBuffer(UINT id);

signals:
    void RecvCount(uint64_t count);   //向主线程发送收到的数据
    void ErrorInfo(QString errorstirng);
};


class ValueThread : public QThread
{
    Q_OBJECT

public:
    ValueThread();
    QSqlDatabase m_historyDB;

    void run();
    void ConnectToDatabase();
    void GetCurrentTime(QString *timestamp, UINT *unixtime);
    void AverageValueToDB(QList<HistoryListNode> *list, UINT time);
    void SaveAllAverageValueToDB();
signals:
    void ErrorInfo(QString errorstirng);
};



#endif // WORKTHREAD_H
