#ifndef HISTORYRECORDDEFINE_H
#define HISTORYRECORDDEFINE_H
#include <QList>
#include "widgetdatastructure.h"

typedef struct
{
    int pollGlobalInfo;   //重新定义并使用int类型是为了方便初始化状态值（-1）。若使用原始的类型，初始化时，无论如何都有可能与实际的状态值冲突。
}HistoryBMSPoll;


typedef struct
{
    int basicStatus;
    int errVoltSensor;
    int errTempSensor;
    int errInnCom;
    int errChrgVoltHigh;
    int errWireInversed;
    int errRelaySticky;

    int almCellVoltLow;
    int almCellVoltHigh;
    int almPackVoltLow;
    int almPackVoltHigh;
    int almChrgTempLow;
    int almChrgTempHigh;
    int almDischrgTempLow;
    int almDischrgTempHigh;
    int almChrgCurrHigh;
    int almDischrgCurrHigh;
    int almMoudleVoltLow;
    int almMoudleVoltHigh;

    int pCellVoltLow;
    int pCellVoltHigh;
    int pPackVoltLow;
    int pPackVoltHigh;
    int pChrgTempLow;
    int pChrgTempHigh;
    int pDischrgTempLow;
    int pDischrgTempHigh;
    int pChrgCurrHigh;
    int pDischrgCurrHigh;
    int pMoudleVoltLow;
    int pMoudleVoltHigh;
}HistoryBMSCellError;


typedef struct
{
    int forceChrgSt;
    int posiRlySt;
    int negRlySt;
    int rlySticky;
    int almSt;
}HistoryBMSCellStatus;


typedef struct
{
    int fatalPOSC;

    int fatalBMSSensor;
    int fatalBMSAFE;
    int fatalBMSCV;
    int fatalBMSCT;
    int fatalHvcuCom;
    int fatalHvcuSensor;
}HistoryBMSCellFault;


typedef struct
{
    int chrgForbidenMark;
    int dischrgForbidenMark;
}HistoryBMSCommand1;


typedef struct
{
    int sleepCtrl;
}HistoryBMSCommand2;


typedef struct
{
    int chrgEN;
    int dischrgEN;
}HistoryBMSCommand3;


typedef struct
{
    int relayForceBreak;
}HistoryBMSCommand4;


typedef struct
{
    int cellAH ;
    int cellRateVolt ;
    int cellNum;
    int tempNum;
}HistoryBMUModuleConfig;


typedef struct
{
    int AFESample;
    int AFEFault;
    int OWDSt;

    int lv1CellVoltLow;
    int lv1CellVoltHigh;
    int lv1CellVoltDiff;
    int lv1MoudleVoltLow;
    int lv1MoudleVoltHigh;
    int lv1AmbientTempLow;
    int lv1AmbientTempHigh;

    int lv1ChrgTempLow;
    int lv1ChrgTempHigh;
    int lv1DischrgTempLow;
    int lv1DischrgTempHigh;

    int lv2CellVoltLow;
    int lv2CellVoltHigh;
    int lv2CellVoltDiff;
    int lv2MoudleVoltLow;
    int lv2MoudleVoltHigh;
    int lv2AmbientTempLow;
    int lv2AmbientTempHigh;

    int lv2ChrgTempLow;
    int lv2ChrgTempHigh;
    int lv2DischrgTempLow;
    int lv2DischrgTempHigh;
}HistoryBMUStatus;


typedef struct
{
    int cellBalMode;
    int cellBalSt;
    int cellInBal[MAX_CELL_VOLT_NUMBER];
}HistoryBMUBalStatus;


typedef struct
{
    int bmsMaxCVNO;
    int bmsMinCVNO;
    int bmsMaxCTNO;
    int bmsMinCTNO;
    int maxMCVNO;
    int minMCVNO;
    int maxMCTNO;
    int minMCTNO;

    HistoryBMSPoll globalInfo;
    HistoryBMSCellError errorStatus;
    HistoryBMSCellStatus cellStatus;
    HistoryBMSCellFault cellFault;
    HistoryBMSCommand1 command1;
    HistoryBMSCommand2 command2;
    HistoryBMSCommand3 command3;
    HistoryBMSCommand4 command4;
}BMSHistoryStatus;


typedef struct
{
    int bmuMaxCVNO;
    int bmuMinCVNO;
    int bmuMaxCTNO;
    int bmuMinCTNO;

    HistoryBMUModuleConfig moduleConfig;
    HistoryBMUStatus status;
    HistoryBMUBalStatus balStatus;
}BMUHistoryStatus;


typedef struct
{
    UINT signalID;
    QString parName;
    float value;
}HistoryListNode;


typedef struct
{
    UINT time;
    float value;
}HistoryChartNode;


typedef struct
{
    /** BMS **/
    //0x4210
    QList<HistoryListNode> packVoltList;
    QList<HistoryListNode> packCurrList;
    QList<HistoryListNode> ambientTempOutList;
    QList<HistoryListNode> bmsSocList;
    QList<HistoryListNode> packPwrList;

    //0x18FF02C0
    QList<HistoryListNode> ambientTempList;

    //0x4220
    QList<HistoryListNode> maxChgCurrList;
    QList<HistoryListNode> maxDischgCurrList;

    //0x4230
    QList<HistoryListNode> bmsMaxCellVoltList;
    QList<HistoryListNode> bmsMinCellVoltList;

    //0x4240
    QList<HistoryListNode> maxCellTempList;
    QList<HistoryListNode> minCellTempList;

    //0x4260
    QList<HistoryListNode> maxMoudleCVList;
    QList<HistoryListNode> minMoudleCVList;

    //0x4270
    QList<HistoryListNode> maxMoudleCTList;
    QList<HistoryListNode> minMoudleCTList;

    /** BMU **/
    //0x18FF01Bx
    QList<HistoryListNode> bmuSocList;
    QList<HistoryListNode> diffCellVoltList;
    QList<HistoryListNode> diffCellTempList;

    //0x18FF02Bx
    QList<HistoryListNode> moudleVoltList;
    QList<HistoryListNode> boardTempList;

    //0x18FF10Bx
    QList<HistoryListNode> bmuMaxCellVoltList;
    QList<HistoryListNode> bmuMinCellVoltList;
    QList<HistoryListNode> avgCellVoltList;

    //0x18FF20Bx
    QList<HistoryListNode> bmuMaxCellTempList;
    QList<HistoryListNode> bmuMinCellTempList;
    QList<HistoryListNode> avgCellTempList;

    //0x18FF40Bx - 0x18FF4FBx
    QList<HistoryListNode> cellVolt0;
    QList<HistoryListNode> cellVolt1;
    QList<HistoryListNode> cellVolt2;
    QList<HistoryListNode> cellVolt3;
    QList<HistoryListNode> cellVolt4;
    QList<HistoryListNode> cellVolt5;
    QList<HistoryListNode> cellVolt6;
    QList<HistoryListNode> cellVolt7;
    QList<HistoryListNode> cellVolt8;
    QList<HistoryListNode> cellVolt9;
    QList<HistoryListNode> cellVolt10;
    QList<HistoryListNode> cellVolt11;
    QList<HistoryListNode> cellVolt12;
    QList<HistoryListNode> cellVolt13;
    QList<HistoryListNode> cellVolt14;
    QList<HistoryListNode> cellVolt15;

    //0x18FF50Bx - 0x18FF5FBx
    QList<HistoryListNode> cellTemp0;
    QList<HistoryListNode> cellTemp1;
    QList<HistoryListNode> cellTemp2;
    QList<HistoryListNode> cellTemp3;
}HistoryValue;


#endif // HISTORYRECORDDEFINE_H
