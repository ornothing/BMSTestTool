#include "WorkThread.h"
#include "databasedefine.h"

extern QList<ChartData> g_selectedSignalData;
extern BMSUIData g_GetCANBMSData;
extern BMUUIData g_GetCANBMUData[MAX_BMU_NUMBER];


void BMSInfoToChart(VCI_CAN_OBJ srcData)
{
    switch (srcData.ID)
    {
    /** BMS cmd **/
    case 0x4200:
        GetSelectedData(BMS_POLL_GLOBAL_INFO, -1, g_GetCANBMSData.bmsPoll.pollGlobalInfo);
        break;

    /** 电池模组参数 **/
    case 0x4210:
        GetSelectedData(BMS_PACK_VOLT, -1, g_GetCANBMSData.bmsCellModuleP1.packVolt);
        GetSelectedData(BMS_PACK_CURR, -1, g_GetCANBMSData.bmsCellModuleP1.packCurr);
        GetSelectedData(BMS_AMBIENT_TEMP_OUT, -1, g_GetCANBMSData.bmsCellModuleP1.ambientTempOut);
        GetSelectedData(BMS_SOC, -1, g_GetCANBMSData.bmsCellModuleP1.SOC);
        GetSelectedData(BMS_PACK_PWR, -1, g_GetCANBMSData.bmsCellModuleP1.packPwr);
        break;

    case 0x18FF02C0:
        GetSelectedData(BMS_AMBIENT_TEMP_IN, -1, g_GetCANBMSData.bmsCellModuleP2.ambientTemp);
        break;

    case 0x4220:
        GetSelectedData(BMS_MAX_CHG_CURR, -1, g_GetCANBMSData.bmsCellModuleP3.maxChgCurr);
        GetSelectedData(BMS_MAX_DISCHG_CURR, -1, g_GetCANBMSData.bmsCellModuleP3.maxDischgCurr);
        break;

    /** 电池基本参数 **/
    case 0x4230:
        GetSelectedData(BMS_MAX_CELL_VLOT, -1, g_GetCANBMSData.bmsCellBaiscP1.maxCellVolt);
        GetSelectedData(BMS_MIN_CELL_VOLT, -1, g_GetCANBMSData.bmsCellBaiscP1.minCellVolt);
        GetSelectedData(BMS_MAX_CV_NO, -1, g_GetCANBMSData.bmsCellBaiscP1.maxCVNO);
        GetSelectedData(BMS_MIN_CV_NO, -1, g_GetCANBMSData.bmsCellBaiscP1.minCVNO);
        break;

    case 0x4240:
        GetSelectedData(BMS_MAX_CELL_TEMP, -1, g_GetCANBMSData.bmsCellBaiscP2.maxCellTemp);
        GetSelectedData(BMS_MIN_CELL_TEMP, -1, g_GetCANBMSData.bmsCellBaiscP2.minCellTemp);
        GetSelectedData(BMS_MAX_CT_NO, -1, g_GetCANBMSData.bmsCellBaiscP2.maxCTNO);
        GetSelectedData(BMS_MIN_CT_NO, -1, g_GetCANBMSData.bmsCellBaiscP2.minCTNO);
        break;

    case 0x4260:
        GetSelectedData(BMS_MAX_MODULE_CV, -1, g_GetCANBMSData.bmsCellBaiscP3.maxMoudleCV);
        GetSelectedData(BMS_MIN_MODULE_CV, -1, g_GetCANBMSData.bmsCellBaiscP3.minMoudleCV);
        GetSelectedData(BMS_MAX_MCV_NO, -1, g_GetCANBMSData.bmsCellBaiscP3.maxMCVNO);
        GetSelectedData(BMS_MIN_MCV_NO, -1, g_GetCANBMSData.bmsCellBaiscP3.minMCVNO);
        break;

    case 0x4270:
        GetSelectedData(BMS_MAX_MODULE_CT, -1, g_GetCANBMSData.bmsCellBaiscP4.maxMoudleCT);
        GetSelectedData(BMS_MIN_MOUDLE_CT, -1, g_GetCANBMSData.bmsCellBaiscP4.minMoudleCT);
        GetSelectedData(BMS_MAX_MCT_NO, -1, g_GetCANBMSData.bmsCellBaiscP4.maxMCTNO);
        GetSelectedData(BMS_MIN_MCT_NO, -1, g_GetCANBMSData.bmsCellBaiscP4.minMCTNO);
        break;

    /** 指令 **/
    case 0x4280:
        GetSelectedData(BMS_CHRG_FORBIDEN_MARK, -1, g_GetCANBMSData.bmsCommand1.chrgForbidenMark);
        GetSelectedData(BMS_DISCHRG_FORBIDEN_MARK, -1, g_GetCANBMSData.bmsCommand1.dischrgForbidenMark);
        break;

    case 0x8200:
        GetSelectedData(BMS_SLEEP_CTRL, -1, g_GetCANBMSData.bmsCommand2.sleepCtrl);
        break;

    case 0x8210:
        GetSelectedData(BMS_CHRG_EN, -1, g_GetCANBMSData.bmsCommand3.chrgEN);
        GetSelectedData(BMS_DISCHRG_EN, -1, g_GetCANBMSData.bmsCommand3.dischrgEN);
        break;

    case 0x8220:
        GetSelectedData(BMS_RELAY_FORCE_BREAK, -1, g_GetCANBMSData.bmsCommand4.relayForceBreak);
        break;

    default:
        break;
    }
}


void BMSErrorStatusToChart()
{
    GetSelectedData(BMS_BASIC_STATUS, -1, g_GetCANBMSData.bmsCellError.basicStatus);
    GetSelectedData(BMS_ERR_VOLT_SENSOR, -1, g_GetCANBMSData.bmsCellError.errVoltSensor);
    GetSelectedData(BMS_ERR_TEMP_SENSOR, -1, g_GetCANBMSData.bmsCellError.errTempSensor);
    GetSelectedData(BMS_ERR_INN_COM, -1, g_GetCANBMSData.bmsCellError.errInnCom);
    GetSelectedData(BMS_ERR_CHRG_VOLT_HIGH, -1, g_GetCANBMSData.bmsCellError.errChrgVoltHigh);
    GetSelectedData(BMS_ERR_WIRE_INVERSED, -1, g_GetCANBMSData.bmsCellError.errWireInversed);
    GetSelectedData(BMS_ERR_RELAY_STICKY, -1, g_GetCANBMSData.bmsCellError.errRelaySticky);

    GetSelectedData(BMS_ALM_CELL_VOLT_LOW, -1, g_GetCANBMSData.bmsCellError.almCellVoltLow);
    GetSelectedData(BMS_ALM_CELL_VOLT_HIGH, -1, g_GetCANBMSData.bmsCellError.almCellVoltHigh);
    GetSelectedData(BMS_ALM_PACK_VOLT_LOW, -1, g_GetCANBMSData.bmsCellError.almPackVoltLow);
    GetSelectedData(BMS_ALM_PACK_VOLT_HIGH, -1, g_GetCANBMSData.bmsCellError.almPackVoltHigh);
    GetSelectedData(BMS_ALM_CHRG_TEMP_LOW, -1, g_GetCANBMSData.bmsCellError.almChrgTempLow);
    GetSelectedData(BMS_ALM_CHRG_TEMP_HIGH, -1, g_GetCANBMSData.bmsCellError.almChrgTempHigh);
    GetSelectedData(BMS_ALM_DISCHRG_TEMP_LOW, -1, g_GetCANBMSData.bmsCellError.almDischrgTempLow);
    GetSelectedData(BMS_ALM_DISCHRG_TEMP_HIGH, -1, g_GetCANBMSData.bmsCellError.almDischrgTempHigh);

    GetSelectedData(BMS_ALM_CHRG_CURR_HIGH, -1, g_GetCANBMSData.bmsCellError.almChrgCurrHigh);
    GetSelectedData(BMS_ALM_DISCHRG_CURR_HIGH, -1, g_GetCANBMSData.bmsCellError.almDischrgCurrHigh);
    GetSelectedData(BMS_ALM_MODULE_VOLT_LOW, -1, g_GetCANBMSData.bmsCellError.almMoudleVoltLow);
    GetSelectedData(BMS_ALM_MODULE_VOLT_HIGH, -1, g_GetCANBMSData.bmsCellError.almMoudleVoltHigh);

    GetSelectedData(BMS_P_CELL_VOLT_LOW, -1, g_GetCANBMSData.bmsCellError.pCellVoltLow);
    GetSelectedData(BMS_P_CELL_VOLT_HIGH, -1, g_GetCANBMSData.bmsCellError.pCellVoltHigh);
    GetSelectedData(BMS_P_PACK_VOLT_LOW, -1, g_GetCANBMSData.bmsCellError.pPackVoltLow);
    GetSelectedData(BMS_P_PACK_VOLT_HIGH, -1, g_GetCANBMSData.bmsCellError.pPackVoltHigh);
    GetSelectedData(BMS_P_CHRG_TEMP_LOW, -1, g_GetCANBMSData.bmsCellError.pChrgTempLow);
    GetSelectedData(BMS_P_CHRG_TEMP_HIGH, -1, g_GetCANBMSData.bmsCellError.pChrgTempHigh);
    GetSelectedData(BMS_P_DISCHRG_TEMP_LOW, -1, g_GetCANBMSData.bmsCellError.pDischrgTempLow);
    GetSelectedData(BMS_P_DISCHRG_TEMP_HIGH, -1, g_GetCANBMSData.bmsCellError.pDischrgTempHigh);

    GetSelectedData(BMS_P_CHRG_CURR_HIGH, -1, g_GetCANBMSData.bmsCellError.pChrgCurrHigh);
    GetSelectedData(BMS_P_DISCHRG_CURR_HIGH, -1, g_GetCANBMSData.bmsCellError.pDischrgCurrHigh);
    GetSelectedData(BMS_P_MODULE_VOLT_LOW, -1, g_GetCANBMSData.bmsCellError.pMoudleVoltLow);
    GetSelectedData(BMS_P_MODULE_VOLT_HIGH, -1, g_GetCANBMSData.bmsCellError.pMoudleVoltHigh);
}


void BMSCellStatusToChart()
{
    GetSelectedData(BMS_FORCE_CHRG_ST, -1, g_GetCANBMSData.bmsCellStatus.forceChrgSt);
    GetSelectedData(BMS_POSI_RLY_ST, -1, g_GetCANBMSData.bmsCellStatus.posiRlySt);
    GetSelectedData(BMS_NEG_RLY_ST, -1, g_GetCANBMSData.bmsCellStatus.negRlySt);
    GetSelectedData(BMS_RLY_STICKY, -1, g_GetCANBMSData.bmsCellStatus.rlySticky);
    GetSelectedData(BMS_ALM_ST, -1, g_GetCANBMSData.bmsCellStatus.almSt);
}


void BMSFaultToChart()
{
    GetSelectedData(BMS_FATAL_BMU_SENSOR, -1, g_GetCANBMSData.bmsCellFault.fatalBMSSensor);
    GetSelectedData(BMS_FATAL_BMU_AFE, -1, g_GetCANBMSData.bmsCellFault.fatalBMSAFE);
    GetSelectedData(BMS_FATAL_BMU_CV, -1, g_GetCANBMSData.bmsCellFault.fatalBMSCV);
    GetSelectedData(BMS_FATAL_BMU_VT, -1, g_GetCANBMSData.bmsCellFault.fatalBMSCT);
    GetSelectedData(BMS_FATAL_HVCU_COM, -1, g_GetCANBMSData.bmsCellFault.fatalHvcuCom);
    GetSelectedData(BMS_FATAL_HVCU_SENSOR, -1, g_GetCANBMSData.bmsCellFault.fatalHvcuSensor);
}


void BMUInfoToChart(VCI_CAN_OBJ srcData)
{
    int index = 0;
    index = srcData.ID & 0x0000000f;
    UINT id = 0;
    id = srcData.ID >> 4;

    /** BMU基本参数 **/
    switch (id)
    {
    case 0x18FF01B:
        GetSelectedData(BMU_SOC, index, g_GetCANBMUData[index].bmuBasicP1.SOC);
        GetSelectedData(BMU_DIFF_CELL_VOLT, index, g_GetCANBMUData[index].bmuBasicP1.diffCellVolt);
        GetSelectedData(BMU_DIFF_CELL_TEMP, index, g_GetCANBMUData[index].bmuBasicP1.diffCellTemp);
        break;

    case 0x18FF02B:
        GetSelectedData(BMU_MODULE_VOLT, index, g_GetCANBMUData[index].bmuBasicP2.moudleVolt);
        GetSelectedData(BMU_BOARD_TEMP, index, g_GetCANBMUData[index].bmuBasicP2.boardTemp);
        break;

    case 0x18FF10B:
        GetSelectedData(BMU_MAX_CELL_VOLT, index, g_GetCANBMUData[index].bmuBasicP3.maxCellVolt);
        GetSelectedData(BMU_MIN_CELL_VOLT, index, g_GetCANBMUData[index].bmuBasicP3.minCellVolt);
        GetSelectedData(BMU_AVG_CELL_VOLT, index, g_GetCANBMUData[index].bmuBasicP3.avgCellVolt);
        GetSelectedData(BMU_MAX_CV_NO, index, g_GetCANBMUData[index].bmuBasicP3.maxCVNO);
        GetSelectedData(BMU_MIN_CV_NO, index, g_GetCANBMUData[index].bmuBasicP3.minCVNO);
        break;

    case 0x18FF20B:
        GetSelectedData(BMU_MAX_CELL_TEMP, index, g_GetCANBMUData[index].bmuBasicP4.maxCellTemp);
        GetSelectedData(BMU_MIN_CELL_TEMP, index, g_GetCANBMUData[index].bmuBasicP4.minCellTemp);
        GetSelectedData(BMU_AVG_CELL_TEMP, index, g_GetCANBMUData[index].bmuBasicP4.avgCellTemp);
        GetSelectedData(BMU_MAX_CT_NO, index, g_GetCANBMUData[index].bmuBasicP4.maxCTNO);
        GetSelectedData(BMU_MIN_CT_NO, index, g_GetCANBMUData[index].bmuBasicP4.minCTNO);
        break;

    /** 模组配置 **/
    case 0x18FF60B:
        GetSelectedData(BMU_CELL_AH, index, g_GetCANBMUData[index].bmuModuleConfig.cellAH);
        GetSelectedData(BMU_CELL_RATE_VOLT, index, g_GetCANBMUData[index].bmuModuleConfig.cellRateVolt);
        GetSelectedData(BMU_CELL_NUM, index, g_GetCANBMUData[index].bmuModuleConfig.cellNum);
        GetSelectedData(BMU_TEMP_NUM, index, g_GetCANBMUData[index].bmuModuleConfig.tempNum);
        break;

    /** 单芯电压 **/
    case 0x18FF40B:
        GetSelectedData(BMU_CELL_VOLT_0, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[0]);
        GetSelectedData(BMU_CELL_VOLT_1, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[1]);
        GetSelectedData(BMU_CELL_VOLT_2, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[2]);
        GetSelectedData(BMU_CELL_VOLT_3, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[3]);
        break;

    case 0x18FF41B:
        GetSelectedData(BMU_CELL_VOLT_4, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[4]);
        GetSelectedData(BMU_CELL_VOLT_5, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[5]);
        GetSelectedData(BMU_CELL_VOLT_6, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[6]);
        GetSelectedData(BMU_CELL_VOLT_7, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[7]);
        break;

    case 0x18FF42B:
        GetSelectedData(BMU_CELL_VOLT_8, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[8]);
        GetSelectedData(BMU_CELL_VOLT_9, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[9]);
        GetSelectedData(BMU_CELL_VOLT_10, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[10]);
        GetSelectedData(BMU_CELL_VOLT_11, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[11]);
        break;

    case 0x18FF43B:
        GetSelectedData(BMU_CELL_VOLT_12, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[12]);
        GetSelectedData(BMU_CELL_VOLT_13, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[13]);
        GetSelectedData(BMU_CELL_VOLT_14, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[14]);
        GetSelectedData(BMU_CELL_VOLT_15, index, g_GetCANBMUData[index].bmuCellVolt.cellVolt[15]);
        break;

     /** 单体温度 **/
    case 0x18FF50B:
        GetSelectedData(BMU_CELL_TEMP_0, index, g_GetCANBMUData[index].bmuCellTemp.cellTemp[0]);
        GetSelectedData(BMU_CELL_TEMP_1, index, g_GetCANBMUData[index].bmuCellTemp.cellTemp[1]);
        GetSelectedData(BMU_CELL_TEMP_2, index, g_GetCANBMUData[index].bmuCellTemp.cellTemp[2]);
        GetSelectedData(BMU_CELL_TEMP_3, index, g_GetCANBMUData[index].bmuCellTemp.cellTemp[3]);
        break;

    default:
        break;
    }
}


void BMUStatusToChart(VCI_CAN_OBJ srcData)
{
    int index = 0;
    index = srcData.ID & 0x0000000f;

    GetSelectedData(BMU_AFE_SAMPLE, index, g_GetCANBMUData[index].bmuStatus.AFESample);
    GetSelectedData(BMU_AFE_FAULT, index, g_GetCANBMUData[index].bmuStatus.AFEFault);
    GetSelectedData(BMU_OWD_ST, index, g_GetCANBMUData[index].bmuStatus.OWDSt);

    GetSelectedData(BMU_LV1_CELL_VOLT_LOW, index, g_GetCANBMUData[index].bmuStatus.lv1CellVoltLow);
    GetSelectedData(BMU_LV1_CELL_VOLT_HIGH, index, g_GetCANBMUData[index].bmuStatus.lv1CellVoltHigh);
    GetSelectedData(BMU_LV1_CELL_VOLT_DIFF, index, g_GetCANBMUData[index].bmuStatus.lv1CellVoltDiff);
    GetSelectedData(BMU_LV1_MODULE_VOLT_LOW, index, g_GetCANBMUData[index].bmuStatus.lv1MoudleVoltLow);
    GetSelectedData(BMU_LV1_MODULE_VOLT_HIGH, index, g_GetCANBMUData[index].bmuStatus.lv1MoudleVoltHigh);
    GetSelectedData(BMU_LV1_AMBIENT_TEMP_LOW, index, g_GetCANBMUData[index].bmuStatus.lv1AmbientTempLow);
    GetSelectedData(BMU_LV1_AMBIENT_TEMP_HIGH, index, g_GetCANBMUData[index].bmuStatus.lv1AmbientTempHigh);

    GetSelectedData(BMU_LV1_CHRG_TEMP_LOW, index, g_GetCANBMUData[index].bmuStatus.lv1ChrgTempLow);
    GetSelectedData(BMU_LV1_CHRG_TEMP_HIGH, index, g_GetCANBMUData[index].bmuStatus.lv1ChrgTempHigh);
    GetSelectedData(BMU_LV1_DISCHRG_TEMP_LOW, index, g_GetCANBMUData[index].bmuStatus.lv1DischrgTempLow);
    GetSelectedData(BMU_LV1_DISCHRG_TEMP_HIGH, index, g_GetCANBMUData[index].bmuStatus.lv1DischrgTempHigh);

    GetSelectedData(BMU_LV2_CELL_VOLT_LOW, index, g_GetCANBMUData[index].bmuStatus.lv2CellVoltLow);
    GetSelectedData(BMU_LV2_CELL_VOLT_HIGH, index, g_GetCANBMUData[index].bmuStatus.lv2CellVoltHigh);
    GetSelectedData(BMU_LV2_CELL_VOLT_DIFF, index, g_GetCANBMUData[index].bmuStatus.lv2CellVoltDiff);
    GetSelectedData(BMU_LV2_MODULE_VOLT_LOW, index, g_GetCANBMUData[index].bmuStatus.lv2MoudleVoltLow);
    GetSelectedData(BMU_LV2_MODULE_VOLT_HIGH, index, g_GetCANBMUData[index].bmuStatus.lv2MoudleVoltHigh);
    GetSelectedData(BMU_LV2_AMBIENT_TEMP_LOW, index, g_GetCANBMUData[index].bmuStatus.lv2AmbientTempLow);
    GetSelectedData(BMU_LV2_AMBIENT_TEMP_HIGH, index, g_GetCANBMUData[index].bmuStatus.lv2AmbientTempHigh);

    GetSelectedData(BMU_LV2_CHRG_TEMP_LOW, index, g_GetCANBMUData[index].bmuStatus.lv2ChrgTempLow);
    GetSelectedData(BMU_LV2_CHRG_TEMP_HIGH, index, g_GetCANBMUData[index].bmuStatus.lv2ChrgTempHigh);
    GetSelectedData(BMU_LV2_DISCHRG_TEMP_LOW, index, g_GetCANBMUData[index].bmuStatus.lv2DischrgTempLow);
    GetSelectedData(BMU_LV2_DISCHRG_TEMP_HIGH, index, g_GetCANBMUData[index].bmuStatus.lv2DischrgTempHigh);
}


void BMUBalStatusToChart(VCI_CAN_OBJ srcData)
{
    int index = 0;
    index = srcData.ID & 0x0000000f;

    GetSelectedData(BMU_CELL_BAL_MODE, index, g_GetCANBMUData[index].bmuBalStatus.cellBalMode);
    GetSelectedData(BMU_CELL_BAL_ST, index, g_GetCANBMUData[index].bmuBalStatus.cellBalSt);
    GetSelectedData(BMU_CELL_IN_BAL_0, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[0]);
    GetSelectedData(BMU_CELL_IN_BAL_1, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[1]);
    GetSelectedData(BMU_CELL_IN_BAL_2, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[2]);
    GetSelectedData(BMU_CELL_IN_BAL_3, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[3]);
    GetSelectedData(BMU_CELL_IN_BAL_4, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[4]);
    GetSelectedData(BMU_CELL_IN_BAL_5, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[5]);
    GetSelectedData(BMU_CELL_IN_BAL_6, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[6]);
    GetSelectedData(BMU_CELL_IN_BAL_7, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[7]);

    GetSelectedData(BMU_CELL_IN_BAL_8, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[8]);
    GetSelectedData(BMU_CELL_IN_BAL_9, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[9]);
    GetSelectedData(BMU_CELL_IN_BAL_10, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[10]);
    GetSelectedData(BMU_CELL_IN_BAL_11, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[11]);
    GetSelectedData(BMU_CELL_IN_BAL_12, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[12]);
    GetSelectedData(BMU_CELL_IN_BAL_13, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[13]);
    GetSelectedData(BMU_CELL_IN_BAL_14, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[14]);
    GetSelectedData(BMU_CELL_IN_BAL_15, index, g_GetCANBMUData[index].bmuBalStatus.cellInBal[15]);
}


void GetSelectedData(QString parameter, int bmuNumber, float data)
{
    int i = 0;

    for (i=0; i<g_selectedSignalData.size(); i++)
    {
        if ((g_selectedSignalData.at(i).parameterName == parameter) &&\
                (g_selectedSignalData.at(i).BMUNumber == bmuNumber) &&\
                (g_selectedSignalData.at(i).selectedFlag == true))
        {
            g_selectedSignalData[i].data.append(data);
            break;
        }
    }
}
