#include "WorkThread.h"
#include "databasedefine.h"
#include "systemdefine.h"
#include "historyrecorddefine.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>

extern bool g_DBConnectionFlag;
extern unsigned char g_TestNumber;
extern BMSUIData g_GetCANBMSData;
extern BMUUIData g_GetCANBMUData[MAX_BMU_NUMBER];
extern BMSHistoryStatus g_BMSHistoryStatus;
extern BMUHistoryStatus g_BMUHistoruStatus[MAX_BMU_NUMBER];


void CANThread::BMUInfoToDB(UINT id)
{
    UINT partID = 0;
    partID = id >> 4;
    unsigned int index = 0;
    index = id & 0x0000000f;

    switch (partID)
    {
    /** BMU基本参数 **/
    case 0x18FF01B:
        SaveToRecentValue(id, BMU_SOC, g_GetCANBMUData[index].bmuBasicP1.SOC, AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_DIFF_CELL_VOLT, g_GetCANBMUData[index].bmuBasicP1.diffCellVolt, AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_DIFF_CELL_TEMP, g_GetCANBMUData[index].bmuBasicP1.diffCellTemp, AVERAGE_RECORD);
        break;

    case 0x18FF02B:
        SaveToRecentValue(id, BMU_MODULE_VOLT, g_GetCANBMUData[index].bmuBasicP2.moudleVolt, AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_BOARD_TEMP, g_GetCANBMUData[index].bmuBasicP2.boardTemp, AVERAGE_RECORD);
        break;

    case 0x18FF10B:
        SaveToRecentValue(id, BMU_MAX_CELL_VOLT, g_GetCANBMUData[index].bmuBasicP3.maxCellVolt, AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_MIN_CELL_VOLT, g_GetCANBMUData[index].bmuBasicP3.minCellVolt, AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_AVG_CELL_VOLT, g_GetCANBMUData[index].bmuBasicP3.avgCellVolt, AVERAGE_RECORD);
        if (g_BMUHistoruStatus[index].bmuMaxCVNO != g_GetCANBMUData[index].bmuBasicP3.maxCVNO)
            SaveToRecentValue(id, BMU_MAX_CV_NO, g_GetCANBMUData[index].bmuBasicP3.maxCVNO, SOURCE_RECORD);
        if (g_BMUHistoruStatus[index].bmuMinCVNO != g_GetCANBMUData[index].bmuBasicP3.minCVNO)
            SaveToRecentValue(id, BMU_MIN_CV_NO, g_GetCANBMUData[index].bmuBasicP3.minCVNO, SOURCE_RECORD);
        break;

    case 0x18FF20B:
        SaveToRecentValue(id, BMU_MAX_CELL_TEMP, g_GetCANBMUData[index].bmuBasicP4.maxCellTemp, AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_MIN_CELL_TEMP, g_GetCANBMUData[index].bmuBasicP4.minCellTemp, AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_AVG_CELL_TEMP, g_GetCANBMUData[index].bmuBasicP4.avgCellTemp, AVERAGE_RECORD);
        if (g_BMUHistoruStatus[index].bmuMaxCTNO != g_GetCANBMUData[index].bmuBasicP4.maxCTNO)
            SaveToRecentValue(id, BMU_MAX_CT_NO, g_GetCANBMUData[index].bmuBasicP4.maxCTNO, SOURCE_RECORD);
        if (g_BMUHistoruStatus[index].bmuMinCTNO != g_GetCANBMUData[index].bmuBasicP4.minCTNO)
            SaveToRecentValue(id, BMU_MIN_CT_NO, g_GetCANBMUData[index].bmuBasicP4.minCTNO, SOURCE_RECORD);
        break;

    /** 模组配置 **/
    case 0x18FF60B:
        if (g_BMUHistoruStatus[index].moduleConfig.cellAH != g_GetCANBMUData[index].bmuModuleConfig.cellAH)
            SaveToRecentValue(id, BMU_CELL_AH, g_GetCANBMUData[index].bmuModuleConfig.cellAH, SOURCE_RECORD);
        if (g_BMUHistoruStatus[index].moduleConfig.cellRateVolt != g_GetCANBMUData[index].bmuModuleConfig.cellRateVolt)
            SaveToRecentValue(id, BMU_CELL_RATE_VOLT, g_GetCANBMUData[index].bmuModuleConfig.cellRateVolt, SOURCE_RECORD);
        if (g_BMUHistoruStatus[index].moduleConfig.cellNum != g_GetCANBMUData[index].bmuModuleConfig.cellNum)
            SaveToRecentValue(id, BMU_CELL_NUM, g_GetCANBMUData[index].bmuModuleConfig.cellNum, SOURCE_RECORD);
        if (g_BMUHistoruStatus[index].moduleConfig.tempNum != g_GetCANBMUData[index].bmuModuleConfig.tempNum)
            SaveToRecentValue(id, BMU_TEMP_NUM, g_GetCANBMUData[index].bmuModuleConfig.tempNum, SOURCE_RECORD);
        break;

    /** 单芯电压 **/
    case 0x18FF40B:
        SaveToRecentValue(id, BMU_CELL_VOLT_0, g_GetCANBMUData[index].bmuCellVolt.cellVolt[0], AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_CELL_VOLT_1, g_GetCANBMUData[index].bmuCellVolt.cellVolt[1], AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_CELL_VOLT_2, g_GetCANBMUData[index].bmuCellVolt.cellVolt[2], AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_CELL_VOLT_3, g_GetCANBMUData[index].bmuCellVolt.cellVolt[3], AVERAGE_RECORD);
        break;

    case 0x18FF41B:
        SaveToRecentValue(id, BMU_CELL_VOLT_4, g_GetCANBMUData[index].bmuCellVolt.cellVolt[4], AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_CELL_VOLT_5, g_GetCANBMUData[index].bmuCellVolt.cellVolt[5], AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_CELL_VOLT_6, g_GetCANBMUData[index].bmuCellVolt.cellVolt[6], AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_CELL_VOLT_7, g_GetCANBMUData[index].bmuCellVolt.cellVolt[7], AVERAGE_RECORD);
        break;

    case 0x18FF42B:
        SaveToRecentValue(id, BMU_CELL_VOLT_8, g_GetCANBMUData[index].bmuCellVolt.cellVolt[8], AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_CELL_VOLT_9, g_GetCANBMUData[index].bmuCellVolt.cellVolt[9], AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_CELL_VOLT_10, g_GetCANBMUData[index].bmuCellVolt.cellVolt[10], AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_CELL_VOLT_11, g_GetCANBMUData[index].bmuCellVolt.cellVolt[11], AVERAGE_RECORD);
        break;

    case 0x18FF43B:
        SaveToRecentValue(id, BMU_CELL_VOLT_12, g_GetCANBMUData[index].bmuCellVolt.cellVolt[12], AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_CELL_VOLT_13, g_GetCANBMUData[index].bmuCellVolt.cellVolt[13], AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_CELL_VOLT_14, g_GetCANBMUData[index].bmuCellVolt.cellVolt[14], AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_CELL_VOLT_15, g_GetCANBMUData[index].bmuCellVolt.cellVolt[15], AVERAGE_RECORD);
        break;

    /** 单体温度 **/
    case 0x18FF50B:
        SaveToRecentValue(id, BMU_CELL_TEMP_0, g_GetCANBMUData[index].bmuCellTemp.cellTemp[0], AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_CELL_TEMP_1, g_GetCANBMUData[index].bmuCellTemp.cellTemp[1], AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_CELL_TEMP_2, g_GetCANBMUData[index].bmuCellTemp.cellTemp[2], AVERAGE_RECORD);
        SaveToRecentValue(id, BMU_CELL_TEMP_3, g_GetCANBMUData[index].bmuCellTemp.cellTemp[3], AVERAGE_RECORD);
        break;

    default:
        break;
    }
}


void CANThread::BMSInfoToDB(UINT id)
{
    switch (id)
    {
    /** BMS cmd **/
    case 0x4200:
        if (g_BMSHistoryStatus.globalInfo.pollGlobalInfo != g_GetCANBMSData.bmsPoll.pollGlobalInfo)
            SaveToRecentValue(id, BMS_POLL_GLOBAL_INFO, g_GetCANBMSData.bmsPoll.pollGlobalInfo, SOURCE_RECORD);
        break;


    /** 电池模组参数 **/
    case 0x4210:
        SaveToRecentValue(id, BMS_PACK_VOLT, g_GetCANBMSData.bmsCellModuleP1.packVolt, AVERAGE_RECORD);
        SaveToRecentValue(id, BMS_PACK_CURR, g_GetCANBMSData.bmsCellModuleP1.packCurr, AVERAGE_RECORD);
        SaveToRecentValue(id, BMS_AMBIENT_TEMP_OUT, g_GetCANBMSData.bmsCellModuleP1.ambientTempOut, AVERAGE_RECORD);
        SaveToRecentValue(id, BMS_SOC, g_GetCANBMSData.bmsCellModuleP1.SOC, AVERAGE_RECORD);
        SaveToRecentValue(id, BMS_PACK_PWR, g_GetCANBMSData.bmsCellModuleP1.packPwr, AVERAGE_RECORD);
        break;

    case 0x18FF02C0:
        SaveToRecentValue(id, BMS_AMBIENT_TEMP_IN, g_GetCANBMSData.bmsCellModuleP2.ambientTemp, AVERAGE_RECORD);
        break;

    case 0x4220:
        SaveToRecentValue(id, BMS_MAX_CHG_CURR, g_GetCANBMSData.bmsCellModuleP3.maxChgCurr, AVERAGE_RECORD);
        SaveToRecentValue(id, BMS_MAX_DISCHG_CURR, g_GetCANBMSData.bmsCellModuleP3.maxDischgCurr, AVERAGE_RECORD);
        break;

    /** 电池基本参数 **/
    case 0x4230:
        SaveToRecentValue(id, BMS_MAX_CELL_VLOT, g_GetCANBMSData.bmsCellBaiscP1.maxCellVolt, AVERAGE_RECORD);
        SaveToRecentValue(id, BMS_MIN_CELL_VOLT, g_GetCANBMSData.bmsCellBaiscP1.minCellVolt, AVERAGE_RECORD);
        if (g_BMSHistoryStatus.bmsMaxCVNO != g_GetCANBMSData.bmsCellBaiscP1.maxCVNO)
            SaveToRecentValue(id, BMS_MAX_CV_NO, g_GetCANBMSData.bmsCellBaiscP1.maxCVNO, SOURCE_RECORD);
        if (g_BMSHistoryStatus.bmsMinCVNO != g_GetCANBMSData.bmsCellBaiscP1.minCVNO)
            SaveToRecentValue(id, BMS_MIN_CV_NO, g_GetCANBMSData.bmsCellBaiscP1.minCVNO, SOURCE_RECORD);
        break;

    case 0x4240:
        SaveToRecentValue(id, BMS_MAX_CELL_TEMP, g_GetCANBMSData.bmsCellBaiscP2.maxCellTemp, AVERAGE_RECORD);
        SaveToRecentValue(id, BMS_MIN_CELL_TEMP, g_GetCANBMSData.bmsCellBaiscP2.minCellTemp, AVERAGE_RECORD);
        if (g_BMSHistoryStatus.bmsMaxCTNO != g_GetCANBMSData.bmsCellBaiscP2.maxCTNO)
            SaveToRecentValue(id, BMS_MAX_CT_NO, g_GetCANBMSData.bmsCellBaiscP2.maxCTNO, SOURCE_RECORD);
        if (g_BMSHistoryStatus.bmsMinCTNO != g_GetCANBMSData.bmsCellBaiscP2.minCTNO)
            SaveToRecentValue(id, BMS_MIN_CT_NO, g_GetCANBMSData.bmsCellBaiscP2.minCTNO, SOURCE_RECORD);
        break;

    case 0x4260:
        SaveToRecentValue(id, BMS_MAX_MODULE_CV, g_GetCANBMSData.bmsCellBaiscP3.maxMoudleCV, AVERAGE_RECORD);
        SaveToRecentValue(id, BMS_MIN_MODULE_CV, g_GetCANBMSData.bmsCellBaiscP3.minMoudleCV, AVERAGE_RECORD);
        if (g_BMSHistoryStatus.maxMCVNO != g_GetCANBMSData.bmsCellBaiscP3.maxMCVNO)
            SaveToRecentValue(id, BMS_MAX_MCV_NO, g_GetCANBMSData.bmsCellBaiscP3.maxMCVNO, SOURCE_RECORD);
        if (g_BMSHistoryStatus.minMCVNO != g_GetCANBMSData.bmsCellBaiscP3.minMCVNO)
            SaveToRecentValue(id, BMS_MIN_MCV_NO, g_GetCANBMSData.bmsCellBaiscP3.minMCVNO, SOURCE_RECORD);
        break;

    case 0x4270:
        SaveToRecentValue(id, BMS_MAX_MODULE_CT, g_GetCANBMSData.bmsCellBaiscP4.maxMoudleCT, AVERAGE_RECORD);
        SaveToRecentValue(id, BMS_MIN_MOUDLE_CT, g_GetCANBMSData.bmsCellBaiscP4.minMoudleCT, AVERAGE_RECORD);
        if (g_BMSHistoryStatus.maxMCTNO != g_GetCANBMSData.bmsCellBaiscP4.maxMCTNO)
            SaveToRecentValue(id, BMS_MAX_MCT_NO, g_GetCANBMSData.bmsCellBaiscP4.maxMCTNO, SOURCE_RECORD);
        if (g_BMSHistoryStatus.minMCTNO != g_GetCANBMSData.bmsCellBaiscP4.minMCTNO)
            SaveToRecentValue(id, BMS_MIN_MCT_NO, g_GetCANBMSData.bmsCellBaiscP4.minMCTNO, SOURCE_RECORD);
        break;

    /** 指令 **/
    case 0x4280:
        if (g_BMSHistoryStatus.command1.chrgForbidenMark != g_GetCANBMSData.bmsCommand1.chrgForbidenMark)
            SaveToRecentValue(id, BMS_CHRG_FORBIDEN_MARK, g_GetCANBMSData.bmsCommand1.chrgForbidenMark, SOURCE_RECORD);
        if (g_BMSHistoryStatus.command1.dischrgForbidenMark != g_GetCANBMSData.bmsCommand1.dischrgForbidenMark)
            SaveToRecentValue(id, BMS_DISCHRG_FORBIDEN_MARK, g_GetCANBMSData.bmsCommand1.dischrgForbidenMark, SOURCE_RECORD);
        break;

    case 0x8200:
        if (g_BMSHistoryStatus.command2.sleepCtrl != g_GetCANBMSData.bmsCommand2.sleepCtrl)
            SaveToRecentValue(id, BMS_SLEEP_CTRL,g_GetCANBMSData.bmsCommand2.sleepCtrl, SOURCE_RECORD);
        break;

    case 0x8210:
        if (g_BMSHistoryStatus.command3.chrgEN != g_GetCANBMSData.bmsCommand3.chrgEN)
            SaveToRecentValue(id, BMS_CHRG_EN, g_GetCANBMSData.bmsCommand3.chrgEN, SOURCE_RECORD);
        if (g_BMSHistoryStatus.command3.dischrgEN != g_GetCANBMSData.bmsCommand3.dischrgEN)
            SaveToRecentValue(id, BMS_DISCHRG_EN, g_GetCANBMSData.bmsCommand3.dischrgEN, SOURCE_RECORD);
        break;

    case 0x8220:
        if (g_BMSHistoryStatus.command4.relayForceBreak != g_GetCANBMSData.bmsCommand4.relayForceBreak)
            SaveToRecentValue(id, BMS_RELAY_FORCE_BREAK, g_GetCANBMSData.bmsCommand4.relayForceBreak, SOURCE_RECORD);
        break;

    default:
        break;
    }
}


void CANThread::BMUStatusToDB(UINT id)
{
    unsigned int index = 0;
    index = id & 0x0000000f;

    if (g_BMUHistoruStatus[index].status.AFESample != g_GetCANBMUData[index].bmuStatus.AFESample)
        SaveToRecentValue(id, BMU_AFE_SAMPLE, g_GetCANBMUData[index].bmuStatus.AFESample , SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.AFEFault != g_GetCANBMUData[index].bmuStatus.AFEFault)
        SaveToRecentValue(id, BMU_AFE_FAULT, g_GetCANBMUData[index].bmuStatus.AFEFault, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.OWDSt != g_GetCANBMUData[index].bmuStatus.OWDSt)
        SaveToRecentValue(id, BMU_OWD_ST, g_GetCANBMUData[index].bmuStatus.OWDSt, SOURCE_RECORD);

    if (g_BMUHistoruStatus[index].status.lv1CellVoltLow != g_GetCANBMUData[index].bmuStatus.lv1CellVoltLow)
    SaveToRecentValue(id, BMU_LV1_CELL_VOLT_LOW, g_GetCANBMUData[index].bmuStatus.lv1CellVoltLow, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv1CellVoltHigh != g_GetCANBMUData[index].bmuStatus.lv1CellVoltHigh)
    SaveToRecentValue(id, BMU_LV1_CELL_VOLT_HIGH, g_GetCANBMUData[index].bmuStatus.lv1CellVoltHigh, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv1CellVoltDiff != g_GetCANBMUData[index].bmuStatus.lv1CellVoltDiff)
    SaveToRecentValue(id, BMU_LV1_CELL_VOLT_DIFF, g_GetCANBMUData[index].bmuStatus.lv1CellVoltDiff, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv1MoudleVoltLow != g_GetCANBMUData[index].bmuStatus.lv1MoudleVoltLow)
    SaveToRecentValue(id, BMU_LV1_MODULE_VOLT_LOW, g_GetCANBMUData[index].bmuStatus.lv1MoudleVoltLow, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv1MoudleVoltHigh != g_GetCANBMUData[index].bmuStatus.lv1MoudleVoltHigh)
    SaveToRecentValue(id, BMU_LV1_MODULE_VOLT_HIGH, g_GetCANBMUData[index].bmuStatus.lv1MoudleVoltHigh, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv1AmbientTempLow != g_GetCANBMUData[index].bmuStatus.lv1AmbientTempLow)
    SaveToRecentValue(id, BMU_LV1_AMBIENT_TEMP_LOW, g_GetCANBMUData[index].bmuStatus.lv1AmbientTempLow, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv1AmbientTempHigh != g_GetCANBMUData[index].bmuStatus.lv1AmbientTempHigh)
    SaveToRecentValue(id, BMU_LV1_AMBIENT_TEMP_HIGH, g_GetCANBMUData[index].bmuStatus.lv1AmbientTempHigh, SOURCE_RECORD);

    if (g_BMUHistoruStatus[index].status.lv1ChrgTempLow != g_GetCANBMUData[index].bmuStatus.lv1ChrgTempLow)
    SaveToRecentValue(id, BMU_LV1_CHRG_TEMP_LOW, g_GetCANBMUData[index].bmuStatus.lv1ChrgTempLow, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv1ChrgTempHigh != g_GetCANBMUData[index].bmuStatus.lv1ChrgTempHigh)
    SaveToRecentValue(id, BMU_LV1_CHRG_TEMP_HIGH, g_GetCANBMUData[index].bmuStatus.lv1ChrgTempHigh, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv1DischrgTempLow != g_GetCANBMUData[index].bmuStatus.lv1DischrgTempLow)
    SaveToRecentValue(id, BMU_LV1_DISCHRG_TEMP_LOW, g_GetCANBMUData[index].bmuStatus.lv1DischrgTempLow, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv1DischrgTempHigh != g_GetCANBMUData[index].bmuStatus.lv1DischrgTempHigh)
    SaveToRecentValue(id, BMU_LV1_DISCHRG_TEMP_HIGH, g_GetCANBMUData[index].bmuStatus.lv1DischrgTempHigh, SOURCE_RECORD);

    if (g_BMUHistoruStatus[index].status.lv2CellVoltLow != g_GetCANBMUData[index].bmuStatus.lv2CellVoltLow)
    SaveToRecentValue(id, BMU_LV2_CELL_VOLT_LOW, g_GetCANBMUData[index].bmuStatus.lv2CellVoltLow, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv2CellVoltHigh != g_GetCANBMUData[index].bmuStatus.lv2CellVoltHigh)
    SaveToRecentValue(id, BMU_LV2_CELL_VOLT_HIGH, g_GetCANBMUData[index].bmuStatus.lv2CellVoltHigh, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv2CellVoltDiff != g_GetCANBMUData[index].bmuStatus.lv2CellVoltDiff)
    SaveToRecentValue(id, BMU_LV2_CELL_VOLT_DIFF, g_GetCANBMUData[index].bmuStatus.lv2CellVoltDiff, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv2MoudleVoltLow != g_GetCANBMUData[index].bmuStatus.lv2MoudleVoltLow)
    SaveToRecentValue(id, BMU_LV2_MODULE_VOLT_LOW, g_GetCANBMUData[index].bmuStatus.lv2MoudleVoltLow, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv2MoudleVoltHigh != g_GetCANBMUData[index].bmuStatus.lv2MoudleVoltHigh)
    SaveToRecentValue(id, BMU_LV2_MODULE_VOLT_HIGH, g_GetCANBMUData[index].bmuStatus.lv2MoudleVoltHigh, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv2AmbientTempLow != g_GetCANBMUData[index].bmuStatus.lv2AmbientTempLow)
    SaveToRecentValue(id, BMU_LV2_AMBIENT_TEMP_LOW, g_GetCANBMUData[index].bmuStatus.lv2AmbientTempLow, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv2AmbientTempHigh != g_GetCANBMUData[index].bmuStatus.lv2AmbientTempHigh)
    SaveToRecentValue(id, BMU_LV2_AMBIENT_TEMP_HIGH, g_GetCANBMUData[index].bmuStatus.lv2AmbientTempHigh, SOURCE_RECORD);

    if (g_BMUHistoruStatus[index].status.lv2ChrgTempLow != g_GetCANBMUData[index].bmuStatus.lv2ChrgTempLow)
    SaveToRecentValue(id, BMU_LV2_CHRG_TEMP_LOW, g_GetCANBMUData[index].bmuStatus.lv2ChrgTempLow, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv2ChrgTempHigh != g_GetCANBMUData[index].bmuStatus.lv2ChrgTempHigh)
    SaveToRecentValue(id, BMU_LV2_CHRG_TEMP_HIGH, g_GetCANBMUData[index].bmuStatus.lv2ChrgTempHigh, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv2DischrgTempLow != g_GetCANBMUData[index].bmuStatus.lv2DischrgTempLow)
    SaveToRecentValue(id, BMU_LV2_DISCHRG_TEMP_LOW, g_GetCANBMUData[index].bmuStatus.lv2DischrgTempLow, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].status.lv2DischrgTempHigh != g_GetCANBMUData[index].bmuStatus.lv2DischrgTempHigh)
    SaveToRecentValue(id, BMU_LV2_DISCHRG_TEMP_HIGH, g_GetCANBMUData[index].bmuStatus.lv2DischrgTempHigh, SOURCE_RECORD);
}


void CANThread::BMUBalStatusToDB(UINT id)
{
    unsigned int index = 0;
    index = id & 0x0000000f;

    if (g_BMUHistoruStatus[index].balStatus.cellBalMode != g_GetCANBMUData[index].bmuBalStatus.cellBalMode)
        SaveToRecentValue(id, BMU_CELL_BAL_MODE, g_GetCANBMUData[index].bmuBalStatus.cellBalMode, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellBalSt != g_GetCANBMUData[index].bmuBalStatus.cellBalSt)
        SaveToRecentValue(id, BMU_CELL_BAL_ST, g_GetCANBMUData[index].bmuBalStatus.cellBalSt, SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[0] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[0])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_0, g_GetCANBMUData[index].bmuBalStatus.cellInBal[0], SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[1] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[1])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_1, g_GetCANBMUData[index].bmuBalStatus.cellInBal[1], SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[2] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[2])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_2, g_GetCANBMUData[index].bmuBalStatus.cellInBal[2], SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[3] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[3])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_3, g_GetCANBMUData[index].bmuBalStatus.cellInBal[3], SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[4] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[4])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_4, g_GetCANBMUData[index].bmuBalStatus.cellInBal[4], SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[5] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[5])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_5, g_GetCANBMUData[index].bmuBalStatus.cellInBal[5], SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[6] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[6])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_6, g_GetCANBMUData[index].bmuBalStatus.cellInBal[6], SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[7] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[7])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_7, g_GetCANBMUData[index].bmuBalStatus.cellInBal[7], SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[8] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[8])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_8, g_GetCANBMUData[index].bmuBalStatus.cellInBal[8], SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[9] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[9])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_9, g_GetCANBMUData[index].bmuBalStatus.cellInBal[9], SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[10] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[10])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_10, g_GetCANBMUData[index].bmuBalStatus.cellInBal[10], SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[11] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[11])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_11, g_GetCANBMUData[index].bmuBalStatus.cellInBal[11], SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[12] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[12])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_12, g_GetCANBMUData[index].bmuBalStatus.cellInBal[12], SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[13] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[13])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_13, g_GetCANBMUData[index].bmuBalStatus.cellInBal[13], SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[14] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[14])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_14, g_GetCANBMUData[index].bmuBalStatus.cellInBal[14], SOURCE_RECORD);
    if (g_BMUHistoruStatus[index].balStatus.cellInBal[15] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[15])
        SaveToRecentValue(id, BMU_CELL_IN_BAL_15, g_GetCANBMUData[index].bmuBalStatus.cellInBal[15], SOURCE_RECORD);
}


void CANThread::BMSErrorToDB(UINT id)
{
    if (g_BMSHistoryStatus.errorStatus.basicStatus != g_GetCANBMSData.bmsCellError.basicStatus)
        SaveToRecentValue(id, BMS_BASIC_STATUS, g_GetCANBMSData.bmsCellError.basicStatus, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.errVoltSensor != g_GetCANBMSData.bmsCellError.errVoltSensor)
        SaveToRecentValue(id, BMS_ERR_VOLT_SENSOR, g_GetCANBMSData.bmsCellError.errVoltSensor, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.errTempSensor != g_GetCANBMSData.bmsCellError.errTempSensor)
        SaveToRecentValue(id, BMS_ERR_TEMP_SENSOR, g_GetCANBMSData.bmsCellError.errTempSensor, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.errInnCom != g_GetCANBMSData.bmsCellError.errInnCom)
        SaveToRecentValue(id, BMS_ERR_INN_COM, g_GetCANBMSData.bmsCellError.errInnCom, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.errChrgVoltHigh != g_GetCANBMSData.bmsCellError.errChrgVoltHigh)
        SaveToRecentValue(id, BMS_ERR_CHRG_VOLT_HIGH, g_GetCANBMSData.bmsCellError.errChrgVoltHigh, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.errWireInversed != g_GetCANBMSData.bmsCellError.errWireInversed)
        SaveToRecentValue(id, BMS_ERR_WIRE_INVERSED, g_GetCANBMSData.bmsCellError.errWireInversed, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.errRelaySticky != g_GetCANBMSData.bmsCellError.errRelaySticky)
        SaveToRecentValue(id, BMS_ERR_RELAY_STICKY, g_GetCANBMSData.bmsCellError.errRelaySticky, SOURCE_RECORD);

    if (g_BMSHistoryStatus.errorStatus.almCellVoltLow != g_GetCANBMSData.bmsCellError.almCellVoltLow)
        SaveToRecentValue(id, BMS_ALM_CELL_VOLT_LOW, g_GetCANBMSData.bmsCellError.almCellVoltLow, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.almCellVoltHigh != g_GetCANBMSData.bmsCellError.almCellVoltHigh)
        SaveToRecentValue(id, BMS_ALM_CELL_VOLT_HIGH, g_GetCANBMSData.bmsCellError.almCellVoltHigh, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.almPackVoltLow != g_GetCANBMSData.bmsCellError.almPackVoltLow)
        SaveToRecentValue(id, BMS_ALM_PACK_VOLT_LOW, g_GetCANBMSData.bmsCellError.almPackVoltLow, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.almPackVoltHigh != g_GetCANBMSData.bmsCellError.almPackVoltHigh)
        SaveToRecentValue(id, BMS_ALM_PACK_VOLT_HIGH, g_GetCANBMSData.bmsCellError.almPackVoltHigh, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.almChrgTempLow != g_GetCANBMSData.bmsCellError.almChrgTempLow)
        SaveToRecentValue(id, BMS_ALM_CHRG_TEMP_LOW, g_GetCANBMSData.bmsCellError.almChrgTempLow, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.almChrgTempHigh != g_GetCANBMSData.bmsCellError.almChrgTempHigh)
        SaveToRecentValue(id, BMS_ALM_CHRG_TEMP_HIGH, g_GetCANBMSData.bmsCellError.almChrgTempHigh, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.almDischrgTempLow != g_GetCANBMSData.bmsCellError.almDischrgTempLow)
        SaveToRecentValue(id, BMS_ALM_DISCHRG_TEMP_LOW, g_GetCANBMSData.bmsCellError.almDischrgTempLow, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.almDischrgTempHigh != g_GetCANBMSData.bmsCellError.almDischrgTempHigh)
        SaveToRecentValue(id, BMS_ALM_DISCHRG_TEMP_HIGH, g_GetCANBMSData.bmsCellError.almDischrgTempHigh, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.almChrgCurrHigh != g_GetCANBMSData.bmsCellError.almChrgCurrHigh)
        SaveToRecentValue(id, BMS_ALM_CHRG_CURR_HIGH, g_GetCANBMSData.bmsCellError.almChrgCurrHigh, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.almDischrgCurrHigh != g_GetCANBMSData.bmsCellError.almDischrgCurrHigh)
        SaveToRecentValue(id, BMS_ALM_DISCHRG_CURR_HIGH, g_GetCANBMSData.bmsCellError.almDischrgCurrHigh, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.almMoudleVoltLow != g_GetCANBMSData.bmsCellError.almMoudleVoltLow)
        SaveToRecentValue(id, BMS_ALM_MODULE_VOLT_LOW, g_GetCANBMSData.bmsCellError.almMoudleVoltLow, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.almMoudleVoltHigh != g_GetCANBMSData.bmsCellError.almMoudleVoltHigh)
        SaveToRecentValue(id, BMS_ALM_MODULE_VOLT_HIGH, g_GetCANBMSData.bmsCellError.almMoudleVoltHigh, SOURCE_RECORD);

    if (g_BMSHistoryStatus.errorStatus.pCellVoltLow != g_GetCANBMSData.bmsCellError.pCellVoltLow)
        SaveToRecentValue(id, BMS_P_CELL_VOLT_LOW, g_GetCANBMSData.bmsCellError.pCellVoltLow, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.pCellVoltHigh != g_GetCANBMSData.bmsCellError.pCellVoltHigh)
        SaveToRecentValue(id, BMS_P_CELL_VOLT_HIGH, g_GetCANBMSData.bmsCellError.pCellVoltHigh, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.pPackVoltLow != g_GetCANBMSData.bmsCellError.pPackVoltLow)
        SaveToRecentValue(id, BMS_P_PACK_VOLT_LOW, g_GetCANBMSData.bmsCellError.pPackVoltLow, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.pPackVoltHigh != g_GetCANBMSData.bmsCellError.pPackVoltHigh)
        SaveToRecentValue(id, BMS_P_PACK_VOLT_HIGH, g_GetCANBMSData.bmsCellError.pPackVoltHigh, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.pChrgTempLow != g_GetCANBMSData.bmsCellError.pChrgTempLow)
        SaveToRecentValue(id, BMS_P_CHRG_TEMP_LOW, g_GetCANBMSData.bmsCellError.pChrgTempLow, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.pChrgTempHigh != g_GetCANBMSData.bmsCellError.pChrgTempHigh)
        SaveToRecentValue(id, BMS_P_CHRG_TEMP_HIGH, g_GetCANBMSData.bmsCellError.pChrgTempHigh, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.pDischrgTempLow != g_GetCANBMSData.bmsCellError.pDischrgTempLow)
        SaveToRecentValue(id, BMS_P_DISCHRG_TEMP_LOW, g_GetCANBMSData.bmsCellError.pDischrgTempLow, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.pDischrgTempHigh != g_GetCANBMSData.bmsCellError.pDischrgTempHigh)
        SaveToRecentValue(id, BMS_P_DISCHRG_TEMP_HIGH, g_GetCANBMSData.bmsCellError.pDischrgTempHigh, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.pChrgCurrHigh != g_GetCANBMSData.bmsCellError.pChrgCurrHigh)
        SaveToRecentValue(id, BMS_P_CHRG_CURR_HIGH, g_GetCANBMSData.bmsCellError.pChrgCurrHigh, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.pDischrgCurrHigh != g_GetCANBMSData.bmsCellError.pDischrgCurrHigh)
        SaveToRecentValue(id, BMS_P_DISCHRG_CURR_HIGH, g_GetCANBMSData.bmsCellError.pDischrgCurrHigh, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.pMoudleVoltLow != g_GetCANBMSData.bmsCellError.pMoudleVoltLow)
        SaveToRecentValue(id, BMS_P_MODULE_VOLT_LOW, g_GetCANBMSData.bmsCellError.pMoudleVoltLow, SOURCE_RECORD);
    if (g_BMSHistoryStatus.errorStatus.pMoudleVoltHigh != g_GetCANBMSData.bmsCellError.pMoudleVoltHigh)
        SaveToRecentValue(id, BMS_P_MODULE_VOLT_HIGH, g_GetCANBMSData.bmsCellError.pMoudleVoltHigh, SOURCE_RECORD);
}


void CANThread::BMSStatusToDB(UINT id)
{
    if (g_BMSHistoryStatus.cellStatus.forceChrgSt != g_GetCANBMSData.bmsCellStatus.forceChrgSt)
        SaveToRecentValue(id, BMS_FORCE_CHRG_ST, g_GetCANBMSData.bmsCellStatus.forceChrgSt, SOURCE_RECORD);
    if (g_BMSHistoryStatus.cellStatus.posiRlySt != g_GetCANBMSData.bmsCellStatus.posiRlySt)
        SaveToRecentValue(id, BMS_POSI_RLY_ST, g_GetCANBMSData.bmsCellStatus.posiRlySt, SOURCE_RECORD);
    if (g_BMSHistoryStatus.cellStatus.negRlySt != g_GetCANBMSData.bmsCellStatus.negRlySt)
        SaveToRecentValue(id, BMS_NEG_RLY_ST, g_GetCANBMSData.bmsCellStatus.negRlySt, SOURCE_RECORD);
    if (g_BMSHistoryStatus.cellStatus.rlySticky != g_GetCANBMSData.bmsCellStatus.rlySticky)
        SaveToRecentValue(id, BMS_RLY_STICKY, g_GetCANBMSData.bmsCellStatus.rlySticky, SOURCE_RECORD);
    if (g_BMSHistoryStatus.cellStatus.almSt != g_GetCANBMSData.bmsCellStatus.almSt)
        SaveToRecentValue(id, BMS_ALM_ST, g_GetCANBMSData.bmsCellStatus.almSt, SOURCE_RECORD);
}


void CANThread::BMSFaultToDB(UINT id)
{
    if (g_BMSHistoryStatus.cellFault.fatalBMSSensor != g_GetCANBMSData.bmsCellFault.fatalBMSSensor)
        SaveToRecentValue(id, BMS_FATAL_BMU_SENSOR, g_GetCANBMSData.bmsCellFault.fatalBMSSensor, SOURCE_RECORD);
    if (g_BMSHistoryStatus.cellFault.fatalBMSAFE != g_GetCANBMSData.bmsCellFault.fatalBMSAFE)
        SaveToRecentValue(id, BMS_FATAL_BMU_AFE, g_GetCANBMSData.bmsCellFault.fatalBMSAFE, SOURCE_RECORD);
    if (g_BMSHistoryStatus.cellFault.fatalBMSCV != g_GetCANBMSData.bmsCellFault.fatalBMSCV)
        SaveToRecentValue(id, BMS_FATAL_BMU_CV, g_GetCANBMSData.bmsCellFault.fatalBMSCV, SOURCE_RECORD);
    if (g_BMSHistoryStatus.cellFault.fatalBMSCT != g_GetCANBMSData.bmsCellFault.fatalBMSCT)
        SaveToRecentValue(id, BMS_FATAL_BMU_VT, g_GetCANBMSData.bmsCellFault.fatalBMSCT, SOURCE_RECORD);
    if (g_BMSHistoryStatus.cellFault.fatalHvcuCom != g_GetCANBMSData.bmsCellFault.fatalHvcuCom)
        SaveToRecentValue(id, BMS_FATAL_HVCU_COM, g_GetCANBMSData.bmsCellFault.fatalHvcuCom, SOURCE_RECORD);
    if (g_BMSHistoryStatus.cellFault.fatalHvcuSensor != g_GetCANBMSData.bmsCellFault.fatalHvcuSensor)
        SaveToRecentValue(id, BMS_FATAL_HVCU_SENSOR, g_GetCANBMSData.bmsCellFault.fatalHvcuSensor, SOURCE_RECORD);
}


void CANThread::SaveToRecentValue(unsigned int id, const char *pName, float value, int type)
{
    QSqlQuery query = QSqlQuery(m_canDB);
    QString sqlLine = NULL;

    if (g_DBConnectionFlag)
    {
        sqlLine = QString("insert into %1 (Time, TestNumber, SignalID, ParameterName, Value, Type) values (UNIX_TIMESTAMP(), %2, %3, '%4', %5, %6)")
                .arg(RECENT_RECORD).arg(g_TestNumber).arg(id).arg(pName).arg(value).arg(type);
#ifdef DEBUG_MODE
        qDebug() << sqlLine;
#endif
        query.exec(sqlLine);

        if (query.lastError().isValid())
        {
#ifdef DEBUG_MODE
            qDebug() << query.lastError();
#endif
            g_DBConnectionFlag = false;
            emit ErrorInfo(QString("%1:%2").arg("CANThread::SaveToRecentValue").arg(query.lastError().text()));//发送数据给主线程
            return;
        }
    }
}


