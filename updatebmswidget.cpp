#include "BMSInfoWidget.h"

BMSSignal g_BMSSignalData;
extern QList<UINT> g_BMSRecvedList;
extern BMSUIData g_GetCANBMSData;

void BMSInfoWidget::UpdateWidget()
{
    UINT id;
    while(!g_BMSRecvedList.isEmpty())
    {
        id = g_BMSRecvedList.takeFirst();
        SetBMSWidget(id);
    }
}

void BMSInfoWidget::SetBMSWidget(UINT id)
{
    switch(id)
    {
    /** 电池模组参数 **/
    case 0x4200:
    case 0x4210:
    case 0x18FF02C0:
    case 0x4220:
        SetBMSCellModelPara(id);
        break;

    /** 电池基本参数 **/
    case 0x4230:
    case 0x4240:
    case 0x4260:
    case 0x4270:
        SetBMSCellBasicPara(id);
        break;

    /** 电池配置信息 **/
    case 0x7320:
        SetBMSCellConfig(id);
        break;

    /** 指令 **/
    case 0x4280:
    case 0x8200:
    case 0x8210:
    case 0x8220:
        SetBMSCommand(id);
        break;

    /** 电池状态信息与电池故障信息 **/
    case 0x4250:
        SetBMSErrorStatus(id);
        break;

    case 0x18FF02A0:
        SetBMSCellStatus(id);
        break;

    case 0x18FF04A0:
        SetBMSFaultStatus(id);
        break;

    default:
        break;
    }
}


void BMSInfoWidget::SetBasicStatus()
{
    switch(g_GetCANBMSData.bmsCellError.basicStatus)
    {
    case 0:
        m_basicStatus->setText("睡眠");
        break;
    case 1:
        m_basicStatus->setText("充电");
        break;
    case 2:
        m_basicStatus->setText("放电");
        break;
    case 3:
        m_basicStatus->setText("待机");
        break;
    case 4:
        m_basicStatus->setText("NA");
        break;
    default:
        m_basicStatus->setText(QString("%1(错误)").arg(g_GetCANBMSData.bmsCellError.basicStatus));
        break;
    }
}


void BMSInfoWidget::SetBMSErrorStatus(UINT id)
{
    if (id == 0x4250)
    {
        m_basicStatus->setEnabled(true);
        m_cyclePeriod->setEnabled(true);
        m_basicStatus->setStyleSheet("background-color:white");
        m_cyclePeriod->setStyleSheet("background-color:white");

        SetBasicStatus();
        m_cyclePeriod->setText(tr("%1").arg(g_GetCANBMSData.bmsCellError.cyclePeriod));

        m_errVoltSensor->setEnabled(true);
        m_errTempSensor->setEnabled(true);
        m_errInnCom->setEnabled(true);
        m_errChrgVoltHigh->setEnabled(true);
        m_errWireInversed->setEnabled(true);
        m_errRelaySticky->setEnabled(true);

        m_almCellVoltLow->setEnabled(true);
        m_almCellVoltHigh->setEnabled(true);
        m_almPackVoltLow->setEnabled(true);
        m_almPackVoltHigh->setEnabled(true);
        m_almChrgTempLow->setEnabled(true);
        m_almChrgTempHigh->setEnabled(true);
        m_almDischrgTempLow->setEnabled(true);
        m_almDischrgTempHigh->setEnabled(true);
        m_almChrgCurrHigh->setEnabled(true);
        m_almDischrgCurrHigh->setEnabled(true);
        m_almMoudleVoltLow->setEnabled(true);
        m_almMoudleVoltHigh->setEnabled(true);

        m_pCellVoltLow->setEnabled(true);
        m_pCellVoltHigh->setEnabled(true);
        m_pPackVoltLow->setEnabled(true);
        m_pPackVoltHigh->setEnabled(true);
        m_pChrgTempLow->setEnabled(true);
        m_pChrgTempHigh->setEnabled(true);
        m_pDischrgTempLow->setEnabled(true);
        m_pDischrgTempHigh->setEnabled(true);
        m_pChrgCurrHigh->setEnabled(true);
        m_pDischrgCurrHigh->setEnabled(true);
        m_pMoudleVoltLow->setEnabled(true);
        m_pMoudleVoltHigh->setEnabled(true);


        /** 故障信息 **/
        if (g_GetCANBMSData.bmsCellError.errVoltSensor)
            m_errVoltSensor->setStyleSheet("background-color:red");
        else
            m_errVoltSensor->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.errTempSensor)
            m_errTempSensor->setStyleSheet("background-color:red");
        else
            m_errTempSensor->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.errInnCom)
            m_errInnCom->setStyleSheet("background-color:red");
        else
            m_errInnCom->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.errChrgVoltHigh)
            m_errChrgVoltHigh->setStyleSheet("background-color:red");
        else
            m_errChrgVoltHigh->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.errWireInversed)
            m_errWireInversed->setStyleSheet("background-color:red");
        else
            m_errWireInversed->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.errRelaySticky)
            m_errRelaySticky->setStyleSheet("background-color:red");
        else
            m_errRelaySticky->setStyleSheet("background-color:#32CD32");

        /** 告警信息 **/
        if (g_GetCANBMSData.bmsCellError.almCellVoltLow)
            m_almCellVoltLow->setStyleSheet("background-color:red");
        else
            m_almCellVoltLow->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.almCellVoltHigh)
            m_almCellVoltHigh->setStyleSheet("background-color:red");
        else
            m_almCellVoltHigh->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.almPackVoltLow)
            m_almPackVoltLow->setStyleSheet("background-color:red");
        else
            m_almPackVoltLow->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.almPackVoltHigh)
            m_almPackVoltHigh->setStyleSheet("background-color:red");
        else
            m_almPackVoltHigh->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.almChrgTempLow)
            m_almChrgTempLow->setStyleSheet("background-color:red");
        else
            m_almChrgTempLow->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.almChrgTempHigh)
            m_almChrgTempHigh->setStyleSheet("background-color:red");
        else
            m_almChrgTempHigh->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.almDischrgTempLow)
            m_almDischrgTempLow->setStyleSheet("background-color:red");
        else
            m_almDischrgTempLow->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.almDischrgTempHigh)
            m_almDischrgTempHigh->setStyleSheet("background-color:red");
        else
            m_almDischrgTempHigh->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.almChrgCurrHigh)
            m_almChrgCurrHigh->setStyleSheet("background-color:red");
        else
            m_almChrgCurrHigh->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.almDischrgCurrHigh)
            m_almDischrgCurrHigh->setStyleSheet("background-color:red");
        else
            m_almDischrgCurrHigh->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.almMoudleVoltLow)
            m_almMoudleVoltLow->setStyleSheet("background-color:red");
        else
            m_almMoudleVoltLow->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.almMoudleVoltHigh)
            m_almMoudleVoltHigh->setStyleSheet("background-color:red");
        else
            m_almMoudleVoltHigh->setStyleSheet("background-color:#32CD32");

        /** 保护信息 **/
        if (g_GetCANBMSData.bmsCellError.pCellVoltLow)
            m_pCellVoltLow->setStyleSheet("background-color:red");
        else
            m_pCellVoltLow->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.pCellVoltHigh)
            m_pCellVoltHigh->setStyleSheet("background-color:red");
        else
            m_pCellVoltHigh->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.pPackVoltLow)
            m_pPackVoltLow->setStyleSheet("background-color:red");
        else
            m_pPackVoltLow->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.pPackVoltHigh)
            m_pPackVoltHigh->setStyleSheet("background-color:red");
        else
            m_pPackVoltHigh->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.pChrgTempLow)
            m_pChrgTempLow->setStyleSheet("background-color:red");
        else
            m_pChrgTempLow->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.pChrgTempHigh)
            m_pChrgTempHigh->setStyleSheet("background-color:red");
        else
            m_pChrgTempHigh->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.pDischrgTempLow)
            m_pDischrgTempLow->setStyleSheet("background-color:red");
        else
            m_pDischrgTempLow->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.pDischrgTempHigh)
            m_pDischrgTempHigh->setStyleSheet("background-color:red");
        else
            m_pDischrgTempHigh->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.pChrgCurrHigh)
            m_pChrgCurrHigh->setStyleSheet("background-color:red");
        else
            m_pChrgCurrHigh->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.pDischrgCurrHigh)
            m_pDischrgCurrHigh->setStyleSheet("background-color:red");
        else
            m_pDischrgCurrHigh->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.pMoudleVoltLow)
            m_pMoudleVoltLow->setStyleSheet("background-color:red");
        else
            m_pMoudleVoltLow->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellError.pMoudleVoltHigh)
            m_pMoudleVoltHigh->setStyleSheet("background-color:red");
        else
            m_pMoudleVoltHigh->setStyleSheet("background-color:#32CD32");
    }
    g_BMSSignalData.sig0x4250 = RECV_SIGNAL_SUCCESSFUL;
}


void BMSInfoWidget::SetForceChrgSt()
{
    switch(g_GetCANBMSData.bmsCellStatus.forceChrgSt)
    {
    case 1:
        m_forceChrgSt->setText("强充");
        break;
    case 2:
        m_forceChrgSt->setText("强放");
        break;
    case 3:
        m_forceChrgSt->setText("待机");
        break;
    default:
        m_forceChrgSt->setText(QString("%1(错误)").arg(g_GetCANBMSData.bmsCellStatus.forceChrgSt));
        break;
    }
}


void BMSInfoWidget::SetPosiRlySt()
{
    switch(g_GetCANBMSData.bmsCellStatus.posiRlySt)
    {
    case 0:
        m_posiRlySt->setText("断开");
        break;
    case 1:
        m_posiRlySt->setText("闭合");
        break;
    default:
        m_posiRlySt->setText(QString("%1(错误)").arg(g_GetCANBMSData.bmsCellStatus.posiRlySt));
        break;
    }
}


void BMSInfoWidget::SetNegRlySt()
{
    switch(g_GetCANBMSData.bmsCellStatus.negRlySt)
    {
    case 0:
        m_negRlySt->setText("断开");
        break;
    case 1:
        m_negRlySt->setText("闭合");
        break;
    default:
        m_negRlySt->setText(QString("%1(错误)").arg(g_GetCANBMSData.bmsCellStatus.negRlySt));
        break;
    }
}


void BMSInfoWidget::SetRlySticky()
{
    switch(g_GetCANBMSData.bmsCellStatus.rlySticky)
    {
    case 0:
        m_rlySticky->setText("断开");
        break;
    case 1:
        m_rlySticky->setText("闭合");
        break;
    case 2:
        m_rlySticky->setText("粘滞，无法闭合");
        break;
    case 3:
        m_rlySticky->setText("粘滞，无法断开");
        break;
    case 4:
        m_rlySticky->setText("电池总压错误");
        break;
    case 5:
        m_rlySticky->setText("NA");
        break;
    default:
        m_rlySticky->setText(QString("%1(错误)").arg(g_GetCANBMSData.bmsCellStatus.rlySticky));
        break;
    }
}


void BMSInfoWidget::SetAlmSt()
{
    switch(g_GetCANBMSData.bmsCellStatus.almSt)
    {
    case 0:
        m_almSt->setText("正常");
        break;
    case 1:
        m_almSt->setText("警告");
        break;
    case 2:
        m_almSt->setText("错误");
        break;
    default:
        m_almSt->setText(QString("%1(错误)").arg(g_GetCANBMSData.bmsCellStatus.almSt));
        break;
    }
}

void BMSInfoWidget::SetMoudleCfm()
{
    switch(g_GetCANBMSData.bmsCellStatus.moudleCfm)
    {
    case 0:
        m_moudleCfm->setText("模组检查中");
        break;
    case 1:
        m_moudleCfm->setText("模组数确认");
        break;
    default:
        m_moudleCfm->setText(QString("%1(错误)").arg(g_GetCANBMSData.bmsCellStatus.moudleCfm));
        break;
    }
}


void BMSInfoWidget::SetBMSCellStatus(UINT id)
{
    if (id == 0x18FF02A0)
    {
        m_forceChrgSt->setEnabled(true);
        m_posiRlySt->setEnabled(true);
        m_negRlySt->setEnabled(true);
        m_rlySticky->setEnabled(true);
        m_almSt->setEnabled(true);
        m_moudleCfm->setEnabled(true);
        m_moudleNum->setEnabled(true);
        m_forceChrgSt->setStyleSheet("background-color:white");
        m_posiRlySt->setStyleSheet("background-color:white");
        m_negRlySt->setStyleSheet("background-color:white");
        m_rlySticky->setStyleSheet("background-color:white");
        m_almSt->setStyleSheet("background-color:white");
        m_moudleCfm->setStyleSheet("background-color:white");
        m_moudleNum->setStyleSheet("background-color:white");

        SetForceChrgSt();
        SetPosiRlySt();
        SetNegRlySt();
        SetRlySticky();
        SetAlmSt();
        SetMoudleCfm();
        m_moudleNum->setText(tr("%1").arg(g_GetCANBMSData.bmsCellStatus.moudleNum));
    }
    g_BMSSignalData.sig0x18FF02A0 = RECV_SIGNAL_SUCCESSFUL;
}


void BMSInfoWidget::SetFatalPOSC()
{
    switch(g_GetCANBMSData.bmsCellFault.fatalPOSC)
    {
    case 0:
        m_fatalPOSC->setText("通过");
        break;
    case 1:
        m_fatalPOSC->setText("失败");
        break;
    default:
        m_fatalPOSC->setText(QString("%1(错误)").arg(g_GetCANBMSData.bmsCellFault.fatalPOSC));
        break;
    }
}


void BMSInfoWidget::SetBMSFaultStatus(UINT id)
{
    if (id == 0x18FF04A0)
    {
        m_fatalPOSC->setEnabled(true);
        m_fatalBMUSensor->setEnabled(true);
        m_fatalBMUAFE->setEnabled(true);
        m_fatalBMUCV->setEnabled(true);
        m_fatalBMUCT->setEnabled(true);
        m_fatalHVCUCom->setEnabled(true);
        m_fatalHVCUSensor->setEnabled(true);
        m_fatalPOSC->setStyleSheet("background-color:white");

        SetFatalPOSC();

        if (g_GetCANBMSData.bmsCellFault.fatalBMSSensor)
            m_fatalBMUSensor->setStyleSheet("background-color:red");
        else
            m_fatalBMUSensor->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellFault.fatalBMSAFE)
            m_fatalBMUAFE->setStyleSheet("background-color:red");
        else
            m_fatalBMUAFE->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellFault.fatalBMSCV)
            m_fatalBMUCV->setStyleSheet("background-color:red");
        else
            m_fatalBMUCV->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellFault.fatalBMSCT)
            m_fatalBMUCT->setStyleSheet("background-color:red");
        else
            m_fatalBMUCT->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellFault.fatalHvcuCom)
            m_fatalHVCUCom->setStyleSheet("background-color:red");
        else
            m_fatalHVCUCom->setStyleSheet("background-color:#32CD32");

        if (g_GetCANBMSData.bmsCellFault.fatalHvcuSensor)
            m_fatalHVCUSensor->setStyleSheet("background-color:red");
        else
            m_fatalHVCUSensor->setStyleSheet("background-color:#32CD32");
    }
    g_BMSSignalData.sig0x18FF04A0 = RECV_SIGNAL_SUCCESSFUL;
}


void BMSInfoWidget::SetBMSCommand(UINT id)
{
    switch (id)
    {
    case 0x4280:
        m_chrgForbidenMark->setStyleSheet("background-color:white");
        m_dischrgForbidenMark->setStyleSheet("background-color:white");
        m_chrgForbidenMark->setEnabled(true);
        m_dischrgForbidenMark->setEnabled(true);

        m_chrgForbidenMark->setText(tr("0x") + tr("%1").arg(g_GetCANBMSData.bmsCommand1.chrgForbidenMark,
                                                 2, 16, QChar('0')).toUpper());
        m_dischrgForbidenMark->setText(tr("0x") + tr("%1").arg(g_GetCANBMSData.bmsCommand1.dischrgForbidenMark,
                                                 2, 16, QChar('0')).toUpper());
        g_BMSSignalData.sig0x4280 = RECV_SIGNAL_SUCCESSFUL;
        break;

    case 0x8200:
        m_sleepCtrl->setEnabled(true);
        m_sleepCtrl->setStyleSheet("background-color:white");
        if (g_GetCANBMSData.bmsCommand2.sleepCtrl == 0x55)
            m_sleepCtrl->setText("休眠");
        else if (g_GetCANBMSData.bmsCommand2.sleepCtrl == 0xaa)
            m_sleepCtrl->setText("唤醒");
        g_BMSSignalData.sig0x8200 = RECV_SIGNAL_SUCCESSFUL;
        break;

    case 0x8210:
        m_chrgEn->setStyleSheet("background-color:white");
        m_dischrgEn->setStyleSheet("background-color:white");
        m_chrgEn->setEnabled(true);
        m_dischrgEn->setEnabled(true);

        m_chrgEn->setText(tr("0x") + tr("%1").arg(g_GetCANBMSData.bmsCommand3.chrgEN,
                                                 2, 16, QChar('0')).toUpper());
        m_dischrgEn->setText(tr("0x") + tr("%1").arg(g_GetCANBMSData.bmsCommand3.dischrgEN,
                                                 2, 16, QChar('0')).toUpper());
        g_BMSSignalData.sig0x8210 = RECV_SIGNAL_SUCCESSFUL;
        break;

    case 0x8220:
        m_relayForceBreak->setEnabled(true);
        m_relayForceBreak->setStyleSheet("background-color:white");
        if (g_GetCANBMSData.bmsCommand4.relayForceBreak == 0xaa)
            m_relayForceBreak->setText("继电器强制断开");
        else if (g_GetCANBMSData.bmsCommand4.relayForceBreak == 0x55)
            m_relayForceBreak->setText("继电器允许闭合");
        g_BMSSignalData.sig0x8220 = RECV_SIGNAL_SUCCESSFUL;
        break;

    default:
        break;
    }
}


void BMSInfoWidget::SetBMSCellConfig(UINT id)
{
    if (id == 0x7320)
    {
        OnlineConfig();
        m_cellTotalNum->setText(tr("%1").arg(g_GetCANBMSData.bmsCellConfig.cellTotalNum));
        m_moudleTotalNum->setText(tr("%1").arg(g_GetCANBMSData.bmsCellConfig.moudleTotalNum));
        m_cellNumInMoudle->setText(tr("%1").arg(g_GetCANBMSData.bmsCellConfig.cellNumInMoudle));
        m_voltageLevel->setText(tr("%1").arg(g_GetCANBMSData.bmsCellConfig.voltageLevel));
        m_capAH->setText(tr("%1").arg(g_GetCANBMSData.bmsCellConfig.capAH));
        g_BMSSignalData.sig0x7320 = RECV_SIGNAL_SUCCESSFUL;
    }
}


void BMSInfoWidget::SetBMSCellBasicPara(UINT id)
{
    switch(id)
    {
    case 0x4230:
        OnlineBasicP1();
        m_maxCellVolt->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP1.maxCellVolt));
        m_minCellVolt->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP1.minCellVolt));
        m_maxCVNo->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP1.maxCVNO));
        m_minCVNo->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP1.minCVNO));
        g_BMSSignalData.sig0x4230 = RECV_SIGNAL_SUCCESSFUL;
        break;

    case 0x4240:
        OnlineBasicP2();
        m_maxCellTemp->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP2.maxCellTemp));
        m_minCellTemp->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP2.minCellTemp));
        m_maxCTNo->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP2.maxCTNO));
        m_minCTNo->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP2.minCTNO));
        g_BMSSignalData.sig0x4240 = RECV_SIGNAL_SUCCESSFUL;
        break;

    case 0x4260:
        OnlineBasicP3();
        m_maxMoudleCV->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP3.maxMoudleCV));
        m_minMoudleCV->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP3.minMoudleCV));
        m_maxMCVNo->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP3.maxMCVNO));
        m_minMCVNo->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP3.minMCVNO));
        g_BMSSignalData.sig0x4260 = RECV_SIGNAL_SUCCESSFUL;
        break;

    case 0x4270:
        OnlineBasicP4();
        m_maxMoudleCt->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP4.maxMoudleCT));
        m_minMoudleCt->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP4.minMoudleCT));
        m_maxMCTNo->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP4.maxMCTNO));
        m_minMCTNo->setText(tr("%1").arg(g_GetCANBMSData.bmsCellBaiscP4.minMCTNO));
        g_BMSSignalData.sig0x4270 = RECV_SIGNAL_SUCCESSFUL;
        break;

    default:
        break;
    }
}


void BMSInfoWidget::SetBMSCellModelPara(UINT id)
{
    switch(id)
    {
    case 0x4200:
        OnlineModuleP();

        if (g_GetCANBMSData.bmsPoll.pollGlobalInfo == 0)
            m_pollGlobalInfo->setText("有效");
        else
            m_pollGlobalInfo->setText("无效");

        g_BMSSignalData.sig0x4200 = RECV_SIGNAL_SUCCESSFUL;
        break;

    case 0x4210:
        OnlineModuleP1();
        m_packVolt->setText(tr("%1").arg(g_GetCANBMSData.bmsCellModuleP1.packVolt));
        m_packcurr->setText(tr("%1").arg(g_GetCANBMSData.bmsCellModuleP1.packCurr));
        m_ambientTempOut->setText(tr("%1").arg(g_GetCANBMSData.bmsCellModuleP1.ambientTempOut));
        m_soc->setText(tr("%1").arg(g_GetCANBMSData.bmsCellModuleP1.SOC));
        m_soh->setText(tr("%1").arg(g_GetCANBMSData.bmsCellModuleP1.SOH));
        m_packPwr->setText(tr("%1").arg(g_GetCANBMSData.bmsCellModuleP1.packPwr));
        g_BMSSignalData.sig0x4210 = RECV_SIGNAL_SUCCESSFUL;
        break;

    case 0x18FF02C0:
        OnlineModuleP2();
        m_ambientTempIn->setText(tr("%1").arg(g_GetCANBMSData.bmsCellModuleP2.ambientTemp));
        g_BMSSignalData.sig0x18FF02C0 = RECV_SIGNAL_SUCCESSFUL;
        break;

    case 0x4220:
        OnlineModuleP3();
        m_chgCutoffVolt->setText(tr("%1").arg(g_GetCANBMSData.bmsCellModuleP3.chgCutoffVolt));
        m_dischgCutoffVolt->setText(tr("%1").arg(g_GetCANBMSData.bmsCellModuleP3.dischgCutoffVolt));
        m_maxChgCurr->setText(tr("%1").arg(g_GetCANBMSData.bmsCellModuleP3.maxChgCurr));
        m_maxDischgCurr->setText(tr("%1").arg(g_GetCANBMSData.bmsCellModuleP3.maxDischgCurr));
        g_BMSSignalData.sig0x4220 = RECV_SIGNAL_SUCCESSFUL;
        break;

    default:
        break;
    }
}


void BMSInfoWidget::SignalTimeout()
{
    /** BMS cmd **/
    if (!g_BMSSignalData.sig0x4200)
    {
        OfflineModuleP();
    }


    /** 电池模组参数信号 **/
    if (!g_BMSSignalData.sig0x4210)
    {
        OfflineModuleP1();
    }

    if (!g_BMSSignalData.sig0x18FF02C0)
    {
        OfflineModuleP2();
    }

    if (!g_BMSSignalData.sig0x4220)
    {
        OfflineModuleP3();
    }

    /** 电池基本参数信号 **/
    if (!g_BMSSignalData.sig0x4230)
    {
        OfflineBasicP1();
    }

    if (!g_BMSSignalData.sig0x4240)
    {
        OfflineBasicP2();
    }

    if (!g_BMSSignalData.sig0x4260)
    {
        OfflineBasicP3();
    }

    if (!g_BMSSignalData.sig0x4270)
    {
        OfflineBasicP4();
    }

    /** 电池状态与故障信息信号 **/
    if (!g_BMSSignalData.sig0x4250)
    {
        m_basicStatus->setEnabled(false);
        m_cyclePeriod->setEnabled(false);
        m_basicStatus->setStyleSheet("background-color:lightgray");
        m_cyclePeriod->setStyleSheet("background-color:lightgray");

        m_errVoltSensor->setEnabled(false);
        m_errTempSensor->setEnabled(false);
        m_errInnCom->setEnabled(false);
        m_errChrgVoltHigh->setEnabled(false);
        m_errWireInversed->setEnabled(false);
        m_errRelaySticky->setEnabled(false);
        m_errVoltSensor->setStyleSheet("background-color:lightgray");
        m_errTempSensor->setStyleSheet("background-color:lightgray");
        m_errInnCom->setStyleSheet("background-color:lightgray");
        m_errChrgVoltHigh->setStyleSheet("background-color:lightgray");
        m_errWireInversed->setStyleSheet("background-color:lightgray");
        m_errRelaySticky->setStyleSheet("background-color:lightgray");

        m_almCellVoltLow->setEnabled(false);
        m_almCellVoltHigh->setEnabled(false);
        m_almPackVoltLow->setEnabled(false);
        m_almPackVoltHigh->setEnabled(false);
        m_almChrgTempLow->setEnabled(false);
        m_almChrgTempHigh->setEnabled(false);
        m_almDischrgTempLow->setEnabled(false);
        m_almDischrgTempHigh->setEnabled(false);
        m_almChrgCurrHigh->setEnabled(false);
        m_almDischrgCurrHigh->setEnabled(false);
        m_almMoudleVoltLow->setEnabled(false);
        m_almMoudleVoltHigh->setEnabled(false);
        m_almCellVoltLow->setStyleSheet("background-color:lightgray");
        m_almCellVoltHigh->setStyleSheet("background-color:lightgray");
        m_almPackVoltLow->setStyleSheet("background-color:lightgray");
        m_almPackVoltHigh->setStyleSheet("background-color:lightgray");
        m_almChrgTempLow->setStyleSheet("background-color:lightgray");
        m_almChrgTempHigh->setStyleSheet("background-color:lightgray");
        m_almDischrgTempLow->setStyleSheet("background-color:lightgray");
        m_almDischrgTempHigh->setStyleSheet("background-color:lightgray");
        m_almChrgCurrHigh->setStyleSheet("background-color:lightgray");
        m_almDischrgCurrHigh->setStyleSheet("background-color:lightgray");
        m_almMoudleVoltLow->setStyleSheet("background-color:lightgray");
        m_almMoudleVoltHigh->setStyleSheet("background-color:lightgray");

        m_pCellVoltLow->setEnabled(false);
        m_pCellVoltHigh->setEnabled(false);
        m_pPackVoltLow->setEnabled(false);
        m_pPackVoltHigh->setEnabled(false);
        m_pChrgTempLow->setEnabled(false);
        m_pChrgTempHigh->setEnabled(false);
        m_pDischrgTempLow->setEnabled(false);
        m_pDischrgTempHigh->setEnabled(false);
        m_pChrgCurrHigh->setEnabled(false);
        m_pDischrgCurrHigh->setEnabled(false);
        m_pMoudleVoltLow->setEnabled(false);
        m_pMoudleVoltHigh->setEnabled(false);
        m_pCellVoltLow->setStyleSheet("background-color:lightgray");
        m_pCellVoltHigh->setStyleSheet("background-color:lightgray");
        m_pPackVoltLow->setStyleSheet("background-color:lightgray");
        m_pPackVoltHigh->setStyleSheet("background-color:lightgray");
        m_pChrgTempLow->setStyleSheet("background-color:lightgray");
        m_pChrgTempHigh->setStyleSheet("background-color:lightgray");
        m_pDischrgTempLow->setStyleSheet("background-color:lightgray");
        m_pDischrgTempHigh->setStyleSheet("background-color:lightgray");
        m_pChrgCurrHigh->setStyleSheet("background-color:lightgray");
        m_pDischrgCurrHigh->setStyleSheet("background-color:lightgray");
        m_pMoudleVoltLow->setStyleSheet("background-color:lightgray");
        m_pMoudleVoltHigh->setStyleSheet("background-color:lightgray");
    }

    if (!g_BMSSignalData.sig0x18FF02A0)
    {
        m_forceChrgSt->setEnabled(false);
        m_posiRlySt->setEnabled(false);
        m_negRlySt->setEnabled(false);
        m_rlySticky->setEnabled(false);
        m_almSt->setEnabled(false);
        m_moudleCfm->setEnabled(false);
        m_moudleNum->setEnabled(false);
        m_forceChrgSt->setStyleSheet("background-color:lightgray");
        m_posiRlySt->setStyleSheet("background-color:lightgray");
        m_negRlySt->setStyleSheet("background-color:lightgray");
        m_rlySticky->setStyleSheet("background-color:lightgray");
        m_almSt->setStyleSheet("background-color:lightgray");
        m_moudleCfm->setStyleSheet("background-color:lightgray");
        m_moudleNum->setStyleSheet("background-color:lightgray");
    }

    if (!g_BMSSignalData.sig0x18FF04A0)
    {
        m_fatalPOSC->setEnabled(false);
        m_fatalBMUSensor->setEnabled(false);
        m_fatalBMUAFE->setEnabled(false);
        m_fatalBMUCV->setEnabled(false);
        m_fatalBMUCT->setEnabled(false);
        m_fatalHVCUCom->setEnabled(false);
        m_fatalHVCUSensor->setEnabled(false);
        m_fatalPOSC->setStyleSheet("background-color:lightgray");
        m_fatalBMUSensor->setStyleSheet("background-color:lightgray");
        m_fatalBMUAFE->setStyleSheet("background-color:lightgray");
        m_fatalBMUCV->setStyleSheet("background-color:lightgray");
        m_fatalBMUCT->setStyleSheet("background-color:lightgray");
        m_fatalHVCUCom->setStyleSheet("background-color:lightgray");
        m_fatalHVCUSensor->setStyleSheet("background-color:lightgray");
    }

    /** 指令信号 **/
    if (!g_BMSSignalData.sig0x4280)
    {
        m_chrgForbidenMark->setEnabled(false);
        m_dischrgForbidenMark->setEnabled(false);
        m_chrgForbidenMark->setStyleSheet("background-color:lightgray");
        m_dischrgForbidenMark->setStyleSheet("background-color:lightgray");
    }

    if (!g_BMSSignalData.sig0x8200)
    {
        m_sleepCtrl->setEnabled(false);
        m_sleepCtrl->setStyleSheet("background-color:lightgray");
    }

    if (!g_BMSSignalData.sig0x8210)
    {
        m_chrgEn->setEnabled(false);
        m_dischrgEn->setEnabled(false);
        m_chrgEn->setStyleSheet("background-color:lightgray");
        m_dischrgEn->setStyleSheet("background-color:lightgray");
    }

    if (!g_BMSSignalData.sig0x8220)
    {
        m_relayForceBreak->setEnabled(false);
        m_relayForceBreak->setStyleSheet("background-color:lightgray");
    }

    /** 电池配置信息信号 **/
    if (!g_BMSSignalData.sig0x7320)
    {
        OfflineConfig();
    }

    g_BMSSignalData.sig0x4200 = RECV_SIGNAL_FAIL;
    g_BMSSignalData.sig0x4210 = RECV_SIGNAL_FAIL;
    g_BMSSignalData.sig0x18FF02C0 = RECV_SIGNAL_FAIL;
    g_BMSSignalData.sig0x4220 = RECV_SIGNAL_FAIL;
    g_BMSSignalData.sig0x4230 = RECV_SIGNAL_FAIL;
    g_BMSSignalData.sig0x4240 = RECV_SIGNAL_FAIL;
    g_BMSSignalData.sig0x4260 = RECV_SIGNAL_FAIL;
    g_BMSSignalData.sig0x4270 = RECV_SIGNAL_FAIL;
    g_BMSSignalData.sig0x4250 = RECV_SIGNAL_FAIL;
    g_BMSSignalData.sig0x18FF02A0 = RECV_SIGNAL_FAIL;
    g_BMSSignalData.sig0x18FF04A0 = RECV_SIGNAL_FAIL;
    g_BMSSignalData.sig0x4280 = RECV_SIGNAL_FAIL;
    g_BMSSignalData.sig0x7320 = RECV_SIGNAL_FAIL;
    g_BMSSignalData.sig0x8200 = RECV_SIGNAL_FAIL;
    g_BMSSignalData.sig0x8210 = RECV_SIGNAL_FAIL;
    g_BMSSignalData.sig0x8220 = RECV_SIGNAL_FAIL;
}

void BMSInfoWidget::OnlineModuleP()
{
    m_pollGlobalInfo->setStyleSheet("background-color:white");
    m_pollGlobalInfo->setEnabled(true);
}


void BMSInfoWidget::OfflineModuleP()
{
    m_pollGlobalInfo->setStyleSheet("background-color:lightgray");
    m_pollGlobalInfo->setEnabled(false);
}


void BMSInfoWidget::OnlineModuleP1()
{
    m_packVolt->setStyleSheet("background-color:white");
    m_packcurr->setStyleSheet("background-color:white");
    m_ambientTempOut->setStyleSheet("background-color:white");
    m_soc->setStyleSheet("background-color:white");
    m_soh->setStyleSheet("background-color:white");
    m_packPwr->setStyleSheet("background-color:white");

    m_packVolt->setEnabled(true);
    m_packcurr->setEnabled(true);
    m_ambientTempOut->setEnabled(true);
    m_soc->setEnabled(true);
    m_soh->setEnabled(true);
    m_packPwr->setEnabled(true);
}


void BMSInfoWidget::OfflineModuleP1()
{
    m_packVolt->setEnabled(false);
    m_packcurr->setEnabled(false);
    m_ambientTempOut->setEnabled(false);
    m_soc->setEnabled(false);
    m_soh->setEnabled(false);
    m_packPwr->setEnabled(false);

    m_packVolt->setStyleSheet("background-color:lightgray");
    m_packcurr->setStyleSheet("background-color:lightgray");
    m_ambientTempOut->setStyleSheet("background-color:lightgray");
    m_soc->setStyleSheet("background-color:lightgray");
    m_soh->setStyleSheet("background-color:lightgray");
    m_packPwr->setStyleSheet("background-color:lightgray");
}


void BMSInfoWidget::OnlineModuleP2()
{
    m_ambientTempIn->setStyleSheet("background-color:white");
    m_ambientTempIn->setEnabled(true);
}


void BMSInfoWidget::OfflineModuleP2()
{
    m_ambientTempIn->setEnabled(false);
    m_ambientTempIn->setStyleSheet("background-color:lightgray");
}


void BMSInfoWidget::OnlineModuleP3()
{
    m_chgCutoffVolt->setStyleSheet("background-color:white");
    m_dischgCutoffVolt->setStyleSheet("background-color:white");
    m_maxChgCurr->setStyleSheet("background-color:white");
    m_maxDischgCurr->setStyleSheet("background-color:white");

    m_chgCutoffVolt->setEnabled(true);
    m_dischgCutoffVolt->setEnabled(true);
    m_maxChgCurr->setEnabled(true);
    m_maxDischgCurr->setEnabled(true);
}


void BMSInfoWidget::OfflineModuleP3()
{
    m_chgCutoffVolt->setEnabled(false);
    m_dischgCutoffVolt->setEnabled(false);
    m_maxChgCurr->setEnabled(false);
    m_maxDischgCurr->setEnabled(false);

    m_chgCutoffVolt->setStyleSheet("background-color:lightgray");
    m_dischgCutoffVolt->setStyleSheet("background-color:lightgray");
    m_maxChgCurr->setStyleSheet("background-color:lightgray");
    m_maxDischgCurr->setStyleSheet("background-color:lightgray");
}


void BMSInfoWidget::OnlineBasicP1()
{
    m_maxCellVolt->setStyleSheet("background-color:white");
    m_minCellVolt->setStyleSheet("background-color:white");
    m_maxCVNo->setStyleSheet("background-color:white");
    m_minCVNo->setStyleSheet("background-color:white");

    m_maxCellVolt->setEnabled(true);
    m_minCellVolt->setEnabled(true);
    m_maxCVNo->setEnabled(true);
    m_minCVNo->setEnabled(true);
}


void BMSInfoWidget::OfflineBasicP1()
{
    m_maxCellVolt->setEnabled(false);
    m_minCellVolt->setEnabled(false);
    m_maxCVNo->setEnabled(false);
    m_minCVNo->setEnabled(false);

    m_maxCellVolt->setStyleSheet("background-color:lightgray");
    m_minCellVolt->setStyleSheet("background-color:lightgray");
    m_maxCVNo->setStyleSheet("background-color:lightgray");
    m_minCVNo->setStyleSheet("background-color:lightgray");
}


void BMSInfoWidget::OnlineBasicP2()
{
    m_maxCellTemp->setStyleSheet("background-color:white");
    m_minCellTemp->setStyleSheet("background-color:white");
    m_maxCTNo->setStyleSheet("background-color:white");
    m_minCTNo->setStyleSheet("background-color:white");

    m_maxCellTemp->setEnabled(true);
    m_minCellTemp->setEnabled(true);
    m_maxCTNo->setEnabled(true);
    m_minCTNo->setEnabled(true);
}


void BMSInfoWidget::OfflineBasicP2()
{
    m_maxCellTemp->setEnabled(false);
    m_minCellTemp->setEnabled(false);
    m_maxCTNo->setEnabled(false);
    m_minCTNo->setEnabled(false);

    m_maxCellTemp->setStyleSheet("background-color:lightgray");
    m_minCellTemp->setStyleSheet("background-color:lightgray");
    m_maxCTNo->setStyleSheet("background-color:lightgray");
    m_minCTNo->setStyleSheet("background-color:lightgray");
}


void BMSInfoWidget::OnlineBasicP3()
{
    m_maxMoudleCV->setStyleSheet("background-color:white");
    m_minMoudleCV->setStyleSheet("background-color:white");
    m_maxMCVNo->setStyleSheet("background-color:white");
    m_minMCVNo->setStyleSheet("background-color:white");

    m_maxMoudleCV->setEnabled(true);
    m_minMoudleCV->setEnabled(true);
    m_maxMCVNo->setEnabled(true);
    m_minMCVNo->setEnabled(true);
}


void BMSInfoWidget::OfflineBasicP3()
{
    m_maxMoudleCV->setEnabled(false);
    m_minMoudleCV->setEnabled(false);
    m_maxMCVNo->setEnabled(false);
    m_minMCVNo->setEnabled(false);

    m_maxMoudleCV->setStyleSheet("background-color:lightgray");
    m_minMoudleCV->setStyleSheet("background-color:lightgray");
    m_maxMCVNo->setStyleSheet("background-color:lightgray");
    m_minMCVNo->setStyleSheet("background-color:lightgray");
}


void BMSInfoWidget::OnlineBasicP4()
{
    m_maxMoudleCt->setStyleSheet("background-color:white");
    m_minMoudleCt->setStyleSheet("background-color:white");
    m_maxMCTNo->setStyleSheet("background-color:white");
    m_minMCTNo->setStyleSheet("background-color:white");

    m_maxMoudleCt->setEnabled(true);
    m_minMoudleCt->setEnabled(true);
    m_maxMCTNo->setEnabled(true);
    m_minMCTNo->setEnabled(true);
}


void BMSInfoWidget::OfflineBasicP4()
{
    m_maxMoudleCt->setEnabled(false);
    m_minMoudleCt->setEnabled(false);
    m_maxMCTNo->setEnabled(false);
    m_minMCTNo->setEnabled(false);

    m_maxMoudleCt->setStyleSheet("background-color:lightgray");
    m_minMoudleCt->setStyleSheet("background-color:lightgray");
    m_maxMCTNo->setStyleSheet("background-color:lightgray");
    m_minMCTNo->setStyleSheet("background-color:lightgray");
}


void BMSInfoWidget::OnlineConfig()
{
    m_cellTotalNum->setStyleSheet("background-color:white");
    m_moudleTotalNum->setStyleSheet("background-color:white");
    m_cellNumInMoudle->setStyleSheet("background-color:white");
    m_voltageLevel->setStyleSheet("background-color:white");
    m_capAH->setStyleSheet("background-color:white");

    m_cellTotalNum->setEnabled(true);
    m_moudleTotalNum->setEnabled(true);
    m_cellNumInMoudle->setEnabled(true);
    m_voltageLevel->setEnabled(true);
    m_capAH->setEnabled(true);
}


void BMSInfoWidget::OfflineConfig()
{
    m_cellTotalNum->setEnabled(false);
    m_moudleTotalNum->setEnabled(false);
    m_cellNumInMoudle->setEnabled(false);
    m_voltageLevel->setEnabled(false);
    m_capAH->setEnabled(false);

    m_cellTotalNum->setStyleSheet("background-color:lightgray");
    m_moudleTotalNum->setStyleSheet("background-color:lightgray");
    m_cellNumInMoudle->setStyleSheet("background-color:lightgray");
    m_voltageLevel->setStyleSheet("background-color:lightgray");
    m_capAH->setStyleSheet("background-color:lightgray");
}
