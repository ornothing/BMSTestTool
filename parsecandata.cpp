#include <QList>
#include "WorkThread.h"
#include "candatadefine.h"
#include "historyrecorddefine.h"

BMSUIData g_GetCANBMSData;
BMUUIData g_GetCANBMUData[MAX_BMU_NUMBER];
QList<UINT> g_BMSRecvedList;
QList<UINT> g_BMURecvedList;
QList<UINT> g_BMSVersionList;

extern bool g_DBConnectionFlag;

void CANThread::ParseCANData(VCI_CAN_OBJ srcData)
{
    switch (srcData.ID)
    {
    //BMS
    /** 电池模组参数 **/
    case 0x4200:
    case 0x4210:
    case 0x18FF02C0:
    case 0x4220:
        GetBMSCellModelData(srcData);   //解析数据并保存
        g_BMSRecvedList.append(srcData.ID);   //更新UI
        BMSInfoToChart(srcData);   //更新图表
        if (g_DBConnectionFlag)
        {
            BMSInfoToDB(srcData.ID);   //写数据库(状态数据只有在变化的情况下才会写入数据库)
            SaveBMSCellModelDataToHistoryBuffer(srcData.ID);   //将值类型数据存放的历史缓存中，状态类型数据写入数据库并保存。
        }
        break;

    /** 电池基本参数 **/
    case 0x4230:
    case 0x4240:
    case 0x4260:
    case 0x4270:
        GetBMSBasicData(srcData);
        g_BMSRecvedList.append(srcData.ID);
        BMSInfoToChart(srcData);
        if (g_DBConnectionFlag)
        {
            BMSInfoToDB(srcData.ID);
            SaveBMSCellBasicParToHistoryBuffer(srcData.ID);
        }
        break;

    /** 电池配置信息 **/
    case 0x7320:
        GetBMSCellConfig(srcData);
        g_BMSRecvedList.append(srcData.ID);
        break;

    /** 指令 **/
    case 0x4280:
    case 0x8200:
    case 0x8210:
    case 0x8220:
        GetBMSCommand(srcData);
        g_BMSRecvedList.append(srcData.ID);
        BMSInfoToChart(srcData);
        if (g_DBConnectionFlag)
        {
            BMSInfoToDB(srcData.ID);
            SaveBMSCommandToHistoryBuffer(srcData.ID);
        }
        break;

    /** BMS版本信息 **/
    case 0x7310:
        GetBMSVersion(srcData);
//        g_BMSRecvedList.append(srcData.ID);
        g_BMSVersionList.append(srcData.ID);
        break;

    /** 电池状态信息与电池故障信息 **/
    case 0x4250:
        GetBMSErrorStatus(srcData);
        g_BMSRecvedList.append(srcData.ID);
        BMSErrorStatusToChart();
        if (g_DBConnectionFlag)
        {
            BMSErrorToDB(srcData.ID);
            SaveBMSCellErrorToHistoryBuffer(srcData.ID);
        }
        break;

    case 0x18FF02A0:
        GetBMSCellStatus(srcData);
        g_BMSRecvedList.append(srcData.ID);
        BMSCellStatusToChart();
        if (g_DBConnectionFlag)
        {
            BMSStatusToDB(srcData.ID);
            SaveBMSCellStatusToHistoryBuffer(srcData.ID);
        }
        break;

    case 0x18FF04A0:
        GetBMSFaultStatus(srcData);
        g_BMSRecvedList.append(srcData.ID);
        BMSFaultToChart();
        if (g_DBConnectionFlag)
        {
            BMSFaultToDB(srcData.ID);
            SaveBMSCellFaultToHistoryBuffer(srcData.ID);
        }
        break;

    default:
        GetBMUData(srcData);
        break;
    }
}


void CANThread::GetBMUData(VCI_CAN_OBJ data)
{
    UINT id = 0;
    id = data.ID >> 4;
    int index = 0;
    index = data.ID & 0x0000000f;

    if (index < MAX_BMU_NUMBER)   //设备索引小于8，否则会导致后面的程序错误。
    {
        switch(id)
        {
        /** BMU基本参数 **/
        case 0x18FF01B:
        case 0x18FF02B:
        case 0x18FF10B:
        case 0x18FF20B:
            GetBMUBasicData(data);
            g_BMURecvedList.append(data.ID);
            BMUInfoToChart(data);
            if (g_DBConnectionFlag)
            {
                BMUInfoToDB(data.ID);
                SaveBMUBasicParToHistoryBuffer(data.ID);
            }
            break;

            /** 单体电压 **/
        case 0x18FF40B:
        case 0x18FF41B:
        case 0x18FF42B:
        case 0x18FF43B:
            GetBMUCellVolt(data);
            g_BMURecvedList.append(data.ID);
            BMUInfoToChart(data);
            if (g_DBConnectionFlag)
            {
                BMUInfoToDB(data.ID);
                SaveBMUCellVoltToHistoryBuffer(data.ID);
            }
            break;

            /** 单体温度 **/
        case 0x18FF50B:
            GetBMUCellTemp(data);
            g_BMURecvedList.append(data.ID);
            BMUInfoToChart(data);
            if (g_DBConnectionFlag)
            {
                BMUInfoToDB(data.ID);
                SaveBMUCellTempToHistoryBuffer(data.ID);
            }
            break;

            /** BMU状态 **/
        case 0x18FF00B:
            GetBMUStatus(data);
            g_BMURecvedList.append(data.ID);
            BMUStatusToChart(data);
            if (g_DBConnectionFlag)
            {
                BMUStatusToDB(data.ID);
                SaveBMUStatusToHistoryBuffer(data.ID);
            }
            break;

            /** 均衡状态 **/
        case 0x18FF30B:
            GetBMUBalStatus(data);
            g_BMURecvedList.append(data.ID);
            BMUBalStatusToChart(data);
            if (g_DBConnectionFlag)
            {
                BMUBalStatusToDB(data.ID);
                SaveBMUBalStatusToHistoryBuffer(data.ID);
            }
            break;

            /** 模组配置 **/
        case 0x18FF60B:
            GetBMUModuleConfig(data);
            g_BMURecvedList.append(data.ID);
            BMUInfoToChart(data);
            if (g_DBConnectionFlag)
            {
                BMUInfoToDB(data.ID);
                SaveBMUModuleConfigToHistoryBuffer(data.ID);
            }
            break;

            /** 软硬件版本 **/
        case 0x18FF70B:
            GetBMUVersion(data);
            g_BMURecvedList.append(data.ID);
            break;

        default:
            break;
        }
    }
}


void GetBMUBalStatus(VCI_CAN_OBJ data)
{
    CANData_BMUBalStatus *p = NULL;
    int index = 0;
    index = data.ID & 0x0000000f;

    p = (CANData_BMUBalStatus *)data.Data;
    g_GetCANBMUData[index].bmuBalStatus.cellBalMode = p->bit.cellBalMode;
    g_GetCANBMUData[index].bmuBalStatus.cellBalSt = p->bit.cellBalSt;

    g_GetCANBMUData[index].bmuBalStatus.cellInBal[0] = p->bit.cellInBal0;
    g_GetCANBMUData[index].bmuBalStatus.cellInBal[1] = p->bit.cellInBal1;
    g_GetCANBMUData[index].bmuBalStatus.cellInBal[2] = p->bit.cellInBal2;
    g_GetCANBMUData[index].bmuBalStatus.cellInBal[3] = p->bit.cellInBal3;
    g_GetCANBMUData[index].bmuBalStatus.cellInBal[4] = p->bit.cellInBal4;
    g_GetCANBMUData[index].bmuBalStatus.cellInBal[5] = p->bit.cellInBal5;
    g_GetCANBMUData[index].bmuBalStatus.cellInBal[6] = p->bit.cellInBal6;
    g_GetCANBMUData[index].bmuBalStatus.cellInBal[7] = p->bit.cellInBal7;
    g_GetCANBMUData[index].bmuBalStatus.cellInBal[8] = p->bit.cellInBal8;
    g_GetCANBMUData[index].bmuBalStatus.cellInBal[9] = p->bit.cellInBal9;
    g_GetCANBMUData[index].bmuBalStatus.cellInBal[10] = p->bit.cellInBal10;
    g_GetCANBMUData[index].bmuBalStatus.cellInBal[11] = p->bit.cellInBal11;
    g_GetCANBMUData[index].bmuBalStatus.cellInBal[12] = p->bit.cellInBal12;
    g_GetCANBMUData[index].bmuBalStatus.cellInBal[13] = p->bit.cellInBal13;
    g_GetCANBMUData[index].bmuBalStatus.cellInBal[14] = p->bit.cellInBal14;
    g_GetCANBMUData[index].bmuBalStatus.cellInBal[15] = p->bit.cellInBal15;
}


void GetBMUStatus(VCI_CAN_OBJ data)
{
    CANData_BMUStatus *p = NULL;
    int index = 0;
    index = data.ID & 0x0000000f;

    p = (CANData_BMUStatus *)data.Data;
    g_GetCANBMUData[index].bmuStatus.AFESample = p->bit.AFESample;
    g_GetCANBMUData[index].bmuStatus.AFEFault = p->bit.AFEFault;
    g_GetCANBMUData[index].bmuStatus.OWDSt = p->bit.OWDSt;
    g_GetCANBMUData[index].bmuStatus.msgAlive = p->bit.msgAlive;

    g_GetCANBMUData[index].bmuStatus.lv1CellVoltLow = p->bit.lv1CellVoltLow;
    g_GetCANBMUData[index].bmuStatus.lv1CellVoltHigh = p->bit.lv1CellVoltHigh;
    g_GetCANBMUData[index].bmuStatus.lv1CellVoltDiff = p->bit.lv1CellVoltDiff;
    g_GetCANBMUData[index].bmuStatus.lv1MoudleVoltLow = p->bit.lv1MoudleVoltLow;
    g_GetCANBMUData[index].bmuStatus.lv1MoudleVoltHigh = p->bit.lv1MoudleVoltHigh;
    g_GetCANBMUData[index].bmuStatus.lv1AmbientTempLow = p->bit.lv1AmbientTempLow;
    g_GetCANBMUData[index].bmuStatus.lv1AmbientTempHigh = p->bit.lv1AmbientTempHigh;

    g_GetCANBMUData[index].bmuStatus.lv1ChrgTempLow = p->bit.lv1ChrgTempLow;
    g_GetCANBMUData[index].bmuStatus.lv1ChrgTempHigh = p->bit.lv1ChrgTempHigh;
    g_GetCANBMUData[index].bmuStatus.lv1DischrgTempLow = p->bit.lv1DischrgTempLow;
    g_GetCANBMUData[index].bmuStatus.lv1DischrgTempHigh = p->bit.lv1DischrgTempHigh;

    g_GetCANBMUData[index].bmuStatus.lv2CellVoltLow = p->bit.lv2CellVoltLow;
    g_GetCANBMUData[index].bmuStatus.lv2CellVoltHigh = p->bit.lv2CellVoltHigh;
    g_GetCANBMUData[index].bmuStatus.lv2CellVoltDiff = p->bit.lv2CellVoltDiff;
    g_GetCANBMUData[index].bmuStatus.lv2MoudleVoltLow = p->bit.lv2MoudleVoltLow;
    g_GetCANBMUData[index].bmuStatus.lv2MoudleVoltHigh = p->bit.lv2MoudleVoltHigh;
    g_GetCANBMUData[index].bmuStatus.lv2AmbientTempLow = p->bit.lv2AmbientTempLow;
    g_GetCANBMUData[index].bmuStatus.lv2AmbientTempHigh = p->bit.lv2AmbientTempHigh;

    g_GetCANBMUData[index].bmuStatus.lv2ChrgTempLow = p->bit.lv2ChrgTempLow;
    g_GetCANBMUData[index].bmuStatus.lv2ChrgTempHigh = p->bit.lv2ChrgTempHigh;
    g_GetCANBMUData[index].bmuStatus.lv2DischrgTempLow = p->bit.lv2DischrgTempLow;
    g_GetCANBMUData[index].bmuStatus.lv2DischrgTempHigh = p->bit.lv2DischrgTempHigh;
}


void GetBMUCellTemp(VCI_CAN_OBJ data)
{
    CANData_BMUCellTemp *p = NULL;
    int index = 0;
    index = data.ID & 0x0000000f;

    p = (CANData_BMUCellTemp *)data.Data;
    g_GetCANBMUData[index].bmuCellTemp.cellTemp[0] = (p->cellTemp[0]) * 0.1;
    g_GetCANBMUData[index].bmuCellTemp.cellTemp[1] = p->cellTemp[1] * 0.1;
    g_GetCANBMUData[index].bmuCellTemp.cellTemp[2] = p->cellTemp[2] * 0.1;
    g_GetCANBMUData[index].bmuCellTemp.cellTemp[3] = p->cellTemp[3] * 0.1;
}


void GetBMUCellVolt(VCI_CAN_OBJ data)
{
    CANData_BMUCellVolt *p = NULL;

    int index = 0;
    index = data.ID & 0x0000000f;
    UINT id = 0;
    id = data.ID >> 4;

    switch (id)
    {
    case 0x18FF40B:
        p = (CANData_BMUCellVolt *)data.Data;
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[0] = p->cellVolt[0];
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[1] = p->cellVolt[1];
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[2] = p->cellVolt[2];
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[3] = p->cellVolt[3];
        break;

    case 0x18FF41B:
        p = (CANData_BMUCellVolt *)data.Data;
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[4] = p->cellVolt[0];
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[5] = p->cellVolt[1];
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[6] = p->cellVolt[2];
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[7] = p->cellVolt[3];
        break;

    case 0x18FF42B:
        p = (CANData_BMUCellVolt *)data.Data;
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[8] = p->cellVolt[0];
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[9] = p->cellVolt[1];
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[10] = p->cellVolt[2];
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[11] = p->cellVolt[3];
        break;

    case 0x18FF43B:
        p = (CANData_BMUCellVolt *)data.Data;
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[12] = p->cellVolt[0];
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[13] = p->cellVolt[1];
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[14] = p->cellVolt[2];
        g_GetCANBMUData[index].bmuCellVolt.cellVolt[15] = p->cellVolt[3];
        break;

    default:
        break;
    }
}


void GetBMUVersion(VCI_CAN_OBJ data)
{
    CANData_BMUVersionInfo *p = NULL;
    int index = 0;
    index = data.ID & 0x0000000f;

    p = (CANData_BMUVersionInfo *)data.Data;
    g_GetCANBMUData[index].bmuVersionInfo.SoftVerH = p->SoftVerH;
    g_GetCANBMUData[index].bmuVersionInfo.SoftVerL = p->SoftVerL;
    g_GetCANBMUData[index].bmuVersionInfo.HWVerH = p->HWVerH;
    g_GetCANBMUData[index].bmuVersionInfo.HWVerL = p->HWVerL;
    g_GetCANBMUData[index].bmuVersionInfo.UpdateYear = p->UpdateYear + 2000;
    g_GetCANBMUData[index].bmuVersionInfo.UpdateMonth = p->UpdateMonth;
    g_GetCANBMUData[index].bmuVersionInfo.UpdateDay = p->UpdateDay;
    g_GetCANBMUData[index].bmuVersionInfo.UpdateHour = p->UpdateHour;
}


void GetBMUModuleConfig(VCI_CAN_OBJ data)
{
    CANData_BMUModuleConfig *p = NULL;
    int index = 0;
    index = data.ID & 0x0000000f;

    p = (CANData_BMUModuleConfig *)data.Data;
    g_GetCANBMUData[index].bmuModuleConfig.cellAH = p->cellAH;
    g_GetCANBMUData[index].bmuModuleConfig.cellRateVolt = p->cellRateVolt;
    g_GetCANBMUData[index].bmuModuleConfig.cellNum = p->cellNum;
    g_GetCANBMUData[index].bmuModuleConfig.tempNum = p->tempNum;
}


void GetBMUBasicData(VCI_CAN_OBJ data)
{
    CANData_BMUBasicP1 *p1 = NULL;
    CANData_BMUBasicP2 *p2= NULL;
    CANData_BMUBasicP3 *p3 = NULL;
    CANData_BMUBasicP4 *p4 = NULL;

    int index = 0;
    index = data.ID & 0x0000000f;
    UINT id = 0;
    id = data.ID >> 4;

    switch (id)
    {
    /** BMU基本参数 **/
    case 0x18FF01B:
        p1 = (CANData_BMUBasicP1 *)data.Data;
        g_GetCANBMUData[index].bmuBasicP1.SOC = p1->SOC;
        g_GetCANBMUData[index].bmuBasicP1.SOH = (p1->SOH) * 100;
        g_GetCANBMUData[index].bmuBasicP1.battCycle = p1->battCycle;
        g_GetCANBMUData[index].bmuBasicP1.diffCellVolt = p1->diffCellVolt;
        g_GetCANBMUData[index].bmuBasicP1.diffCellTemp = (p1->diffCellTemp) * 0.1;
        break;

    case 0x18FF02B:
        p2 = (CANData_BMUBasicP2 *)data.Data;
        g_GetCANBMUData[index].bmuBasicP2.moudleVolt = (p2->moudleVolt) * 0.1;
        g_GetCANBMUData[index].bmuBasicP2.boardTemp = (p2->boardTemp) * 0.1;
        break;

    case 0x18FF10B:
        p3 = (CANData_BMUBasicP3 *)data.Data;
        g_GetCANBMUData[index].bmuBasicP3.maxCellVolt = p3->maxCellVolt;
        g_GetCANBMUData[index].bmuBasicP3.minCellVolt = p3->minCellVolt;
        g_GetCANBMUData[index].bmuBasicP3.avgCellVolt = p3->avgCellVolt;
        g_GetCANBMUData[index].bmuBasicP3.maxCVNO = p3->maxCVNO;
        g_GetCANBMUData[index].bmuBasicP3.minCVNO = p3->minCVNO;
        break;

    case 0x18FF20B:
        p4 = (CANData_BMUBasicP4 *)data.Data;
        g_GetCANBMUData[index].bmuBasicP4.maxCellTemp = (p4->maxCellTemp) * 0.1;
        g_GetCANBMUData[index].bmuBasicP4.minCellTemp = (p4->minCellTemp) * 0.1;
        g_GetCANBMUData[index].bmuBasicP4.avgCellTemp = (p4->avgCellTemp) * 0.1;
        g_GetCANBMUData[index].bmuBasicP4.maxCTNO = p4->maxCTNO;
        g_GetCANBMUData[index].bmuBasicP4.minCTNO = p4->minCTNO;
        break;

    default:
        break;
    }
}


void GetBMSFaultStatus(VCI_CAN_OBJ data)
{
    CANData_BMSCellFault *p = NULL;
    p = (CANData_BMSCellFault *)data.Data;

    g_GetCANBMSData.bmsCellFault.fatalPOSC = p->bit.fatalPOSC;
    g_GetCANBMSData.bmsCellFault.fatalBMSSensor = p->bit.fatalBMSSensor;
    g_GetCANBMSData.bmsCellFault.fatalBMSAFE = p->bit.fatalBMSAFE;
    g_GetCANBMSData.bmsCellFault.fatalBMSCV = p->bit.fatalBMSCV;
    g_GetCANBMSData.bmsCellFault.fatalBMSCT = p->bit.fatalBMSCT;
    g_GetCANBMSData.bmsCellFault.fatalHvcuCom = p->bit.fatalHvcuCom;
    g_GetCANBMSData.bmsCellFault.fatalHvcuSensor = p->bit.fatalHvcuSensor;
}


void GetBMSCellStatus(VCI_CAN_OBJ data)
{
    CANData_BMSCellStatus *p = NULL;
    p = (CANData_BMSCellStatus *)data.Data;

    g_GetCANBMSData.bmsCellStatus.forceChrgSt = p->bit.forceChrgSt;
    g_GetCANBMSData.bmsCellStatus.posiRlySt = p->bit.posiRlySt;
    g_GetCANBMSData.bmsCellStatus.negRlySt = p->bit.negRlySt;
    g_GetCANBMSData.bmsCellStatus.rlySticky = p->bit.rlySticky;
    g_GetCANBMSData.bmsCellStatus.almSt = p->bit.almSt;
    g_GetCANBMSData.bmsCellStatus.moudleCfm = p->bit.moudleCfm;
    g_GetCANBMSData.bmsCellStatus.moudleNum = p->bit.moudleNum;
}


void GetBMSErrorStatus(VCI_CAN_OBJ data)
{
    CANData_BMSCellError *p = NULL;
    p = (CANData_BMSCellError *)data.Data;

    g_GetCANBMSData.bmsCellError.basicStatus = p->bit.basicStatus;
    g_GetCANBMSData.bmsCellError.cyclePeriod = p->bit.cyclePeriod;
    g_GetCANBMSData.bmsCellError.errVoltSensor = p->bit.errVoltSensor;
    g_GetCANBMSData.bmsCellError.errTempSensor = p->bit.errTempSensor;
    g_GetCANBMSData.bmsCellError.errInnCom = p->bit.errInnCom;
    g_GetCANBMSData.bmsCellError.errChrgVoltHigh = p->bit.errChrgVoltHigh;
    g_GetCANBMSData.bmsCellError.errWireInversed = p->bit.errWireInversed;
    g_GetCANBMSData.bmsCellError.errRelaySticky = p->bit.errRelaySticky;

    g_GetCANBMSData.bmsCellError.almCellVoltLow = p->bit.almCellVoltLow;
    g_GetCANBMSData.bmsCellError.almCellVoltHigh = p->bit.almCellVoltHigh;
    g_GetCANBMSData.bmsCellError.almPackVoltLow = p->bit.almPackVoltLow;
    g_GetCANBMSData.bmsCellError.almPackVoltHigh = p->bit.almPackVoltHigh;
    g_GetCANBMSData.bmsCellError.almChrgTempLow = p->bit.almChrgTempLow;
    g_GetCANBMSData.bmsCellError.almChrgTempHigh = p->bit.almChrgTempHigh;
    g_GetCANBMSData.bmsCellError.almDischrgTempLow = p->bit.almDischrgTempLow;
    g_GetCANBMSData.bmsCellError.almDischrgTempHigh = p->bit.almDischrgTempHigh;
    g_GetCANBMSData.bmsCellError.almChrgCurrHigh = p->bit.almChrgCurrHigh;
    g_GetCANBMSData.bmsCellError.almDischrgCurrHigh = p->bit.almDischrgCurrHigh;
    g_GetCANBMSData.bmsCellError.almMoudleVoltLow = p->bit.almMoudleVoltLow;
    g_GetCANBMSData.bmsCellError.almMoudleVoltHigh = p->bit.almMoudleVoltHigh;

    g_GetCANBMSData.bmsCellError.pCellVoltLow = p->bit.pCellVoltLow;
    g_GetCANBMSData.bmsCellError.pCellVoltHigh = p->bit.pCellVoltHigh;
    g_GetCANBMSData.bmsCellError.pPackVoltLow = p->bit.pPackVoltLow;
    g_GetCANBMSData.bmsCellError.pPackVoltHigh = p->bit.pPackVoltHigh;
    g_GetCANBMSData.bmsCellError.pChrgTempLow = p->bit.pChrgTempLow;
    g_GetCANBMSData.bmsCellError.pChrgTempHigh = p->bit.pChrgTempHigh;
    g_GetCANBMSData.bmsCellError.pDischrgTempLow = p->bit.pDischrgTempLow;
    g_GetCANBMSData.bmsCellError.pDischrgTempHigh = p->bit.pDischrgTempHigh;
    g_GetCANBMSData.bmsCellError.pChrgCurrHigh = p->bit.pChrgCurrHigh;
    g_GetCANBMSData.bmsCellError.pDischrgCurrHigh = p->bit.pDischrgCurrHigh;
    g_GetCANBMSData.bmsCellError.pMoudleVoltLow = p->bit.pMoudleVoltLow;
    g_GetCANBMSData.bmsCellError.pMoudleVoltHigh = p->bit.pMoudleVoltHigh;
}


void GetBMSVersion(VCI_CAN_OBJ data)
{
    CANData_BMSVersionInfo *p = NULL;
    p = (CANData_BMSVersionInfo *)data.Data;

    g_GetCANBMSData.bmsVersionInfo.hwVersion = p->hwVersion;
    g_GetCANBMSData.bmsVersionInfo.hwVersionSP = p->hwVersionSP;
    g_GetCANBMSData.bmsVersionInfo.hwVersionV = p->hwVersionV;
    g_GetCANBMSData.bmsVersionInfo.hwVersionR = p->hwVersionR;
    g_GetCANBMSData.bmsVersionInfo.swVersionV = p->swVersionV;
    g_GetCANBMSData.bmsVersionInfo.swVersionB = p->swVersionB;
    g_GetCANBMSData.bmsVersionInfo.swVersionS = p->swVersionS;
}


void GetBMSCommand(VCI_CAN_OBJ data)
{
    CANData_BMSCommand1 *p1 = NULL;
    CANData_BMSCommand2 *p2 = NULL;
    CANData_BMSCommand3 *p3 = NULL;
    CANData_BMSCommand4 *p4 = NULL;

    switch (data.ID)
    {
    case 0x4280:
        p1 = (CANData_BMSCommand1 *)data.Data;
        g_GetCANBMSData.bmsCommand1.chrgForbidenMark = p1->chrgForbidenMark;
        g_GetCANBMSData.bmsCommand1.dischrgForbidenMark = p1->dischrgForbidenMark;
        break;

    case 0x8200:
        p2 = (CANData_BMSCommand2 *)data.Data;
        g_GetCANBMSData.bmsCommand2.sleepCtrl = p2->sleepCtrl;
        break;

    case 0x8210:
        p3 = (CANData_BMSCommand3 *)data.Data;
        g_GetCANBMSData.bmsCommand3.chrgEN = p3->chrgEN;
        g_GetCANBMSData.bmsCommand3.dischrgEN = p3->dischrgEN;
        break;

    case 0x8220:
        p4 = (CANData_BMSCommand4 *)data.Data;
        g_GetCANBMSData.bmsCommand4.relayForceBreak = p4->relayForceBreak;
        break;

    default:
        break;
    }
}


void GetBMSCellConfig(VCI_CAN_OBJ data)
{
    CANData_BMSCellConfig *p1 = NULL;
    p1 = (CANData_BMSCellConfig *)data.Data;

    g_GetCANBMSData.bmsCellConfig.cellTotalNum = p1->cellTotalNum;
    g_GetCANBMSData.bmsCellConfig.moudleTotalNum = p1->moudleTotalNum;
    g_GetCANBMSData.bmsCellConfig.cellNumInMoudle = p1->cellNumInMoudle;
    g_GetCANBMSData.bmsCellConfig.voltageLevel = (p1->voltageLevel) * 10;
    g_GetCANBMSData.bmsCellConfig.capAH = p1->capAH;
}


void GetBMSBasicData(VCI_CAN_OBJ data)
{
    CANData_BMSCellBasic1 *p1 = NULL;
    CANData_BMSCellBasic2 *p2 = NULL;
    CANData_BMSCellBasic3 *p3 = NULL;
    CANData_BMSCellBasic4 *p4 = NULL;

    switch(data.ID)
    {
    case 0x4230:
        p1 = (CANData_BMSCellBasic1 *)data.Data;
        g_GetCANBMSData.bmsCellBaiscP1.maxCellVolt = p1->maxCellVolt;
        g_GetCANBMSData.bmsCellBaiscP1.minCellVolt = p1->minCellVolt;
        g_GetCANBMSData.bmsCellBaiscP1.maxCVNO = p1->maxCVNO;
        g_GetCANBMSData.bmsCellBaiscP1.minCVNO = p1->minCVNO;
        break;

    case 0x4240:
        p2 = (CANData_BMSCellBasic2 *)data.Data;
        g_GetCANBMSData.bmsCellBaiscP2.maxCellTemp = (p2->maxCellTemp) * 0.1 - 100;
        g_GetCANBMSData.bmsCellBaiscP2.minCellTemp = (p2->minCellTemp) * 0.1 - 100;
        g_GetCANBMSData.bmsCellBaiscP2.maxCTNO = p2->maxCTNO;
        g_GetCANBMSData.bmsCellBaiscP2.minCTNO = p2->minCTNO;
        break;

    case 0x4260:
        p3 = (CANData_BMSCellBasic3 *)data.Data;
        g_GetCANBMSData.bmsCellBaiscP3.maxMoudleCV = p3->maxMoudleCV;
        g_GetCANBMSData.bmsCellBaiscP3.minMoudleCV = p3->minMoudleCV;
        g_GetCANBMSData.bmsCellBaiscP3.maxMCVNO = p3->maxMCVNO;
        g_GetCANBMSData.bmsCellBaiscP3.minMCVNO = p3->minMCVNO;
        break;

    case 0x4270:
        p4 = (CANData_BMSCellBasic4 *)data.Data;
        g_GetCANBMSData.bmsCellBaiscP4.maxMoudleCT = (p4->maxMoudleCT) * 0.1 - 100;
        g_GetCANBMSData.bmsCellBaiscP4.minMoudleCT = (p4->minMoudleCT) * 0.1 - 100;
        g_GetCANBMSData.bmsCellBaiscP4.maxMCTNO = p4->maxMCTNO;
        g_GetCANBMSData.bmsCellBaiscP4.minMCTNO = p4->minMCTNO;
        break;

    default:
        break;
    }
}


void GetBMSCellModelData(VCI_CAN_OBJ data)
{
    CANData_BMSCellModule1 *p1 = NULL;
    CANData_BMSCellModule2 *p2 = NULL;
    CANData_BMSCellModule3 *p3 = NULL;
    CANData_BMSPoll *p4 = NULL;

    switch(data.ID)
    {
    case 0x4200:
        p4 = (CANData_BMSPoll *)data.Data;
        g_GetCANBMSData.bmsPoll.pollGlobalInfo = p4->pollGlobalInfo;
        break;

    case 0x4210:
        p1 = (CANData_BMSCellModule1 *)data.Data;
        g_GetCANBMSData.bmsCellModuleP1.packVolt = (p1->packVolt) * 0.1;
        g_GetCANBMSData.bmsCellModuleP1.packCurr = (p1->packCurr) * 0.1 - 3000;
        g_GetCANBMSData.bmsCellModuleP1.ambientTempOut = (p1->ambientTempOut) * 0.1 - 100;
        g_GetCANBMSData.bmsCellModuleP1.SOC = p1->SOC;
        g_GetCANBMSData.bmsCellModuleP1.SOH = p1->SOH;
        g_GetCANBMSData.bmsCellModuleP1.packPwr = (g_GetCANBMSData.bmsCellModuleP1.packVolt) * (g_GetCANBMSData.bmsCellModuleP1.packCurr);
        break;

    case 0x18FF02C0:
        p2 = (CANData_BMSCellModule2 *)data.Data;
        g_GetCANBMSData.bmsCellModuleP2.ambientTemp = (p2->ambientTemp) * 0.1;
        break;

    case 0x4220:
        p3 = (CANData_BMSCellModule3 *)data.Data;
        g_GetCANBMSData.bmsCellModuleP3.chgCutoffVolt = (p3->chgCutoffVolt) * 0.1;
        g_GetCANBMSData.bmsCellModuleP3.dischgCutoffVolt = (p3->dischgCutoffVolt) * 0.1;
        g_GetCANBMSData.bmsCellModuleP3.maxChgCurr = (p3->maxChgCurr) * 0.1 - 3000;
        g_GetCANBMSData.bmsCellModuleP3.maxDischgCurr = (p3->maxDischgCurr) * 0.1 - 3000;
        break;

    default:
        break;
    }
}

