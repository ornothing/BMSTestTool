#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "historyrecorddefine.h"
#include "WorkThread.h"
#include "databasedefine.h"
#include "systemdefine.h"

void AppendHistoryListNode(QList<HistoryListNode> *list, QString name, UINT id, float value);

HistoryValue g_HistoryValue;
BMSHistoryStatus g_BMSHistoryStatus;
BMUHistoryStatus g_BMUHistoruStatus[MAX_BMU_NUMBER];
bool g_CurrentTimeFlag;
extern BMSUIData g_GetCANBMSData;
extern BMUUIData g_GetCANBMUData[MAX_BMU_NUMBER];
extern bool g_DBConnectionFlag;
extern unsigned char g_TestNumber;


void InitBMSHisoryRecord()
{
    g_BMSHistoryStatus.bmsMaxCVNO = -1;
    g_BMSHistoryStatus.bmsMinCVNO = -1;
    g_BMSHistoryStatus.bmsMaxCTNO = -1;
    g_BMSHistoryStatus.bmsMinCTNO = -1;
    g_BMSHistoryStatus.maxMCVNO = -1;
    g_BMSHistoryStatus.minMCVNO = -1;
    g_BMSHistoryStatus.maxMCTNO = -1;
    g_BMSHistoryStatus.minMCTNO = -1;

    g_BMSHistoryStatus.globalInfo.pollGlobalInfo = -1;

    g_BMSHistoryStatus.errorStatus.basicStatus = -1;
    g_BMSHistoryStatus.errorStatus.errVoltSensor = -1;
    g_BMSHistoryStatus.errorStatus.errTempSensor = -1;
    g_BMSHistoryStatus.errorStatus.errInnCom = -1;
    g_BMSHistoryStatus.errorStatus.errChrgVoltHigh = -1;
    g_BMSHistoryStatus.errorStatus.errWireInversed = -1;
    g_BMSHistoryStatus.errorStatus.errRelaySticky = -1;
    g_BMSHistoryStatus.errorStatus.almCellVoltLow = -1;
    g_BMSHistoryStatus.errorStatus.almCellVoltHigh = -1;
    g_BMSHistoryStatus.errorStatus.almPackVoltLow = -1;
    g_BMSHistoryStatus.errorStatus.almPackVoltHigh = -1;
    g_BMSHistoryStatus.errorStatus.almChrgTempLow = -1;
    g_BMSHistoryStatus.errorStatus.almChrgTempHigh = -1;
    g_BMSHistoryStatus.errorStatus.almDischrgTempLow = -1;
    g_BMSHistoryStatus.errorStatus.almDischrgTempHigh = -1;
    g_BMSHistoryStatus.errorStatus.almChrgCurrHigh = -1;
    g_BMSHistoryStatus.errorStatus.almDischrgCurrHigh = -1;
    g_BMSHistoryStatus.errorStatus.almMoudleVoltLow = -1;
    g_BMSHistoryStatus.errorStatus.almMoudleVoltHigh = -1;
    g_BMSHistoryStatus.errorStatus.pCellVoltLow = -1;
    g_BMSHistoryStatus.errorStatus.pCellVoltHigh = -1;
    g_BMSHistoryStatus.errorStatus.pPackVoltLow = -1;
    g_BMSHistoryStatus.errorStatus.pPackVoltHigh = -1;
    g_BMSHistoryStatus.errorStatus.pChrgTempLow = -1;
    g_BMSHistoryStatus.errorStatus.pChrgTempHigh = -1;
    g_BMSHistoryStatus.errorStatus.pDischrgTempLow = -1;
    g_BMSHistoryStatus.errorStatus.pDischrgTempHigh = -1;
    g_BMSHistoryStatus.errorStatus.pChrgCurrHigh = -1;
    g_BMSHistoryStatus.errorStatus.pDischrgCurrHigh = -1;
    g_BMSHistoryStatus.errorStatus.pMoudleVoltLow = -1;
    g_BMSHistoryStatus.errorStatus.pMoudleVoltHigh = -1;

    g_BMSHistoryStatus.cellStatus.forceChrgSt = -1;
    g_BMSHistoryStatus.cellStatus.posiRlySt = -1;
    g_BMSHistoryStatus.cellStatus.negRlySt = -1;
    g_BMSHistoryStatus.cellStatus.rlySticky = -1;
    g_BMSHistoryStatus.cellStatus.almSt = -1;

    g_BMSHistoryStatus.cellFault.fatalPOSC = -1;
    g_BMSHistoryStatus.cellFault.fatalBMSSensor = -1;
    g_BMSHistoryStatus.cellFault.fatalBMSAFE = -1;
    g_BMSHistoryStatus.cellFault.fatalBMSCV = -1;
    g_BMSHistoryStatus.cellFault.fatalBMSCT = -1;
    g_BMSHistoryStatus.cellFault.fatalHvcuCom = -1;
    g_BMSHistoryStatus.cellFault.fatalHvcuSensor = -1;

    g_BMSHistoryStatus.command1.chrgForbidenMark = -1;
    g_BMSHistoryStatus.command1.dischrgForbidenMark = -1;

    g_BMSHistoryStatus.command2.sleepCtrl = -1;

    g_BMSHistoryStatus.command3.chrgEN = -1;
    g_BMSHistoryStatus.command3.dischrgEN = -1;

    g_BMSHistoryStatus.command4.relayForceBreak = -1;
}


void InitBMUHisoryRecord()
{
    int i = 0;
    int j =0;
    for (j=0; j<MAX_BMU_NUMBER; j++)
    {
        g_BMUHistoruStatus[j].bmuMaxCVNO = -1;
        g_BMUHistoruStatus[j].bmuMinCVNO = -1;
        g_BMUHistoruStatus[j].bmuMaxCTNO = -1;
        g_BMUHistoruStatus[j].bmuMinCTNO = -1;

        g_BMUHistoruStatus[j].moduleConfig.cellAH = -1;
        g_BMUHistoruStatus[j].moduleConfig.cellRateVolt = -1;
        g_BMUHistoruStatus[j].moduleConfig.cellNum = -1;
        g_BMUHistoruStatus[j].moduleConfig.tempNum = -1;

        g_BMUHistoruStatus[j].status.AFESample = -1;
        g_BMUHistoruStatus[j].status.AFEFault = -1;
        g_BMUHistoruStatus[j].status.OWDSt = -1;
        g_BMUHistoruStatus[j].status.lv1CellVoltLow = -1;
        g_BMUHistoruStatus[j].status.lv1CellVoltHigh = -1;
        g_BMUHistoruStatus[j].status.lv1CellVoltDiff = -1;
        g_BMUHistoruStatus[j].status.lv1MoudleVoltLow = -1;
        g_BMUHistoruStatus[j].status.lv1MoudleVoltHigh = -1;
        g_BMUHistoruStatus[j].status.lv1AmbientTempLow = -1;
        g_BMUHistoruStatus[j].status.lv1AmbientTempHigh = -1;
        g_BMUHistoruStatus[j].status.lv1ChrgTempLow = -1;
        g_BMUHistoruStatus[j].status.lv1ChrgTempHigh = -1;
        g_BMUHistoruStatus[j].status.lv1DischrgTempLow = -1;
        g_BMUHistoruStatus[j].status.lv1DischrgTempHigh = -1;
        g_BMUHistoruStatus[j].status.lv2CellVoltLow = -1;
        g_BMUHistoruStatus[j].status.lv2CellVoltHigh = -1;
        g_BMUHistoruStatus[j].status.lv2CellVoltDiff = -1;
        g_BMUHistoruStatus[j].status.lv2MoudleVoltLow = -1;
        g_BMUHistoruStatus[j].status.lv2MoudleVoltHigh = -1;
        g_BMUHistoruStatus[j].status.lv2AmbientTempLow = -1;
        g_BMUHistoruStatus[j].status.lv2AmbientTempHigh = -1;
        g_BMUHistoruStatus[j].status.lv2ChrgTempLow = -1;
        g_BMUHistoruStatus[j].status.lv2ChrgTempHigh = -1;
        g_BMUHistoruStatus[j].status.lv2DischrgTempLow = -1;
        g_BMUHistoruStatus[j].status.lv2DischrgTempHigh = -1;

        g_BMUHistoruStatus[j].balStatus.cellBalMode = -1;
        g_BMUHistoruStatus[j].balStatus.cellBalSt = -1;

        for (i=0; i<MAX_CELL_VOLT_NUMBER; i++)
        {
            g_BMUHistoruStatus[j].balStatus.cellInBal[i] = -1;
        }
    }
}


void CANThread::SaveBMSCellModelDataToHistoryBuffer(UINT id)
{
    switch (id)
    {
    case 0x4200:
        if (g_BMSHistoryStatus.globalInfo.pollGlobalInfo != g_GetCANBMSData.bmsPoll.pollGlobalInfo)
        {
            g_BMSHistoryStatus.globalInfo.pollGlobalInfo = g_GetCANBMSData.bmsPoll.pollGlobalInfo;
            SaveStatusToHistoryRecord(id, BMS_POLL_GLOBAL_INFO, g_BMSHistoryStatus.globalInfo.pollGlobalInfo, SOURCE_RECORD);
        }
        break;

    case 0x4210:
        AppendHistoryListNode(&g_HistoryValue.packVoltList, BMS_PACK_VOLT, id, g_GetCANBMSData.bmsCellModuleP1.packVolt);
        AppendHistoryListNode(&g_HistoryValue.packCurrList, BMS_PACK_CURR, id, g_GetCANBMSData.bmsCellModuleP1.packCurr);
        AppendHistoryListNode(&g_HistoryValue.ambientTempOutList, BMS_AMBIENT_TEMP_OUT, id, g_GetCANBMSData.bmsCellModuleP1.ambientTempOut);
        AppendHistoryListNode(&g_HistoryValue.bmsSocList, BMS_SOC, id, g_GetCANBMSData.bmsCellModuleP1.SOC);
        AppendHistoryListNode(&g_HistoryValue.packPwrList, BMS_PACK_PWR, id, g_GetCANBMSData.bmsCellModuleP1.packPwr);
        break;

    case 0x18FF02C0:
        AppendHistoryListNode(&g_HistoryValue.ambientTempList, BMS_AMBIENT_TEMP_IN, id, g_GetCANBMSData.bmsCellModuleP2.ambientTemp);
        break;

    case 0x4220:
        AppendHistoryListNode(&g_HistoryValue.maxChgCurrList, BMS_MAX_CHG_CURR, id, g_GetCANBMSData.bmsCellModuleP3.maxChgCurr);
        AppendHistoryListNode(&g_HistoryValue.maxDischgCurrList, BMS_MAX_DISCHG_CURR, id, g_GetCANBMSData.bmsCellModuleP3.maxDischgCurr);
        break;

    default:
        break;
    }
}


void AppendHistoryListNode(QList<HistoryListNode> *list, QString name, UINT id, float value)
{
    HistoryListNode node;
    node.parName = name;
    node.signalID = id;
    node.value = value;
    list->append(node);
}


void CANThread::SaveBMSCellBasicParToHistoryBuffer(UINT id)
{
    switch (id)
    {
    case 0x4230:
        AppendHistoryListNode(&g_HistoryValue.bmsMaxCellVoltList, BMS_MAX_CELL_VLOT, id, g_GetCANBMSData.bmsCellBaiscP1.maxCellVolt);
        AppendHistoryListNode(&g_HistoryValue.bmsMinCellVoltList, BMS_MIN_CELL_VOLT, id, g_GetCANBMSData.bmsCellBaiscP1.minCellVolt);
        if (g_BMSHistoryStatus.bmsMaxCVNO != g_GetCANBMSData.bmsCellBaiscP1.maxCVNO)
        {
            g_BMSHistoryStatus.bmsMaxCVNO = g_GetCANBMSData.bmsCellBaiscP1.maxCVNO;
            SaveStatusToHistoryRecord(id, BMS_MAX_CV_NO, g_BMSHistoryStatus.bmsMaxCVNO, SOURCE_RECORD);
        }
        if (g_BMSHistoryStatus.bmsMinCVNO != g_GetCANBMSData.bmsCellBaiscP1.minCVNO)
        {
            g_BMSHistoryStatus.bmsMinCVNO = g_GetCANBMSData.bmsCellBaiscP1.minCVNO;
            SaveStatusToHistoryRecord(id, BMS_MIN_CV_NO, g_BMSHistoryStatus.bmsMinCVNO, SOURCE_RECORD);
        }
        break;

    case 0x4240:
        AppendHistoryListNode(&g_HistoryValue.maxCellTempList, BMS_MAX_CELL_TEMP, id, g_GetCANBMSData.bmsCellBaiscP2.maxCellTemp);
        AppendHistoryListNode(&g_HistoryValue.minCellTempList, BMS_MIN_CELL_TEMP, id, g_GetCANBMSData.bmsCellBaiscP2.minCellTemp);
        if (g_BMSHistoryStatus.bmsMaxCTNO != g_GetCANBMSData.bmsCellBaiscP2.maxCTNO)
        {
            g_BMSHistoryStatus.bmsMaxCTNO = g_GetCANBMSData.bmsCellBaiscP2.maxCTNO;
            SaveStatusToHistoryRecord(id, BMS_MAX_CT_NO, g_BMSHistoryStatus.bmsMaxCTNO, SOURCE_RECORD);
        }
        if (g_BMSHistoryStatus.bmsMinCTNO != g_GetCANBMSData.bmsCellBaiscP2.minCTNO)
        {
            g_BMSHistoryStatus.bmsMinCTNO = g_GetCANBMSData.bmsCellBaiscP2.minCTNO;
            SaveStatusToHistoryRecord(id, BMS_MIN_CT_NO, g_BMSHistoryStatus.bmsMinCTNO, SOURCE_RECORD);
        }
        break;

    case 0x4260:
        AppendHistoryListNode(&g_HistoryValue.maxMoudleCVList, BMS_MAX_MODULE_CV, id, g_GetCANBMSData.bmsCellBaiscP3.maxMoudleCV);
        AppendHistoryListNode(&g_HistoryValue.minMoudleCVList, BMS_MIN_MODULE_CV, id, g_GetCANBMSData.bmsCellBaiscP3.minMoudleCV);
        if (g_BMSHistoryStatus.maxMCVNO != g_GetCANBMSData.bmsCellBaiscP3.maxMCVNO)
        {
            g_BMSHistoryStatus.maxMCVNO = g_GetCANBMSData.bmsCellBaiscP3.maxMCVNO;
            SaveStatusToHistoryRecord(id, BMS_MAX_MCV_NO, g_BMSHistoryStatus.maxMCVNO, SOURCE_RECORD);
        }
        if (g_BMSHistoryStatus.minMCVNO != g_GetCANBMSData.bmsCellBaiscP3.minMCVNO)
        {
            g_BMSHistoryStatus.minMCVNO = g_GetCANBMSData.bmsCellBaiscP3.minMCVNO;
            SaveStatusToHistoryRecord(id, BMS_MIN_MCV_NO, g_BMSHistoryStatus.minMCVNO, SOURCE_RECORD);
        }
        break;

    case 0x4270:
        AppendHistoryListNode(&g_HistoryValue.maxMoudleCTList, BMS_MAX_MODULE_CT, id, g_GetCANBMSData.bmsCellBaiscP4.maxMoudleCT);
        AppendHistoryListNode(&g_HistoryValue.minMoudleCTList, BMS_MIN_MOUDLE_CT, id, g_GetCANBMSData.bmsCellBaiscP4.minMoudleCT);
        if (g_BMSHistoryStatus.maxMCTNO != g_GetCANBMSData.bmsCellBaiscP4.maxMCTNO)
        {
            g_BMSHistoryStatus.maxMCTNO = g_GetCANBMSData.bmsCellBaiscP4.maxMCTNO;
            SaveStatusToHistoryRecord(id, BMS_MAX_MCT_NO, g_BMSHistoryStatus.maxMCTNO, SOURCE_RECORD);
        }
        if (g_BMSHistoryStatus.minMCTNO != g_GetCANBMSData.bmsCellBaiscP4.minMCTNO)
        {
            g_BMSHistoryStatus.minMCTNO = g_GetCANBMSData.bmsCellBaiscP4.minMCTNO;
            SaveStatusToHistoryRecord(id, BMS_MIN_MCT_NO, g_BMSHistoryStatus.minMCTNO, SOURCE_RECORD);
        }
        break;

    default:
        break;
    }
}


void CANThread::SaveBMSCommandToHistoryBuffer(UINT id)
{
    switch(id)
    {
    case 0x4280:
        if (g_BMSHistoryStatus.command1.chrgForbidenMark != g_GetCANBMSData.bmsCommand1.chrgForbidenMark)
        {
            g_BMSHistoryStatus.command1.chrgForbidenMark = g_GetCANBMSData.bmsCommand1.chrgForbidenMark;
            SaveStatusToHistoryRecord(id, BMS_CHRG_FORBIDEN_MARK, g_BMSHistoryStatus.command1.chrgForbidenMark, SOURCE_RECORD);
        }
        if (g_BMSHistoryStatus.command1.dischrgForbidenMark != g_GetCANBMSData.bmsCommand1.dischrgForbidenMark)
        {
            g_BMSHistoryStatus.command1.dischrgForbidenMark = g_GetCANBMSData.bmsCommand1.dischrgForbidenMark;
            SaveStatusToHistoryRecord(id, BMS_DISCHRG_FORBIDEN_MARK, g_BMSHistoryStatus.command1.dischrgForbidenMark, SOURCE_RECORD);
        }
        break;

    case 0x8200:
        if (g_BMSHistoryStatus.command2.sleepCtrl != g_GetCANBMSData.bmsCommand2.sleepCtrl)
        {
            g_BMSHistoryStatus.command2.sleepCtrl = g_GetCANBMSData.bmsCommand2.sleepCtrl;
            SaveStatusToHistoryRecord(id, BMS_SLEEP_CTRL, g_BMSHistoryStatus.command2.sleepCtrl, SOURCE_RECORD);
        }
        break;

    case 0x8210:
        if (g_BMSHistoryStatus.command3.chrgEN != g_GetCANBMSData.bmsCommand3.chrgEN)
        {
            g_BMSHistoryStatus.command3.chrgEN = g_GetCANBMSData.bmsCommand3.chrgEN;
            SaveStatusToHistoryRecord(id, BMS_CHRG_EN, g_BMSHistoryStatus.command3.chrgEN, SOURCE_RECORD);
        }
        if (g_BMSHistoryStatus.command3.dischrgEN != g_GetCANBMSData.bmsCommand3.dischrgEN)
        {
            g_BMSHistoryStatus.command3.dischrgEN = g_GetCANBMSData.bmsCommand3.dischrgEN;
            SaveStatusToHistoryRecord(id, BMS_DISCHRG_EN, g_BMSHistoryStatus.command3.dischrgEN, SOURCE_RECORD);
        }
        break;

    case 0x8220:
        if (g_BMSHistoryStatus.command4.relayForceBreak != g_GetCANBMSData.bmsCommand4.relayForceBreak)
        {
            g_BMSHistoryStatus.command4.relayForceBreak = g_GetCANBMSData.bmsCommand4.relayForceBreak;
            SaveStatusToHistoryRecord(id, BMS_RELAY_FORCE_BREAK, g_BMSHistoryStatus.command4.relayForceBreak, SOURCE_RECORD);
        }
        break;

    default:
        break;
    }
}


void CANThread::SaveBMSCellErrorToHistoryBuffer(UINT id)
{
    if (g_BMSHistoryStatus.errorStatus.basicStatus != g_GetCANBMSData.bmsCellError.basicStatus)
    {
        g_BMSHistoryStatus.errorStatus.basicStatus = g_GetCANBMSData.bmsCellError.basicStatus;
        SaveStatusToHistoryRecord(id, BMS_BASIC_STATUS, g_BMSHistoryStatus.errorStatus.basicStatus, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.errVoltSensor != g_GetCANBMSData.bmsCellError.errVoltSensor)
    {
        g_BMSHistoryStatus.errorStatus.errVoltSensor = g_GetCANBMSData.bmsCellError.errVoltSensor;
        SaveStatusToHistoryRecord(id, BMS_ERR_VOLT_SENSOR, g_BMSHistoryStatus.errorStatus.errVoltSensor, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.errTempSensor != g_GetCANBMSData.bmsCellError.errTempSensor)
    {
        g_BMSHistoryStatus.errorStatus.errTempSensor = g_GetCANBMSData.bmsCellError.errTempSensor;
        SaveStatusToHistoryRecord(id, BMS_ERR_TEMP_SENSOR, g_BMSHistoryStatus.errorStatus.errTempSensor, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.errInnCom != g_GetCANBMSData.bmsCellError.errInnCom)
    {
        g_BMSHistoryStatus.errorStatus.errInnCom = g_GetCANBMSData.bmsCellError.errInnCom;
        SaveStatusToHistoryRecord(id, BMS_ERR_INN_COM, g_BMSHistoryStatus.errorStatus.errInnCom, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.errChrgVoltHigh != g_GetCANBMSData.bmsCellError.errChrgVoltHigh)
    {
        g_BMSHistoryStatus.errorStatus.errChrgVoltHigh = g_GetCANBMSData.bmsCellError.errChrgVoltHigh;
        SaveStatusToHistoryRecord(id, BMS_ERR_CHRG_VOLT_HIGH, g_BMSHistoryStatus.errorStatus.errChrgVoltHigh, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.errWireInversed != g_GetCANBMSData.bmsCellError.errWireInversed)
    {
        g_BMSHistoryStatus.errorStatus.errWireInversed = g_GetCANBMSData.bmsCellError.errWireInversed;
        SaveStatusToHistoryRecord(id, BMS_ERR_WIRE_INVERSED, g_BMSHistoryStatus.errorStatus.errWireInversed, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.errRelaySticky != g_GetCANBMSData.bmsCellError.errRelaySticky)
    {
        g_BMSHistoryStatus.errorStatus.errRelaySticky = g_GetCANBMSData.bmsCellError.errRelaySticky;
        SaveStatusToHistoryRecord(id, BMS_ERR_RELAY_STICKY, g_BMSHistoryStatus.errorStatus.errRelaySticky, SOURCE_RECORD);
    }


    if (g_BMSHistoryStatus.errorStatus.almCellVoltLow != g_GetCANBMSData.bmsCellError.almCellVoltLow)
    {
        g_BMSHistoryStatus.errorStatus.almCellVoltLow = g_GetCANBMSData.bmsCellError.almCellVoltLow;
        SaveStatusToHistoryRecord(id, BMS_ALM_CELL_VOLT_LOW, g_BMSHistoryStatus.errorStatus.almCellVoltLow, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.almCellVoltHigh != g_GetCANBMSData.bmsCellError.almCellVoltHigh)
    {
        g_BMSHistoryStatus.errorStatus.almCellVoltHigh = g_GetCANBMSData.bmsCellError.almCellVoltHigh;
        SaveStatusToHistoryRecord(id, BMS_ALM_CELL_VOLT_HIGH, g_BMSHistoryStatus.errorStatus.almCellVoltHigh, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.almPackVoltLow != g_GetCANBMSData.bmsCellError.almPackVoltLow)
    {
        g_BMSHistoryStatus.errorStatus.almPackVoltLow = g_GetCANBMSData.bmsCellError.almPackVoltLow;
        SaveStatusToHistoryRecord(id, BMS_ALM_PACK_VOLT_LOW, g_BMSHistoryStatus.errorStatus.almPackVoltLow, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.almPackVoltHigh != g_GetCANBMSData.bmsCellError.almPackVoltHigh)
    {
        g_BMSHistoryStatus.errorStatus.almPackVoltHigh = g_GetCANBMSData.bmsCellError.almPackVoltHigh;
        SaveStatusToHistoryRecord(id, BMS_ALM_PACK_VOLT_HIGH, g_BMSHistoryStatus.errorStatus.almPackVoltHigh, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.almChrgTempLow != g_GetCANBMSData.bmsCellError.almChrgTempLow)
    {
        g_BMSHistoryStatus.errorStatus.almChrgTempLow = g_GetCANBMSData.bmsCellError.almChrgTempLow;
        SaveStatusToHistoryRecord(id, BMS_ALM_CHRG_TEMP_LOW, g_BMSHistoryStatus.errorStatus.almChrgTempLow, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.almChrgTempHigh != g_GetCANBMSData.bmsCellError.almChrgTempHigh)
    {
        g_BMSHistoryStatus.errorStatus.almChrgTempHigh = g_GetCANBMSData.bmsCellError.almChrgTempHigh;
        SaveStatusToHistoryRecord(id, BMS_ALM_CHRG_TEMP_HIGH, g_BMSHistoryStatus.errorStatus.almChrgTempHigh, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.almDischrgTempLow != g_GetCANBMSData.bmsCellError.almDischrgTempLow)
    {
        g_BMSHistoryStatus.errorStatus.almDischrgTempLow = g_GetCANBMSData.bmsCellError.almDischrgTempLow;
        SaveStatusToHistoryRecord(id, BMS_ALM_DISCHRG_TEMP_LOW, g_BMSHistoryStatus.errorStatus.almDischrgTempLow, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.almDischrgTempHigh != g_GetCANBMSData.bmsCellError.almDischrgTempHigh)
    {
        g_BMSHistoryStatus.errorStatus.almDischrgTempHigh = g_GetCANBMSData.bmsCellError.almDischrgTempHigh;
        SaveStatusToHistoryRecord(id, BMS_ALM_DISCHRG_TEMP_HIGH, g_BMSHistoryStatus.errorStatus.almDischrgTempHigh, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.almChrgCurrHigh != g_GetCANBMSData.bmsCellError.almChrgCurrHigh)
    {
        g_BMSHistoryStatus.errorStatus.almChrgCurrHigh = g_GetCANBMSData.bmsCellError.almChrgCurrHigh;
        SaveStatusToHistoryRecord(id, BMS_ALM_CHRG_CURR_HIGH, g_BMSHistoryStatus.errorStatus.almChrgCurrHigh, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.almDischrgCurrHigh != g_GetCANBMSData.bmsCellError.almDischrgCurrHigh)
    {
        g_BMSHistoryStatus.errorStatus.almDischrgCurrHigh = g_GetCANBMSData.bmsCellError.almDischrgCurrHigh;
        SaveStatusToHistoryRecord(id, BMS_ALM_DISCHRG_CURR_HIGH, g_BMSHistoryStatus.errorStatus.almDischrgCurrHigh, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.almMoudleVoltLow != g_GetCANBMSData.bmsCellError.almMoudleVoltLow)
    {
        g_BMSHistoryStatus.errorStatus.almMoudleVoltLow = g_GetCANBMSData.bmsCellError.almMoudleVoltLow;
        SaveStatusToHistoryRecord(id, BMS_ALM_MODULE_VOLT_LOW, g_BMSHistoryStatus.errorStatus.almMoudleVoltLow, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.almMoudleVoltHigh != g_GetCANBMSData.bmsCellError.almMoudleVoltHigh)
    {
        g_BMSHistoryStatus.errorStatus.almMoudleVoltHigh = g_GetCANBMSData.bmsCellError.almMoudleVoltHigh;
        SaveStatusToHistoryRecord(id, BMS_ALM_MODULE_VOLT_HIGH, g_BMSHistoryStatus.errorStatus.almMoudleVoltHigh, SOURCE_RECORD);
    }


    if (g_BMSHistoryStatus.errorStatus.pCellVoltLow != g_GetCANBMSData.bmsCellError.pCellVoltLow)
    {
        g_BMSHistoryStatus.errorStatus.pCellVoltLow = g_GetCANBMSData.bmsCellError.pCellVoltLow;
        SaveStatusToHistoryRecord(id, BMS_P_CELL_VOLT_LOW, g_BMSHistoryStatus.errorStatus.pCellVoltLow, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.pCellVoltHigh != g_GetCANBMSData.bmsCellError.pCellVoltHigh)
    {
        g_BMSHistoryStatus.errorStatus.pCellVoltHigh = g_GetCANBMSData.bmsCellError.pCellVoltHigh;
        SaveStatusToHistoryRecord(id, BMS_P_CELL_VOLT_HIGH, g_BMSHistoryStatus.errorStatus.pCellVoltHigh, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.pPackVoltLow != g_GetCANBMSData.bmsCellError.pPackVoltLow)
    {
        g_BMSHistoryStatus.errorStatus.pPackVoltLow = g_GetCANBMSData.bmsCellError.pPackVoltLow;
        SaveStatusToHistoryRecord(id, BMS_P_PACK_VOLT_LOW, g_BMSHistoryStatus.errorStatus.pPackVoltLow, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.pPackVoltHigh != g_GetCANBMSData.bmsCellError.pPackVoltHigh)
    {
        g_BMSHistoryStatus.errorStatus.pPackVoltHigh = g_GetCANBMSData.bmsCellError.pPackVoltHigh;
        SaveStatusToHistoryRecord(id, BMS_P_PACK_VOLT_HIGH, g_BMSHistoryStatus.errorStatus.pPackVoltHigh, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.pChrgTempLow != g_GetCANBMSData.bmsCellError.pChrgTempLow)
    {
        g_BMSHistoryStatus.errorStatus.pChrgTempLow = g_GetCANBMSData.bmsCellError.pChrgTempLow;
        SaveStatusToHistoryRecord(id, BMS_P_CHRG_TEMP_LOW, g_BMSHistoryStatus.errorStatus.pChrgTempLow, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.pChrgTempHigh != g_GetCANBMSData.bmsCellError.pChrgTempHigh)
    {
        g_BMSHistoryStatus.errorStatus.pChrgTempHigh = g_GetCANBMSData.bmsCellError.pChrgTempHigh;
        SaveStatusToHistoryRecord(id, BMS_P_CHRG_TEMP_HIGH, g_BMSHistoryStatus.errorStatus.pChrgTempHigh, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.pDischrgTempLow != g_GetCANBMSData.bmsCellError.pDischrgTempLow)
    {
        g_BMSHistoryStatus.errorStatus.pDischrgTempLow = g_GetCANBMSData.bmsCellError.pDischrgTempLow;
        SaveStatusToHistoryRecord(id, BMS_P_DISCHRG_TEMP_LOW, g_BMSHistoryStatus.errorStatus.pDischrgTempLow, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.pDischrgTempHigh != g_GetCANBMSData.bmsCellError.pDischrgTempHigh)
    {
        g_BMSHistoryStatus.errorStatus.pDischrgTempHigh = g_GetCANBMSData.bmsCellError.pDischrgTempHigh;
        SaveStatusToHistoryRecord(id, BMS_P_DISCHRG_TEMP_HIGH, g_BMSHistoryStatus.errorStatus.pDischrgTempHigh, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.pChrgCurrHigh != g_GetCANBMSData.bmsCellError.pChrgCurrHigh)
    {
        g_BMSHistoryStatus.errorStatus.pChrgCurrHigh = g_GetCANBMSData.bmsCellError.pChrgCurrHigh;
        SaveStatusToHistoryRecord(id, BMS_P_CHRG_CURR_HIGH, g_BMSHistoryStatus.errorStatus.pChrgCurrHigh, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.pDischrgCurrHigh != g_GetCANBMSData.bmsCellError.pDischrgCurrHigh)
    {
        g_BMSHistoryStatus.errorStatus.pDischrgCurrHigh = g_GetCANBMSData.bmsCellError.pDischrgCurrHigh;
        SaveStatusToHistoryRecord(id, BMS_P_DISCHRG_CURR_HIGH, g_BMSHistoryStatus.errorStatus.pDischrgCurrHigh, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.pMoudleVoltLow != g_GetCANBMSData.bmsCellError.pMoudleVoltLow)
    {
        g_BMSHistoryStatus.errorStatus.pMoudleVoltLow = g_GetCANBMSData.bmsCellError.pMoudleVoltLow;
        SaveStatusToHistoryRecord(id, BMS_P_MODULE_VOLT_LOW, g_BMSHistoryStatus.errorStatus.pMoudleVoltLow, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.errorStatus.pMoudleVoltHigh != g_GetCANBMSData.bmsCellError.pMoudleVoltHigh)
    {
        g_BMSHistoryStatus.errorStatus.pMoudleVoltHigh = g_GetCANBMSData.bmsCellError.pMoudleVoltHigh;
        SaveStatusToHistoryRecord(id, BMS_P_MODULE_VOLT_HIGH, g_BMSHistoryStatus.errorStatus.pMoudleVoltHigh, SOURCE_RECORD);
    }
}

void CANThread::SaveBMSCellStatusToHistoryBuffer(UINT id)
{
    if (g_BMSHistoryStatus.cellStatus.forceChrgSt != g_GetCANBMSData.bmsCellStatus.forceChrgSt)
    {
        g_BMSHistoryStatus.cellStatus.forceChrgSt = g_GetCANBMSData.bmsCellStatus.forceChrgSt;
        SaveStatusToHistoryRecord(id, BMS_FORCE_CHRG_ST, g_BMSHistoryStatus.cellStatus.forceChrgSt, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.cellStatus.posiRlySt != g_GetCANBMSData.bmsCellStatus.posiRlySt)
    {
        g_BMSHistoryStatus.cellStatus.posiRlySt = g_GetCANBMSData.bmsCellStatus.posiRlySt;
        SaveStatusToHistoryRecord(id, BMS_POSI_RLY_ST, g_BMSHistoryStatus.cellStatus.posiRlySt, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.cellStatus.negRlySt != g_GetCANBMSData.bmsCellStatus.negRlySt)
    {
        g_BMSHistoryStatus.cellStatus.negRlySt = g_GetCANBMSData.bmsCellStatus.negRlySt;
        SaveStatusToHistoryRecord(id, BMS_NEG_RLY_ST, g_BMSHistoryStatus.cellStatus.negRlySt, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.cellStatus.rlySticky != g_GetCANBMSData.bmsCellStatus.rlySticky)
    {
        g_BMSHistoryStatus.cellStatus.rlySticky = g_GetCANBMSData.bmsCellStatus.rlySticky;
        SaveStatusToHistoryRecord(id, BMS_RLY_STICKY, g_BMSHistoryStatus.cellStatus.rlySticky, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.cellStatus.almSt != g_GetCANBMSData.bmsCellStatus.almSt)
    {
        g_BMSHistoryStatus.cellStatus.almSt = g_GetCANBMSData.bmsCellStatus.almSt;
        SaveStatusToHistoryRecord(id, BMS_ALM_ST, g_BMSHistoryStatus.cellStatus.almSt, SOURCE_RECORD);
    }
}


void CANThread::SaveBMSCellFaultToHistoryBuffer(UINT id)
{
    if (g_BMSHistoryStatus.cellFault.fatalBMSSensor != g_GetCANBMSData.bmsCellFault.fatalBMSSensor)
    {
        g_BMSHistoryStatus.cellFault.fatalBMSSensor = g_GetCANBMSData.bmsCellFault.fatalBMSSensor;
        SaveStatusToHistoryRecord(id, BMS_FATAL_BMU_SENSOR, g_BMSHistoryStatus.cellFault.fatalBMSSensor, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.cellFault.fatalBMSAFE != g_GetCANBMSData.bmsCellFault.fatalBMSAFE)
    {
        g_BMSHistoryStatus.cellFault.fatalBMSAFE = g_GetCANBMSData.bmsCellFault.fatalBMSAFE;
        SaveStatusToHistoryRecord(id, BMS_FATAL_BMU_AFE, g_BMSHistoryStatus.cellFault.fatalBMSAFE, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.cellFault.fatalBMSCV != g_GetCANBMSData.bmsCellFault.fatalBMSCV)
    {
        g_BMSHistoryStatus.cellFault.fatalBMSCV = g_GetCANBMSData.bmsCellFault.fatalBMSCV;
        SaveStatusToHistoryRecord(id, BMS_FATAL_BMU_CV, g_BMSHistoryStatus.cellFault.fatalBMSCV, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.cellFault.fatalBMSCT != g_GetCANBMSData.bmsCellFault.fatalBMSCT)
    {
        g_BMSHistoryStatus.cellFault.fatalBMSCT = g_GetCANBMSData.bmsCellFault.fatalBMSCT;
        SaveStatusToHistoryRecord(id, BMS_FATAL_BMU_VT, g_BMSHistoryStatus.cellFault.fatalBMSCT, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.cellFault.fatalHvcuCom != g_GetCANBMSData.bmsCellFault.fatalHvcuCom)
    {
        g_BMSHistoryStatus.cellFault.fatalHvcuCom = g_GetCANBMSData.bmsCellFault.fatalHvcuCom;
        SaveStatusToHistoryRecord(id, BMS_FATAL_HVCU_COM, g_BMSHistoryStatus.cellFault.fatalHvcuCom, SOURCE_RECORD);
    }
    if (g_BMSHistoryStatus.cellFault.fatalHvcuSensor != g_GetCANBMSData.bmsCellFault.fatalHvcuSensor)
    {
        g_BMSHistoryStatus.cellFault.fatalHvcuSensor = g_GetCANBMSData.bmsCellFault.fatalHvcuSensor;
        SaveStatusToHistoryRecord(id, BMS_FATAL_HVCU_SENSOR, g_BMSHistoryStatus.cellFault.fatalHvcuSensor, SOURCE_RECORD);
    }
}


void CANThread::SaveBMUBasicParToHistoryBuffer(UINT id)
{
    unsigned int index = 0;
    index = id & 0x0000000f;
    UINT partID = 0;
    partID = id >> 4;

    switch(partID)
    {
    case 0x18FF01B:
        AppendHistoryListNode(&g_HistoryValue.bmuSocList, BMU_SOC, id, g_GetCANBMUData[index].bmuBasicP1.SOC);
        AppendHistoryListNode(&g_HistoryValue.diffCellVoltList, BMU_DIFF_CELL_VOLT, id, g_GetCANBMUData[index].bmuBasicP1.diffCellVolt);
        AppendHistoryListNode(&g_HistoryValue.diffCellTempList, BMU_DIFF_CELL_TEMP, id, g_GetCANBMUData[index].bmuBasicP1.diffCellTemp);
        break;
    case 0x18FF02B:
        AppendHistoryListNode(&g_HistoryValue.moudleVoltList, BMU_MODULE_VOLT, id, g_GetCANBMUData[index].bmuBasicP2.moudleVolt);
        AppendHistoryListNode(&g_HistoryValue.boardTempList, BMU_BOARD_TEMP, id, g_GetCANBMUData[index].bmuBasicP2.boardTemp);

    case 0x18FF10B:
        if (g_BMUHistoruStatus[index].bmuMaxCVNO != g_GetCANBMUData[index].bmuBasicP3.maxCVNO)
        {
            g_BMUHistoruStatus[index].bmuMaxCVNO = g_GetCANBMUData[index].bmuBasicP3.maxCVNO;
            SaveStatusToHistoryRecord(id, BMU_MAX_CV_NO, g_BMUHistoruStatus[index].bmuMaxCVNO, SOURCE_RECORD);
        }
        if (g_BMUHistoruStatus[index].bmuMinCVNO != g_GetCANBMUData[index].bmuBasicP3.minCVNO)
        {
            g_BMUHistoruStatus[index].bmuMinCVNO = g_GetCANBMUData[index].bmuBasicP3.minCVNO;
            SaveStatusToHistoryRecord(id, BMU_MIN_CV_NO, g_BMUHistoruStatus[index].bmuMinCVNO, SOURCE_RECORD);
        }
        break;

    case 0x18FF20B:
        if (g_BMUHistoruStatus[index].bmuMaxCTNO != g_GetCANBMUData[index].bmuBasicP4.maxCTNO)
        {
            g_BMUHistoruStatus[index].bmuMaxCTNO = g_GetCANBMUData[index].bmuBasicP4.maxCTNO;
            SaveStatusToHistoryRecord(id, BMU_MAX_CT_NO, g_BMUHistoruStatus[index].bmuMaxCTNO, SOURCE_RECORD);
        }
        if (g_BMUHistoruStatus[index].bmuMinCTNO != g_GetCANBMUData[index].bmuBasicP4.minCTNO)
        {
            g_BMUHistoruStatus[index].bmuMinCTNO = g_GetCANBMUData[index].bmuBasicP4.minCTNO;
            SaveStatusToHistoryRecord(id, BMU_MIN_CT_NO, g_BMUHistoruStatus[index].bmuMinCTNO, SOURCE_RECORD);
        }
        break;

    default:
        break;
    }
}


void CANThread::SaveBMUCellVoltToHistoryBuffer(UINT id)
{
    unsigned int index = 0;
    index = id & 0x0000000f;
    UINT partID = 0;
    partID = id >> 4;

    switch(partID)
    {
    case 0x18FF40B:
        AppendHistoryListNode(&g_HistoryValue.cellVolt0, BMU_CELL_VOLT_0, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[0]);
        AppendHistoryListNode(&g_HistoryValue.cellVolt1, BMU_CELL_VOLT_1, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[1]);
        AppendHistoryListNode(&g_HistoryValue.cellVolt2, BMU_CELL_VOLT_2, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[2]);
        AppendHistoryListNode(&g_HistoryValue.cellVolt3, BMU_CELL_VOLT_3, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[3]);
        break;
    case 0x18FF41B:
        AppendHistoryListNode(&g_HistoryValue.cellVolt4, BMU_CELL_VOLT_4, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[4]);
        AppendHistoryListNode(&g_HistoryValue.cellVolt5, BMU_CELL_VOLT_5, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[5]);
        AppendHistoryListNode(&g_HistoryValue.cellVolt6, BMU_CELL_VOLT_6, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[6]);
        AppendHistoryListNode(&g_HistoryValue.cellVolt7, BMU_CELL_VOLT_7, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[7]);
        break;
    case 0x18FF42B:
        AppendHistoryListNode(&g_HistoryValue.cellVolt8, BMU_CELL_VOLT_8, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[8]);
        AppendHistoryListNode(&g_HistoryValue.cellVolt9, BMU_CELL_VOLT_9, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[9]);
        AppendHistoryListNode(&g_HistoryValue.cellVolt10, BMU_CELL_VOLT_10, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[10]);
        AppendHistoryListNode(&g_HistoryValue.cellVolt11, BMU_CELL_VOLT_11, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[11]);
        break;
    case 0x18FF43B:
        AppendHistoryListNode(&g_HistoryValue.cellVolt12, BMU_CELL_VOLT_12, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[12]);
        AppendHistoryListNode(&g_HistoryValue.cellVolt13, BMU_CELL_VOLT_13, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[13]);
        AppendHistoryListNode(&g_HistoryValue.cellVolt14, BMU_CELL_VOLT_14, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[14]);
        AppendHistoryListNode(&g_HistoryValue.cellVolt15, BMU_CELL_VOLT_15, id, g_GetCANBMUData[index].bmuCellVolt.cellVolt[15]);
        break;
    default:
        break;
    }
}


void CANThread::SaveBMUCellTempToHistoryBuffer(UINT id)
{
    unsigned int index = 0;
    index = id & 0x0000000f;

    AppendHistoryListNode(&g_HistoryValue.cellTemp0, BMU_CELL_VOLT_0, id, g_GetCANBMUData[index].bmuCellTemp.cellTemp[0]);
    AppendHistoryListNode(&g_HistoryValue.cellTemp1, BMU_CELL_VOLT_0, id, g_GetCANBMUData[index].bmuCellTemp.cellTemp[1]);
    AppendHistoryListNode(&g_HistoryValue.cellTemp2, BMU_CELL_VOLT_0, id, g_GetCANBMUData[index].bmuCellTemp.cellTemp[2]);
    AppendHistoryListNode(&g_HistoryValue.cellTemp3, BMU_CELL_VOLT_0, id, g_GetCANBMUData[index].bmuCellTemp.cellTemp[3]);
}


void CANThread::SaveBMUModuleConfigToHistoryBuffer(UINT id)
{
    unsigned int index = 0;
    index = id & 0x0000000f;

    if (g_BMUHistoruStatus[index].moduleConfig.cellAH != g_GetCANBMUData[index].bmuModuleConfig.cellAH)
    {
        g_BMUHistoruStatus[index].moduleConfig.cellAH = g_GetCANBMUData[index].bmuModuleConfig.cellAH;
        SaveStatusToHistoryRecord(id, BMU_CELL_AH, g_BMUHistoruStatus[index].moduleConfig.cellAH, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].moduleConfig.cellRateVolt != g_GetCANBMUData[index].bmuModuleConfig.cellRateVolt)
    {
        g_BMUHistoruStatus[index].moduleConfig.cellRateVolt = g_GetCANBMUData[index].bmuModuleConfig.cellRateVolt;
        SaveStatusToHistoryRecord(id, BMU_CELL_RATE_VOLT, g_BMUHistoruStatus[index].moduleConfig.cellRateVolt, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].moduleConfig.cellNum != g_GetCANBMUData[index].bmuModuleConfig.cellNum)
    {
        g_BMUHistoruStatus[index].moduleConfig.cellNum = g_GetCANBMUData[index].bmuModuleConfig.cellNum;
        SaveStatusToHistoryRecord(id, BMU_CELL_NUM, g_BMUHistoruStatus[index].moduleConfig.cellNum, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].moduleConfig.tempNum != g_GetCANBMUData[index].bmuModuleConfig.tempNum)
    {
        g_BMUHistoruStatus[index].moduleConfig.tempNum = g_GetCANBMUData[index].bmuModuleConfig.tempNum;
        SaveStatusToHistoryRecord(id, BMU_TEMP_NUM, g_BMUHistoruStatus[index].moduleConfig.tempNum, SOURCE_RECORD);
    }
}


void CANThread::SaveBMUStatusToHistoryBuffer(UINT id)
{
    unsigned int index = 0;
    index = id & 0x0000000f;

    if (g_BMUHistoruStatus[index].status.AFESample != g_GetCANBMUData[index].bmuStatus.AFESample)
    {
        g_BMUHistoruStatus[index].status.AFESample = g_GetCANBMUData[index].bmuStatus.AFESample;
        SaveStatusToHistoryRecord(id, BMU_AFE_SAMPLE, g_BMUHistoruStatus[index].status.AFESample, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.AFEFault != g_GetCANBMUData[index].bmuStatus.AFEFault)
    {
        g_BMUHistoruStatus[index].status.AFEFault = g_GetCANBMUData[index].bmuStatus.AFEFault;
        SaveStatusToHistoryRecord(id, BMU_AFE_FAULT, g_BMUHistoruStatus[index].status.AFEFault, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.OWDSt != g_GetCANBMUData[index].bmuStatus.OWDSt)
    {
        g_BMUHistoruStatus[index].status.OWDSt = g_GetCANBMUData[index].bmuStatus.OWDSt;
        SaveStatusToHistoryRecord(id, BMU_OWD_ST, g_BMUHistoruStatus[index].status.OWDSt, SOURCE_RECORD);
    }


    if (g_BMUHistoruStatus[index].status.lv1CellVoltLow != g_GetCANBMUData[index].bmuStatus.lv1CellVoltLow)
    {
        g_BMUHistoruStatus[index].status.lv1CellVoltLow = g_GetCANBMUData[index].bmuStatus.lv1CellVoltLow;
        SaveStatusToHistoryRecord(id, BMU_LV1_CELL_VOLT_LOW, g_BMUHistoruStatus[index].status.lv1CellVoltLow, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv1CellVoltHigh != g_GetCANBMUData[index].bmuStatus.lv1CellVoltHigh)
    {
        g_BMUHistoruStatus[index].status.lv1CellVoltHigh = g_GetCANBMUData[index].bmuStatus.lv1CellVoltHigh;
        SaveStatusToHistoryRecord(id, BMU_LV1_CELL_VOLT_HIGH, g_BMUHistoruStatus[index].status.lv1CellVoltHigh, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv1CellVoltDiff != g_GetCANBMUData[index].bmuStatus.lv1CellVoltDiff)
    {
        g_BMUHistoruStatus[index].status.lv1CellVoltDiff = g_GetCANBMUData[index].bmuStatus.lv1CellVoltDiff;
        SaveStatusToHistoryRecord(id, BMU_LV1_CELL_VOLT_DIFF, g_BMUHistoruStatus[index].status.lv1CellVoltDiff, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv1MoudleVoltLow != g_GetCANBMUData[index].bmuStatus.lv1MoudleVoltLow)
    {
        g_BMUHistoruStatus[index].status.lv1MoudleVoltLow = g_GetCANBMUData[index].bmuStatus.lv1MoudleVoltLow;
        SaveStatusToHistoryRecord(id, BMU_LV1_MODULE_VOLT_LOW, g_BMUHistoruStatus[index].status.lv1MoudleVoltLow, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv1MoudleVoltHigh != g_GetCANBMUData[index].bmuStatus.lv1MoudleVoltHigh)
    {
        g_BMUHistoruStatus[index].status.lv1MoudleVoltHigh = g_GetCANBMUData[index].bmuStatus.lv1MoudleVoltHigh;
        SaveStatusToHistoryRecord(id, BMU_LV1_MODULE_VOLT_HIGH, g_BMUHistoruStatus[index].status.lv1MoudleVoltHigh, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv1AmbientTempLow != g_GetCANBMUData[index].bmuStatus.lv1AmbientTempLow)
    {
        g_BMUHistoruStatus[index].status.lv1AmbientTempLow = g_GetCANBMUData[index].bmuStatus.lv1AmbientTempLow;
        SaveStatusToHistoryRecord(id, BMU_LV1_AMBIENT_TEMP_LOW, g_BMUHistoruStatus[index].status.lv1AmbientTempLow, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv1AmbientTempHigh != g_GetCANBMUData[index].bmuStatus.lv1AmbientTempHigh)
    {
        g_BMUHistoruStatus[index].status.lv1AmbientTempHigh = g_GetCANBMUData[index].bmuStatus.lv1AmbientTempHigh;
        SaveStatusToHistoryRecord(id, BMU_LV1_AMBIENT_TEMP_HIGH, g_BMUHistoruStatus[index].status.lv1AmbientTempHigh, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv1ChrgTempLow != g_GetCANBMUData[index].bmuStatus.lv1ChrgTempLow)
    {
        g_BMUHistoruStatus[index].status.lv1ChrgTempLow = g_GetCANBMUData[index].bmuStatus.lv1ChrgTempLow;
        SaveStatusToHistoryRecord(id, BMU_LV1_CHRG_TEMP_LOW, g_BMUHistoruStatus[index].status.lv1ChrgTempLow, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv1ChrgTempHigh != g_GetCANBMUData[index].bmuStatus.lv1ChrgTempHigh)
    {
        g_BMUHistoruStatus[index].status.lv1ChrgTempHigh = g_GetCANBMUData[index].bmuStatus.lv1ChrgTempHigh;
        SaveStatusToHistoryRecord(id, BMU_LV1_CHRG_TEMP_HIGH, g_BMUHistoruStatus[index].status.lv1ChrgTempHigh, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv1DischrgTempLow != g_GetCANBMUData[index].bmuStatus.lv1DischrgTempLow)
    {
        g_BMUHistoruStatus[index].status.lv1DischrgTempLow = g_GetCANBMUData[index].bmuStatus.lv1DischrgTempLow;
        SaveStatusToHistoryRecord(id, BMU_LV1_DISCHRG_TEMP_LOW, g_BMUHistoruStatus[index].status.lv1DischrgTempLow, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv1DischrgTempHigh != g_GetCANBMUData[index].bmuStatus.lv1DischrgTempHigh)
    {
        g_BMUHistoruStatus[index].status.lv1DischrgTempHigh = g_GetCANBMUData[index].bmuStatus.lv1DischrgTempHigh;
        SaveStatusToHistoryRecord(id, BMU_LV1_DISCHRG_TEMP_HIGH, g_BMUHistoruStatus[index].status.lv1DischrgTempHigh, SOURCE_RECORD);
    }


    if (g_BMUHistoruStatus[index].status.lv2CellVoltLow != g_GetCANBMUData[index].bmuStatus.lv2CellVoltLow)
    {
        g_BMUHistoruStatus[index].status.lv2CellVoltLow = g_GetCANBMUData[index].bmuStatus.lv2CellVoltLow;
        SaveStatusToHistoryRecord(id, BMU_LV2_CELL_VOLT_LOW, g_BMUHistoruStatus[index].status.lv2CellVoltLow, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv2CellVoltHigh != g_GetCANBMUData[index].bmuStatus.lv2CellVoltHigh)
    {
        g_BMUHistoruStatus[index].status.lv2CellVoltHigh = g_GetCANBMUData[index].bmuStatus.lv2CellVoltHigh;
        SaveStatusToHistoryRecord(id, BMU_LV2_CELL_VOLT_HIGH, g_BMUHistoruStatus[index].status.lv2CellVoltHigh, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv2CellVoltDiff != g_GetCANBMUData[index].bmuStatus.lv2CellVoltDiff)
    {
        g_BMUHistoruStatus[index].status.lv2CellVoltDiff = g_GetCANBMUData[index].bmuStatus.lv2CellVoltDiff;
        SaveStatusToHistoryRecord(id, BMU_LV2_CELL_VOLT_DIFF, g_BMUHistoruStatus[index].status.lv2CellVoltDiff, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv2MoudleVoltLow != g_GetCANBMUData[index].bmuStatus.lv2MoudleVoltLow)
    {
        g_BMUHistoruStatus[index].status.lv2MoudleVoltLow = g_GetCANBMUData[index].bmuStatus.lv2MoudleVoltLow;
        SaveStatusToHistoryRecord(id, BMU_LV2_MODULE_VOLT_LOW, g_BMUHistoruStatus[index].status.lv2MoudleVoltLow, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv2MoudleVoltHigh != g_GetCANBMUData[index].bmuStatus.lv2MoudleVoltHigh)
    {
        g_BMUHistoruStatus[index].status.lv2MoudleVoltHigh = g_GetCANBMUData[index].bmuStatus.lv2MoudleVoltHigh;
        SaveStatusToHistoryRecord(id, BMU_LV2_MODULE_VOLT_HIGH, g_BMUHistoruStatus[index].status.lv2MoudleVoltHigh, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv2AmbientTempLow != g_GetCANBMUData[index].bmuStatus.lv2AmbientTempLow)
    {
        g_BMUHistoruStatus[index].status.lv2AmbientTempLow = g_GetCANBMUData[index].bmuStatus.lv2AmbientTempLow;
        SaveStatusToHistoryRecord(id, BMU_LV2_AMBIENT_TEMP_LOW, g_BMUHistoruStatus[index].status.lv2AmbientTempLow, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv2AmbientTempHigh != g_GetCANBMUData[index].bmuStatus.lv2AmbientTempHigh)
    {
        g_BMUHistoruStatus[index].status.lv2AmbientTempHigh = g_GetCANBMUData[index].bmuStatus.lv2AmbientTempHigh;
        SaveStatusToHistoryRecord(id, BMU_LV2_AMBIENT_TEMP_HIGH, g_BMUHistoruStatus[index].status.lv2AmbientTempHigh, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv2ChrgTempLow != g_GetCANBMUData[index].bmuStatus.lv2ChrgTempLow)
    {
        g_BMUHistoruStatus[index].status.lv2ChrgTempLow = g_GetCANBMUData[index].bmuStatus.lv2ChrgTempLow;
        SaveStatusToHistoryRecord(id, BMU_LV2_CHRG_TEMP_LOW, g_BMUHistoruStatus[index].status.lv2ChrgTempLow, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv2ChrgTempHigh != g_GetCANBMUData[index].bmuStatus.lv2ChrgTempHigh)
    {
        g_BMUHistoruStatus[index].status.lv2ChrgTempHigh = g_GetCANBMUData[index].bmuStatus.lv2ChrgTempHigh;
        SaveStatusToHistoryRecord(id, BMU_LV2_CHRG_TEMP_HIGH, g_BMUHistoruStatus[index].status.lv2ChrgTempHigh, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv2DischrgTempLow != g_GetCANBMUData[index].bmuStatus.lv2DischrgTempLow)
    {
        g_BMUHistoruStatus[index].status.lv2DischrgTempLow = g_GetCANBMUData[index].bmuStatus.lv2DischrgTempLow;
        SaveStatusToHistoryRecord(id, BMU_LV2_DISCHRG_TEMP_LOW, g_BMUHistoruStatus[index].status.lv2DischrgTempLow, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].status.lv2DischrgTempHigh != g_GetCANBMUData[index].bmuStatus.lv2DischrgTempHigh)
    {
        g_BMUHistoruStatus[index].status.lv2DischrgTempHigh = g_GetCANBMUData[index].bmuStatus.lv2DischrgTempHigh;
        SaveStatusToHistoryRecord(id, BMU_LV2_DISCHRG_TEMP_HIGH, g_BMUHistoruStatus[index].status.lv2DischrgTempHigh, SOURCE_RECORD);
    }
}


void CANThread::SaveBMUBalStatusToHistoryBuffer(UINT id)
{
    unsigned int index = 0;
    index = id & 0x0000000f;
    int i = 0;

    if (g_BMUHistoruStatus[index].balStatus.cellBalMode != g_GetCANBMUData[index].bmuBalStatus.cellBalMode)
    {
        g_BMUHistoruStatus[index].balStatus.cellBalMode = g_GetCANBMUData[index].bmuBalStatus.cellBalMode;
        SaveStatusToHistoryRecord(id, BMU_CELL_BAL_MODE, g_BMUHistoruStatus[index].balStatus.cellBalMode, SOURCE_RECORD);
    }
    if (g_BMUHistoruStatus[index].balStatus.cellBalSt != g_GetCANBMUData[index].bmuBalStatus.cellBalSt)
    {
        g_BMUHistoruStatus[index].balStatus.cellBalSt = g_GetCANBMUData[index].bmuBalStatus.cellBalSt;
        SaveStatusToHistoryRecord(id, BMU_CELL_BAL_ST, g_BMUHistoruStatus[index].balStatus.cellBalSt, SOURCE_RECORD);
    }

    for (i=0; i<MAX_CELL_VOLT_NUMBER; i++)
    {
        if (g_BMUHistoruStatus[index].balStatus.cellInBal[i] != g_GetCANBMUData[index].bmuBalStatus.cellInBal[i])
        {
            g_BMUHistoruStatus[index].balStatus.cellInBal[i] = g_GetCANBMUData[index].bmuBalStatus.cellInBal[i];
            SaveStatusToHistoryRecord(id, QString("%1%2").arg(STRING_BMU_CELL_IN_BAL).arg(i),\
                                      g_BMUHistoruStatus[index].balStatus.cellInBal[i], SOURCE_RECORD);
        }
    }
}


void CANThread::SaveStatusToHistoryRecord(unsigned int id, QString name, float value, int type)
{
    QSqlQuery query = QSqlQuery(m_canDB);
    QString sqlLine = NULL;

    if (g_DBConnectionFlag)
    {
        sqlLine = QString("insert into %1 (Time, TestNumber, SignalID, ParameterName, Value, Type) values (UNIX_TIMESTAMP(), %2, %3, '%4', %5, %6)")
                .arg(HISTORY_RECORD).arg(g_TestNumber).arg(id).arg(name).arg(value).arg(type);
#ifdef DEBUG_MODE
        qDebug() << sqlLine;
#endif
        query.exec(sqlLine);

        if (query.lastError().isValid())
        {
#ifdef DEBUG_MODE
            qDebug() << query.lastError();
#endif
            emit ErrorInfo(QString("%1:%2").arg("CANThread::SaveStatusToHistoryRecord").arg(query.lastError().text()));
            g_DBConnectionFlag = false;
            return;
        }
    }
}


void ValueThread::SaveAllAverageValueToDB()
{
    QString timestamp = NULL;
    UINT unixtime = 0;
    GetCurrentTime(&timestamp, &unixtime);
    static QString savedTime = NULL;

    if (!g_CurrentTimeFlag)
    {
        savedTime = timestamp;
        g_CurrentTimeFlag = true;
    }

    if (savedTime.left(16) < timestamp.left(16))
    {
        savedTime = timestamp;
        //0x4210
        AverageValueToDB(&g_HistoryValue.packVoltList, unixtime);
        AverageValueToDB(&g_HistoryValue.packCurrList, unixtime);
        AverageValueToDB(&g_HistoryValue.ambientTempOutList, unixtime);
        AverageValueToDB(&g_HistoryValue.bmsSocList, unixtime);
        AverageValueToDB(&g_HistoryValue.packPwrList, unixtime);

        //0x18FF02C0
        AverageValueToDB(&g_HistoryValue.ambientTempList, unixtime);

        //0x4220
        AverageValueToDB(&g_HistoryValue.maxChgCurrList, unixtime);
        AverageValueToDB(&g_HistoryValue.maxDischgCurrList, unixtime);

        //0x4230
        AverageValueToDB(&g_HistoryValue.bmsMaxCellVoltList, unixtime);
        AverageValueToDB(&g_HistoryValue.bmsMinCellVoltList, unixtime);

        //0x4240
        AverageValueToDB(&g_HistoryValue.maxCellTempList, unixtime);
        AverageValueToDB(&g_HistoryValue.minCellTempList, unixtime);

        //0x4260
        AverageValueToDB(&g_HistoryValue.maxMoudleCVList, unixtime);
        AverageValueToDB(&g_HistoryValue.minMoudleCVList, unixtime);

        //0x4270
        AverageValueToDB(&g_HistoryValue.maxMoudleCTList, unixtime);
        AverageValueToDB(&g_HistoryValue.minMoudleCTList, unixtime);

        //0x18FF01Bx
        AverageValueToDB(&g_HistoryValue.bmuSocList, unixtime);
        AverageValueToDB(&g_HistoryValue.diffCellVoltList, unixtime);
        AverageValueToDB(&g_HistoryValue.diffCellTempList, unixtime);

        //0x18FF02Bx
        AverageValueToDB(&g_HistoryValue.moudleVoltList, unixtime);
        AverageValueToDB(&g_HistoryValue.boardTempList, unixtime);

        //0x18FF10Bx
        AverageValueToDB(&g_HistoryValue.bmuMaxCellVoltList, unixtime);
        AverageValueToDB(&g_HistoryValue.bmuMinCellVoltList, unixtime);
        AverageValueToDB(&g_HistoryValue.avgCellVoltList, unixtime);

        //0x18FF20Bx
        AverageValueToDB(&g_HistoryValue.bmuMaxCellTempList, unixtime);
        AverageValueToDB(&g_HistoryValue.bmuMinCellTempList, unixtime);
        AverageValueToDB(&g_HistoryValue.avgCellTempList, unixtime);

        //0x18FF40Bx - 0x18FF4FBx
        AverageValueToDB(&g_HistoryValue.cellVolt0, unixtime);
        AverageValueToDB(&g_HistoryValue.cellVolt1, unixtime);
        AverageValueToDB(&g_HistoryValue.cellVolt2, unixtime);
        AverageValueToDB(&g_HistoryValue.cellVolt3, unixtime);
        AverageValueToDB(&g_HistoryValue.cellVolt4, unixtime);
        AverageValueToDB(&g_HistoryValue.cellVolt5, unixtime);
        AverageValueToDB(&g_HistoryValue.cellVolt6, unixtime);
        AverageValueToDB(&g_HistoryValue.cellVolt7, unixtime);
        AverageValueToDB(&g_HistoryValue.cellVolt8, unixtime);
        AverageValueToDB(&g_HistoryValue.cellVolt9, unixtime);
        AverageValueToDB(&g_HistoryValue.cellVolt10, unixtime);
        AverageValueToDB(&g_HistoryValue.cellVolt11, unixtime);
        AverageValueToDB(&g_HistoryValue.cellVolt12, unixtime);
        AverageValueToDB(&g_HistoryValue.cellVolt13, unixtime);
        AverageValueToDB(&g_HistoryValue.cellVolt14, unixtime);
        AverageValueToDB(&g_HistoryValue.cellVolt15, unixtime);

        //0x18FF50Bx - 0x18FF5FBx
        AverageValueToDB(&g_HistoryValue.cellTemp0, unixtime);
        AverageValueToDB(&g_HistoryValue.cellTemp1, unixtime);
        AverageValueToDB(&g_HistoryValue.cellTemp2, unixtime);
        AverageValueToDB(&g_HistoryValue.cellTemp3, unixtime);
    }
}


void ValueThread::AverageValueToDB(QList<HistoryListNode> *list, UINT time)
{
    QSqlQuery query = QSqlQuery(m_historyDB);
    int listSize = 0;
    int i = 0;
    HistoryListNode node;
    float sumValue = 0;
    float maxValue = 0;
    float minValue = 0;
    float avrValue = 0;
    QString sqlLine = NULL;

    if (g_DBConnectionFlag)
    {
        if (!list->isEmpty())
        {
            minValue = list->first().value;
            maxValue = list->first().value;
            listSize = list->size();
            for (i=0; i<listSize; i++)
            {
                node = list->takeFirst();
                sumValue += node.value;

                if (maxValue < node.value)
                {
                    maxValue = node.value;
                }

                if (minValue > node.value)
                {
                    minValue = node.value;
                }
            }
            avrValue = sumValue / listSize;

            sqlLine = QString("insert into %1(Time, TestNumber, SignalID, ParameterName, `MaxValue`, `MinValue`, `Value`, Type) "
                              "values (%2, %3, %4, '%5', %6, %7, %8, %9)").arg(HISTORY_RECORD).arg(time).arg(g_TestNumber).arg(node.signalID)\
                    .arg(node.parName).arg(maxValue).arg(minValue).arg(avrValue).arg(AVERAGE_RECORD);
            query.exec(sqlLine);
            if (query.lastError().isValid())
            {
                g_DBConnectionFlag = false;
#ifdef DEBUG_MODE
                qDebug() << query.lastError();
#endif
                emit ErrorInfo(QString("%1:%2").arg("ValueThread::AverageValueToDB").arg(query.lastError().text()));
                return;
            }
        }
    }
}


void ValueThread::GetCurrentTime(QString *timestamp, UINT *unixtime)
{
    QSqlQuery query = QSqlQuery(m_historyDB);

    if (g_DBConnectionFlag)
    {
        QString sqlLine  = QString("select current_timestamp(), UNIX_TIMESTAMP()");
        query.exec(sqlLine);

        if (query.lastError().isValid())
        {
            g_DBConnectionFlag = false;
#ifdef DEBUG_MODE
            qDebug() << query.lastError();
#endif
            emit ErrorInfo(QString("%1:%2").arg("ValueThread::GetCurrentTime").arg(query.lastError().text()));
            return;
        }

        while(query.next())
        {
            *timestamp = query.value(0).toString();
            *unixtime = query.value(1).toUInt();
        }
    }
}

