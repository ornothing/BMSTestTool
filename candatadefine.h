#ifndef CANDATADEFINE_H
#define CANDATADEFINE_H

#include <stdint.h>
#include "ControlCAN.h"


/* -------------- BMS信息解析 -------------*/
//0x4200
typedef struct
{
    UCHAR pollGlobalInfo;
}CANData_BMSPoll;


/** 电池模组参数 **/
//0x4210
typedef struct
{
    short packVolt;
    short packCurr;
    USHORT ambientTempOut;
    UCHAR SOC;
    UCHAR SOH;
}CANData_BMSCellModule1;


//0x18FF02C0
typedef struct
{
    USHORT Invalid0;
    USHORT ambientTemp;
}CANData_BMSCellModule2;


//0x4220
typedef struct
{
    USHORT chgCutoffVolt;
    USHORT dischgCutoffVolt;
    USHORT maxChgCurr;
    USHORT maxDischgCurr;
}CANData_BMSCellModule3;


/** 电池基本参数 **/
//0x4230
typedef struct
{
    USHORT maxCellVolt;
    USHORT minCellVolt;
    USHORT maxCVNO;
    USHORT minCVNO;
}CANData_BMSCellBasic1;


//0x4240
typedef struct
{
    USHORT maxCellTemp;
    USHORT minCellTemp;
    USHORT maxCTNO;
    USHORT minCTNO;
}CANData_BMSCellBasic2;


//0x4260
typedef struct
{
    USHORT maxMoudleCV;
    USHORT minMoudleCV;
    USHORT maxMCVNO;
    USHORT minMCVNO;
}CANData_BMSCellBasic3;


//0x4270
typedef struct
{
    USHORT maxMoudleCT;
    USHORT minMoudleCT;
    USHORT maxMCTNO;
    USHORT minMCTNO;
}CANData_BMSCellBasic4;


/** 电池状态信息与电池故障信息 **/
//0x18FF02A0
union CANData_BMSCellStatus
{
    uint64_t data;
    struct
    {
        uint64_t Invalid0          :4;
        uint64_t forceChrgSt       :4;
        uint64_t posiRlySt         :1;
        uint64_t negRlySt          :1;
        uint64_t Invalid2          :2;
        uint64_t rlySticky         :4;
        uint64_t almSt             :4;
        uint64_t Invalid3          :4;
        uint64_t moudleCfm         :1;
        uint64_t moudleNum         :7;
        uint64_t Invalid4          :32;
    }bit;
};


//0x18FF04A0
union CANData_BMSCellFault
{
    uint64_t data;
    struct
    {
        uint64_t Invalid0          :32;
        uint64_t fatalPOSC         :1;
        uint64_t Invalid1          :1;
        uint64_t fatalBMSSensor    :1;
        uint64_t fatalBMSAFE       :1;
        uint64_t fatalBMSCV        :1;
        uint64_t fatalBMSCT        :1;
        uint64_t fatalHvcuCom      :1;
        uint64_t Invalid2          :1;
        uint64_t Invalid3          :7;
        uint64_t fatalHvcuSensor   :1;
        uint64_t Invalid4          :16;
    }bit;
};


//0x4250
union CANData_BMSCellError
{
    uint64_t data;
    struct
    {
        uint64_t basicStatus       :8;
        uint64_t cyclePeriod       :16;
        uint64_t errVoltSensor     :1;
        uint64_t errTempSensor     :1;
        uint64_t errInnCom         :1;
        uint64_t errChrgVoltHigh   :1;
        uint64_t errWireInversed   :1;
        uint64_t errRelaySticky    :1;
        uint64_t Invalid0          :2;
        uint64_t almCellVoltLow    :1;
        uint64_t almCellVoltHigh   :1;
        uint64_t almPackVoltLow    :1;
        uint64_t almPackVoltHigh   :1;
        uint64_t almChrgTempLow    :1;
        uint64_t almChrgTempHigh   :1;
        uint64_t almDischrgTempLow :1;
        uint64_t almDischrgTempHigh:1;
        uint64_t almChrgCurrHigh   :1;
        uint64_t almDischrgCurrHigh:1;
        uint64_t almMoudleVoltLow  :1;
        uint64_t almMoudleVoltHigh :1;
        uint64_t Invalid1          :4;
        uint64_t pCellVoltLow      :1;
        uint64_t pCellVoltHigh     :1;
        uint64_t pPackVoltLow      :1;
        uint64_t pPackVoltHigh     :1;
        uint64_t pChrgTempLow      :1;
        uint64_t pChrgTempHigh     :1;
        uint64_t pDischrgTempLow   :1;
        uint64_t pDischrgTempHigh  :1;
        uint64_t pChrgCurrHigh     :1;
        uint64_t pDischrgCurrHigh  :1;
        uint64_t pMoudleVoltLow    :1;
        uint64_t pMoudleVoltHigh   :1;
        uint64_t Invalid2          :4;
    }bit;
};


/** 指令 **/
//0x4280
typedef struct
{
    UCHAR chrgForbidenMark;
    UCHAR dischrgForbidenMark;
}CANData_BMSCommand1;


//0x8200
typedef struct
{
    UCHAR sleepCtrl;
}CANData_BMSCommand2;


//0x8210
typedef struct
{
    UCHAR chrgEN;
    UCHAR dischrgEN;
}CANData_BMSCommand3;


//0x8220
typedef struct
{
    UCHAR relayForceBreak;
}CANData_BMSCommand4;


/** 电池配置信息 **/
//0x7320
typedef struct
{
    USHORT cellTotalNum;
    UCHAR moudleTotalNum;
    UCHAR cellNumInMoudle;
    USHORT voltageLevel;
    UCHAR capAH;
}CANData_BMSCellConfig;


/** 版本信息 **/
//0x7310
typedef struct
{
    UCHAR hwVersion;
    UCHAR hwVersionSP;
    UCHAR hwVersionV;
    UCHAR hwVersionR;
    UCHAR swVersionV;
    UCHAR swVersionB;
    UCHAR swVersionS;
}CANData_BMSVersionInfo;


/* -------------- BMU信息解析 -------------*/
/** BMU状态 **/
//0x18FF00Bx
union CANData_BMUStatus
{
    uint64_t data;
    struct
    {
        uint64_t AFESample         :2;
        uint64_t AFEFault          :2;
        uint64_t OWDSt             :4;
        uint64_t msgAlive          :8;

        uint64_t lv1CellVoltLow    :1;
        uint64_t lv1CellVoltHigh   :1;
        uint64_t lv1CellVoltDiff   :1;
        uint64_t lv1MoudleVoltLow  :1;
        uint64_t lv1MoudleVoltHigh :1;
        uint64_t lv1AmbientTempLow :1;
        uint64_t lv1AmbientTempHigh:1;
        uint64_t Invalid0          :1;

        uint64_t lv1ChrgTempLow    :1;
        uint64_t lv1ChrgTempHigh   :1;
        uint64_t lv1DischrgTempLow :1;
        uint64_t lv1DischrgTempHigh:1;
        uint64_t Invalid1          :4;

        uint64_t lv2CellVoltLow    :1;
        uint64_t lv2CellVoltHigh   :1;
        uint64_t lv2CellVoltDiff   :1;
        uint64_t lv2MoudleVoltLow  :1;
        uint64_t lv2MoudleVoltHigh :1;
        uint64_t lv2AmbientTempLow :1;
        uint64_t lv2AmbientTempHigh:1;
        uint64_t Invalid2          :1;

        uint64_t lv2ChrgTempLow    :1;
        uint64_t lv2ChrgTempHigh   :1;
        uint64_t lv2DischrgTempLow :1;
        uint64_t lv2DischrgTempHigh:1;
        uint64_t Invalid3          :4;
        uint64_t Invalid4          :16;
    }bit;
};


/** BMU基本参数 **/
//0x18FF01Bx
typedef struct
{
    UCHAR SOC;
    UCHAR SOH;
    USHORT battCycle;
    USHORT diffCellVolt;
    USHORT diffCellTemp;
}CANData_BMUBasicP1;


//0x18FF02Bx
typedef struct
{
    USHORT moudleVolt;
    USHORT boardTemp;
}CANData_BMUBasicP2;


//0x18FF10Bx
typedef struct
{
    USHORT maxCellVolt;
    USHORT minCellVolt;
    USHORT avgCellVolt;
    UCHAR maxCVNO;
    UCHAR minCVNO;
}CANData_BMUBasicP3;


//0x18FF20Bx
typedef struct
{
    USHORT maxCellTemp;
    USHORT minCellTemp;
    USHORT avgCellTemp;
    UCHAR maxCTNO;
    UCHAR minCTNO;
}CANData_BMUBasicP4;


/** 均衡状态 **/
//0x18FF30Bx
union CANData_BMUBalStatus
{
    uint64_t data;
    struct
    {
        uint64_t cellBalMode       :8;
        uint64_t cellBalSt         :8;

        uint64_t cellInBal0        :1;
        uint64_t cellInBal1        :1;
        uint64_t cellInBal2        :1;
        uint64_t cellInBal3        :1;
        uint64_t cellInBal4        :1;
        uint64_t cellInBal5        :1;
        uint64_t cellInBal6        :1;
        uint64_t cellInBal7        :1;

        uint64_t cellInBal8        :1;
        uint64_t cellInBal9        :1;
        uint64_t cellInBal10       :1;
        uint64_t cellInBal11       :1;
        uint64_t cellInBal12       :1;
        uint64_t cellInBal13       :1;
        uint64_t cellInBal14       :1;
        uint64_t cellInBal15       :1;

        uint64_t Invalid0          :32;
    }bit;
};


/** 单体电压 **/
//0x18FF40Bx - 0x18FF4FBx
typedef struct
{
    USHORT cellVolt[4];
}CANData_BMUCellVolt;


/** 单体温度 **/
//0x18FF50Bx - 0x18FF5FBx
typedef struct
{
    USHORT cellTemp[4];
}CANData_BMUCellTemp;


/** 模组配置 **/
//0x18FF60Bx
typedef struct
{
    USHORT cellAH ;
    USHORT cellRateVolt ;
    UCHAR cellNum;
    UCHAR tempNum;
}CANData_BMUModuleConfig;


/** BMU版本信息 **/
//0x18FF70Bx
typedef struct
{
    UCHAR SoftVerH;
    UCHAR SoftVerL;
    UCHAR HWVerH;
    UCHAR HWVerL;
    UCHAR UpdateYear;
    UCHAR UpdateMonth;
    UCHAR UpdateDay;
    UCHAR UpdateHour;
}CANData_BMUVersionInfo;



#endif // CANDATADEFINE_H
