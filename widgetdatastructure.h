#ifndef WIDGETDATASTRUCTURE_H
#define WIDGETDATASTRUCTURE_H

#include "ControlCAN.h"
#include <QString>
#include <QList>

#define MAX_UI_DATA_LEN 33
#define MAX_BMU_NUMBER 8
#define RECV_SIGNAL_SUCCESSFUL true
#define RECV_SIGNAL_FAIL false
#define MAX_CELL_VOLT_NUMBER 16
#define MAX_CELL_TEMP_NUMBER 4
#define MAX_SELECTED_SIGNAL_NUMBER 6


typedef struct
{
    UINT frameID;
    UCHAR UIData[MAX_UI_DATA_LEN];
}ListNode;


/* -------------- BMS信号对应UI信息结构 -------------*/
/** BMS cmd **/
typedef struct
{
    UCHAR pollGlobalInfo;
}BMSPoll;


/** 电池模组参数 **/
typedef struct
{
    float packVolt;
    float packCurr;
    float ambientTempOut;
    UCHAR SOC;
    UCHAR SOH;
    float packPwr;
}BMSCellModuleP1;

typedef struct
{
    float ambientTemp;
}BMSCellModuleP2;

typedef struct
{
    float chgCutoffVolt;
    float dischgCutoffVolt;
    float maxChgCurr;
    float maxDischgCurr;
}BMSCellModuleP3;


/** 电池基本参数 **/
typedef struct
{
    USHORT maxCellVolt;
    USHORT minCellVolt;
    UCHAR maxCVNO;
    UCHAR minCVNO;
}BMSCellBasicP1;

typedef struct
{
    float maxCellTemp;
    float minCellTemp;
    UCHAR maxCTNO;
    UCHAR minCTNO;
}BMSCellBasicP2;

typedef struct
{
    USHORT maxMoudleCV;
    USHORT minMoudleCV;
    UCHAR maxMCVNO;
    UCHAR minMCVNO;
}BMSCellBasicP3;

typedef struct
{
    float maxMoudleCT;
    float minMoudleCT;
    UCHAR maxMCTNO;
    UCHAR minMCTNO;
}BMSCellBasicP4;


/** 电池状态信息与电池故障信息 **/
//0x18FF02A0
typedef struct
{
    UCHAR forceChrgSt;
    UCHAR posiRlySt;
    UCHAR negRlySt;
    UCHAR rlySticky;
    UCHAR almSt;
    UCHAR moudleCfm;
    UCHAR moudleNum;
}BMSCellStatus;


//0x18FF04A0
typedef struct
{
    UCHAR fatalPOSC;

    UCHAR fatalBMSSensor;
    UCHAR fatalBMSAFE;
    UCHAR fatalBMSCV;
    UCHAR fatalBMSCT;
    UCHAR fatalHvcuCom;
    UCHAR fatalHvcuSensor;
}BMSCellFault;


//0x4250
typedef struct
{
    UCHAR basicStatus;
    USHORT cyclePeriod;
    UCHAR errVoltSensor;
    UCHAR errTempSensor;
    UCHAR errInnCom;
    UCHAR errChrgVoltHigh;
    UCHAR errWireInversed;
    UCHAR errRelaySticky;

    UCHAR almCellVoltLow;
    UCHAR almCellVoltHigh;
    UCHAR almPackVoltLow;
    UCHAR almPackVoltHigh;
    UCHAR almChrgTempLow;
    UCHAR almChrgTempHigh;
    UCHAR almDischrgTempLow;
    UCHAR almDischrgTempHigh;
    UCHAR almChrgCurrHigh;
    UCHAR almDischrgCurrHigh;
    UCHAR almMoudleVoltLow;
    UCHAR almMoudleVoltHigh;

    UCHAR pCellVoltLow;
    UCHAR pCellVoltHigh;
    UCHAR pPackVoltLow;
    UCHAR pPackVoltHigh;
    UCHAR pChrgTempLow;
    UCHAR pChrgTempHigh;
    UCHAR pDischrgTempLow;
    UCHAR pDischrgTempHigh;
    UCHAR pChrgCurrHigh;
    UCHAR pDischrgCurrHigh;
    UCHAR pMoudleVoltLow;
    UCHAR pMoudleVoltHigh;
}BMSCellError;


/** 指令 **/
typedef struct
{
    UCHAR chrgForbidenMark;
    UCHAR dischrgForbidenMark;
}BMSCommand1;

typedef struct
{
    UCHAR sleepCtrl;
}BMSCommand2;

typedef struct
{
    UCHAR chrgEN;
    UCHAR dischrgEN;
}BMSCommand3;

typedef struct
{
    UCHAR relayForceBreak;
}BMSCommand4;


/** 电池配置信息 **/
typedef struct
{
    USHORT cellTotalNum;
    UCHAR moudleTotalNum;
    UCHAR cellNumInMoudle;
    USHORT voltageLevel;
    UCHAR capAH;
}BMSCellConfig;


/** 版本信息 **/
typedef struct
{
    UCHAR hwVersion;
    UCHAR hwVersionSP;
    UCHAR hwVersionV;
    UCHAR hwVersionR;
    UCHAR swVersionV;
    UCHAR swVersionB;
    UCHAR swVersionS;
}BMSVersionInfo;


/* -------------- BMU信号对应UI信息结构 -------------*/
/** BMU状态 **/
typedef struct
{
    UCHAR AFESample;
    UCHAR AFEFault;
    UCHAR OWDSt;
    UCHAR msgAlive;

    UCHAR lv1CellVoltLow;
    UCHAR lv1CellVoltHigh;
    UCHAR lv1CellVoltDiff;
    UCHAR lv1MoudleVoltLow;
    UCHAR lv1MoudleVoltHigh;
    UCHAR lv1AmbientTempLow;
    UCHAR lv1AmbientTempHigh;

    UCHAR lv1ChrgTempLow;
    UCHAR lv1ChrgTempHigh;
    UCHAR lv1DischrgTempLow;
    UCHAR lv1DischrgTempHigh;

    UCHAR lv2CellVoltLow;
    UCHAR lv2CellVoltHigh;
    UCHAR lv2CellVoltDiff;
    UCHAR lv2MoudleVoltLow;
    UCHAR lv2MoudleVoltHigh;
    UCHAR lv2AmbientTempLow;
    UCHAR lv2AmbientTempHigh;

    UCHAR lv2ChrgTempLow;
    UCHAR lv2ChrgTempHigh;
    UCHAR lv2DischrgTempLow;
    UCHAR lv2DischrgTempHigh;
}BMUStatus;


/** BMU基本参数 **/
typedef struct
{
    UCHAR SOC;
    USHORT SOH;
    USHORT battCycle;
    USHORT diffCellVolt;
    float diffCellTemp;
}BMUBasicP1;

typedef struct
{
    float moudleVolt;
    float boardTemp;
}BMUBasicP2;

typedef struct
{
    USHORT maxCellVolt;
    USHORT minCellVolt;
    USHORT avgCellVolt;
    UCHAR maxCVNO;
    UCHAR minCVNO;
}BMUBasicP3;

typedef struct
{
    float maxCellTemp;
    float minCellTemp;
    float avgCellTemp;
    UCHAR maxCTNO;
    UCHAR minCTNO;
}BMUBasicP4;


/** 均衡状态 **/
typedef struct
{
    UCHAR cellBalMode;
    UCHAR cellBalSt;
    UCHAR cellInBal[MAX_CELL_VOLT_NUMBER];
}BMUBalStatus;


/** 单体电压 **/
//该格式用于对收到电压值进行读取（一个信号带四个单芯电压值）
typedef struct
{
    USHORT cellVolt[4];
}ParseBMUCellVolt;


//该格式用于对收到电压信号进行存储
typedef struct
{
    USHORT cellVolt[MAX_CELL_VOLT_NUMBER] ;
}BMUCellVolt;


/** 单体温度 **/
//该格式用于对收到温度值进行读取（一个信号带四个温度值）
typedef struct
{
    float cellTemp[4];
}ParseBMUCellTemp;


//该格式用于对收到温度信号进行存储
typedef struct
{
    float cellTemp[MAX_CELL_TEMP_NUMBER] ;
}BMUCellTemp;


/** 模组配置 **/
typedef struct
{
    USHORT cellAH ;
    USHORT cellRateVolt ;
    UCHAR cellNum;
    UCHAR tempNum;
}BMUModuleConfig;


/** BMU版本信息 **/
typedef struct
{
    UCHAR SoftVerH;
    UCHAR SoftVerL;
    UCHAR HWVerH;
    UCHAR HWVerL;
    USHORT UpdateYear;
    UCHAR UpdateMonth;
    UCHAR UpdateDay;
    UCHAR UpdateHour;
}BMUVersionInfo;


/* -------------- BMS信号标志 -------------*/
typedef struct
{
    /** BMScmd **/
    bool sig0x4200;

    /** 电池模组参数信号 **/
    bool sig0x4210;
    bool sig0x18FF02C0;
    bool sig0x4220;

    /** 电池基本参数信号 **/
    bool sig0x4230;
    bool sig0x4240;
    bool sig0x4260;
    bool sig0x4270;

    /** 电池状态与故障信息信号 **/
    bool sig0x4250;
    bool sig0x18FF02A0;
    bool sig0x18FF04A0;

    /** 指令信号 **/
    bool sig0x4280;
    bool sig0x8200;
    bool sig0x8210;
    bool sig0x8220;

    /** 电池配置信息信号 **/
    bool sig0x7320;

    /** 版本信息信号 **/
    bool sig0x7310;
}BMSSignal;


typedef struct
{
    /** BMU基本参数 **/
    bool sig0x18FF01Bx;
    bool sig0x18FF02Bx;
    bool sig0x18FF10Bx;
    bool sig0x18FF20Bx;

    /** 均衡状态 **/
    bool sig0x18FF30Bx;

    /** 模组配置 **/
    bool sig0x18FF60Bx;

    /** 软硬件版本 **/
    bool sig0x18FF70Bx;

    /** 单体电压 **/
    bool sig0x18FF40Bx;   //cell 0 - cell 3
    bool sig0x18FF41Bx;   //cell 4 - cell 7
    bool sig0x18FF42Bx;   //cell 8 - cell 11
    bool sig0x18FF43Bx;   //cell 12 - cell 15

    /** 单体温度 **/
    bool sig0x18FF50Bx;   //temp 0 - temp 3

    /** BMU状态 **/
    bool sig0x18FF00Bx;

}BMUSignal;



/* -------------- BMS整体界面信息结构 -------------*/
typedef struct
{
    BMSPoll bmsPoll;
    BMSCellModuleP1 bmsCellModuleP1;
    BMSCellModuleP2 bmsCellModuleP2;
    BMSCellModuleP3 bmsCellModuleP3;
    BMSCellBasicP1 bmsCellBaiscP1;
    BMSCellBasicP2 bmsCellBaiscP2;
    BMSCellBasicP3 bmsCellBaiscP3;
    BMSCellBasicP4 bmsCellBaiscP4;
    BMSCellStatus bmsCellStatus;
    BMSCellFault bmsCellFault;
    BMSCellError bmsCellError;
    BMSCommand1 bmsCommand1;
    BMSCommand2 bmsCommand2;
    BMSCommand3 bmsCommand3;
    BMSCommand4 bmsCommand4;
    BMSCellConfig bmsCellConfig;
    BMSVersionInfo bmsVersionInfo;
}BMSUIData;


/* -------------- BMU整体界面信息结构 -------------*/
typedef struct
{
    BMUBasicP1 bmuBasicP1;
    BMUBasicP2 bmuBasicP2;
    BMUBasicP3 bmuBasicP3;
    BMUBasicP4 bmuBasicP4;
    BMUCellVolt bmuCellVolt;
    BMUVersionInfo bmuVersionInfo;
    BMUBalStatus bmuBalStatus;
    BMUStatus bmuStatus;
    BMUModuleConfig bmuModuleConfig;
    BMUCellTemp bmuCellTemp;
}BMUUIData;


typedef struct
{
    UINT currentIndex;
    BMUSignal Signal[MAX_BMU_NUMBER];
    BMUSignal Timeout[MAX_BMU_NUMBER];   //只有定时器真的超时了才会在这里记录下面超时的信号。界面的刷新也一次为标准。否则会导致界面状态与实际状态不匹配。
}BMUData;


typedef struct
{
    QString hostName;
    QString dbName;
    QString userName;
    QString password;
}SQLInfo;


typedef struct
{
    QString parameterName;
    int BMUNumber;
    bool selectedFlag;
    QList<float> data;
}ChartData;


typedef struct
{
    QString parameterName;
    unsigned int signalID;
}SQLCondition;


#endif // WIDGETDATASTRUCTURE_H
