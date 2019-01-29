#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include "BMSInfoWidget.h"
#include "ControlCAN.h"
#include "widgetdatastructure.h"
#include "databasedefine.h"


BMSInfoWidget::BMSInfoWidget(QWidget *parent)
    :QWidget(parent)
{
    m_bmsInfoLayout = new QGridLayout(this);

    m_cellModuleParGroup = new QGroupBox("电池模组参数", this);
    BuildCellModuleParameterUI();

    m_cellBasicParGroup = new QGroupBox("电池基本参数", this);
    BuildCellBasicParameterUI();

    m_cellConfigInfoGroup = new QGroupBox("电池配置信息", this);
    BuildCellConfigInfoUI();

    m_cellStatusInfoGroup = new QGroupBox("电池状态信息", this);
    BuildCellStatusInfoUI();

    m_cellFaultInfoGroup = new QGroupBox("电池故障信息", this);
    cellFaultInfoUI();

    m_cellAlarmInfoGroup = new QGroupBox("电池告警信息", this);
    CellAlarmInfoUI();

    m_cellProInfoGroup = new QGroupBox("电池保护信息", this);
    CellProInfoUI();

    m_commandInfoGroup = new QGroupBox("指令", this);
    BuildCommandInfoUI();

    m_bmsInfoLayout->setRowStretch(0, 2);
    m_bmsInfoLayout->setRowStretch(1, 1);
    m_bmsInfoLayout->setRowStretch(2, 1);
    m_bmsInfoLayout->setRowStretch(3, 1);
    m_bmsInfoLayout->setRowStretch(4, 1);

    m_bmsInfoLayout->addWidget(m_cellModuleParGroup, 0, 0);
    m_bmsInfoLayout->addWidget(m_cellBasicParGroup, 1, 0, 3, 1);
    m_bmsInfoLayout->addWidget(m_cellConfigInfoGroup, 4, 0);
    m_bmsInfoLayout->addWidget(m_cellStatusInfoGroup, 0, 1);
    m_bmsInfoLayout->addWidget(m_cellFaultInfoGroup, 1, 1);
    m_bmsInfoLayout->addWidget(m_cellAlarmInfoGroup, 2, 1);
    m_bmsInfoLayout->addWidget(m_cellProInfoGroup, 3, 1);
    m_bmsInfoLayout->addWidget(m_commandInfoGroup, 4, 1);

    m_bmsInfoLayout->setColumnStretch(0, 2);
    m_bmsInfoLayout->setColumnStretch(1, 3);

    setLayout(m_bmsInfoLayout);

    m_BMSWidgetTimer = new QTimer(this);
    connect(m_BMSWidgetTimer, SIGNAL(timeout()), this, SLOT(UpdateWidget()));
    m_BMSWidgetTimer->start(100);

    m_BMSSignalTimeout = new QTimer(this);
    connect(m_BMSSignalTimeout, SIGNAL(timeout()), this, SLOT(SignalTimeout()));
    m_BMSSignalTimeout->start(10000);
}


BMSInfoWidget::~BMSInfoWidget()
{
    delete m_cellModuleLayout;
    delete m_cellBasicLayout;
    delete m_cellConfigInfoLayout;
    delete m_cellStatusInfoLayout;
    delete m_commandInfoLayout;
    delete m_cellFaultInfoLayout;
    delete m_cellAlarmInfoLayout;
    delete m_cellProInfoLayout;
}


void BMSInfoWidget::BuildCellModuleParameterUI()
{
    m_cellModuleLayout = new QGridLayout();

    QLabel *pollGlobalInfolabel = new QLabel(QString("%1：").arg(BMS_POLL_GLOBAL_INFO), this);
    QLabel *packVoltLabel = new QLabel("电池组总压：", this);
    QLabel *currLabel = new QLabel("电池组电流：", this);
    QLabel *packVol2Label = new QLabel("环境温度(外)：", this);
    QLabel *socLabel = new QLabel("SOC：", this);
    QLabel *sohLabel = new QLabel("SOH：", this);
    QLabel *pwrLabel = new QLabel("电池组功率：", this);
    QLabel *ambientTempLabel = new QLabel("环境温度(内)：", this);
    QLabel *chgCutoffVoltLabel = new QLabel("充电截止电压：", this);
    QLabel *dischgCutoffVoltLabel = new QLabel("放电截止电压：", this);
    QLabel *maxChgCurrLabel = new QLabel("最大充电电流：", this);
    QLabel *maxDischgCurrLabel = new QLabel("最大放电电流：", this);

    m_pollGlobalInfo = new QLineEdit(this);
    m_packVolt = new QLineEdit(this);
    m_packcurr = new QLineEdit(this);
    m_ambientTempIn = new QLineEdit(this);
    m_soc = new QLineEdit(this);
    m_soh = new QLineEdit(this);
    m_ambientTempOut = new QLineEdit(this);
    m_packPwr = new QLineEdit(this);
    m_chgCutoffVolt = new QLineEdit(this);
    m_dischgCutoffVolt = new QLineEdit(this);
    m_maxChgCurr = new QLineEdit(this);
    m_maxDischgCurr = new QLineEdit(this);

    OfflineModuleP();
    OfflineModuleP1();
    OfflineModuleP2();
    OfflineModuleP3();

    m_pollGlobalInfo->setAlignment(Qt::AlignCenter);
    m_packVolt->setAlignment(Qt::AlignCenter);
    m_packcurr->setAlignment(Qt::AlignCenter);
    m_ambientTempIn->setAlignment(Qt::AlignCenter);
    m_soc->setAlignment(Qt::AlignCenter);
    m_soh->setAlignment(Qt::AlignCenter);
    m_ambientTempOut->setAlignment(Qt::AlignCenter);
    m_packPwr->setAlignment(Qt::AlignCenter);
    m_chgCutoffVolt->setAlignment(Qt::AlignCenter);
    m_dischgCutoffVolt->setAlignment(Qt::AlignCenter);
    m_maxChgCurr->setAlignment(Qt::AlignCenter);
    m_maxDischgCurr->setAlignment(Qt::AlignCenter);

    QLabel *packVoltUnit = new QLabel("V", this);
    QLabel *currUnit = new QLabel("A", this);
    QLabel *ambientTempUnit = new QLabel("℃", this);
    QLabel *socUnit = new QLabel("%", this);
    QLabel *sohUnit = new QLabel("%", this);
    QLabel *OutVoltUnit = new QLabel("℃", this);
    QLabel *pwrUnit = new QLabel("W", this);
    QLabel *chgCutoffVoltUnit = new QLabel("V", this);
    QLabel *dischgCutoffVoltUnit = new QLabel("V", this);
    QLabel *maxChgCurrUnit = new QLabel("A", this);
    QLabel *maxDischgCurrUnit = new QLabel("A", this);

    m_cellModuleLayout->addWidget(pollGlobalInfolabel, 0, 0);
    m_cellModuleLayout->addWidget(m_pollGlobalInfo, 0, 1);
    m_cellModuleLayout->addWidget(packVoltLabel, 1, 0);
    m_cellModuleLayout->addWidget(m_packVolt, 1, 1);
    m_cellModuleLayout->addWidget(packVoltUnit, 1, 2);
    m_cellModuleLayout->addWidget(currLabel, 2, 0);
    m_cellModuleLayout->addWidget(m_packcurr, 2, 1);
    m_cellModuleLayout->addWidget(currUnit, 2, 2);
    m_cellModuleLayout->addWidget(packVol2Label, 3, 0);
    m_cellModuleLayout->addWidget(m_ambientTempOut, 3, 1);
    m_cellModuleLayout->addWidget(OutVoltUnit, 3, 2);
    m_cellModuleLayout->addWidget(socLabel, 4, 0);
    m_cellModuleLayout->addWidget(m_soc, 4, 1);
    m_cellModuleLayout->addWidget(socUnit, 4, 2);
    m_cellModuleLayout->addWidget(sohLabel, 5, 0);
    m_cellModuleLayout->addWidget(m_soh, 5, 1);
    m_cellModuleLayout->addWidget(sohUnit, 5, 2);

    m_cellModuleLayout->addWidget(pwrLabel, 0, 4);
    m_cellModuleLayout->addWidget(m_packPwr, 0, 5);
    m_cellModuleLayout->addWidget(pwrUnit, 0, 6);
    m_cellModuleLayout->addWidget(ambientTempLabel, 1, 4);
    m_cellModuleLayout->addWidget(m_ambientTempIn, 1, 5);
    m_cellModuleLayout->addWidget(ambientTempUnit, 1, 6);
    m_cellModuleLayout->addWidget(chgCutoffVoltLabel, 2, 4);
    m_cellModuleLayout->addWidget(m_chgCutoffVolt, 2, 5);
    m_cellModuleLayout->addWidget(chgCutoffVoltUnit, 2, 6);
    m_cellModuleLayout->addWidget(dischgCutoffVoltLabel, 3, 4);
    m_cellModuleLayout->addWidget(m_dischgCutoffVolt, 3, 5);
    m_cellModuleLayout->addWidget(dischgCutoffVoltUnit, 3, 6);
    m_cellModuleLayout->addWidget(maxChgCurrLabel, 4, 4);
    m_cellModuleLayout->addWidget(m_maxChgCurr, 4, 5);
    m_cellModuleLayout->addWidget(maxChgCurrUnit, 4, 6);
    m_cellModuleLayout->addWidget(maxDischgCurrLabel, 5, 4);
    m_cellModuleLayout->addWidget(m_maxDischgCurr, 5, 5);
    m_cellModuleLayout->addWidget(maxDischgCurrUnit, 5, 6);

    m_cellModuleLayout->setColumnStretch(0, 2);
    m_cellModuleLayout->setColumnStretch(1, 3);
    m_cellModuleLayout->setColumnStretch(2, 0.5);
    m_cellModuleLayout->setColumnStretch(3, 2);
    m_cellModuleLayout->setColumnStretch(4, 2);
    m_cellModuleLayout->setColumnStretch(5, 3);
    m_cellModuleLayout->setColumnStretch(6, 0.5);

    m_cellModuleParGroup->setLayout(m_cellModuleLayout);
}


void BMSInfoWidget::BuildCellBasicParameterUI()
{
    m_cellBasicLayout = new QGridLayout();

    QLabel *maxCellVoltLabel = new QLabel("最高单芯电压：", this);
    QLabel *maxCVNoLabel = new QLabel("最高单芯电压编号：", this);
    QLabel *minCellVoltLabel = new QLabel("最低单芯电压：", this);
    QLabel *minCVNoLabel = new QLabel("最低单芯电压编号：", this);
    QLabel *maxCellTempLabel = new QLabel("最高单芯温度：", this);
    QLabel *maxCTNoLabel = new QLabel("最高单芯温度编号：", this);
    QLabel *minCellTempLabel = new QLabel("最低单芯温度：", this);
    QLabel *minCTNoLabel = new QLabel("最低单芯温度编号：", this);
    QLabel *maxMoudleCVLabel = new QLabel("模组最高单芯电压：", this);
    QLabel *maxMCVNoLabel = new QLabel("模组最高单芯电压编号：", this);
    QLabel *minMoudleCVLabel = new QLabel("模组最低单芯电压：", this);
    QLabel *minMCVNoLabel = new QLabel("模组最低单芯电压编号：", this);
    QLabel *maxMoudleCtLabel = new QLabel("模组最高单芯温度：", this);
    QLabel *maxMCTNoLabel = new QLabel("模组最高单芯温度编号：", this);
    QLabel *minMoudleCtLabel = new QLabel("模组最低单芯温度：", this);
    QLabel *minMCTNoLabel = new QLabel("模组最低单芯温度编号：", this);

    m_maxCellVolt = new QLineEdit(this);
    m_maxCVNo = new QLineEdit(this);
    m_minCellVolt = new QLineEdit(this);
    m_minCVNo = new QLineEdit(this);
    m_maxCellTemp = new QLineEdit(this);
    m_maxCTNo = new QLineEdit(this);
    m_minCellTemp = new QLineEdit(this);
    m_minCTNo = new QLineEdit(this);
    m_maxMoudleCV = new QLineEdit(this);
    m_maxMCVNo = new QLineEdit(this);
    m_minMoudleCV = new QLineEdit(this);
    m_minMCVNo = new QLineEdit(this);
    m_maxMoudleCt = new QLineEdit(this);
    m_maxMCTNo = new QLineEdit(this);
    m_minMoudleCt = new QLineEdit(this);
    m_minMCTNo = new QLineEdit(this);

    OfflineBasicP1();
    OfflineBasicP2();
    OfflineBasicP3();
    OfflineBasicP4();

    m_maxCellVolt->setAlignment(Qt::AlignCenter);
    m_maxCVNo->setAlignment(Qt::AlignCenter);
    m_minCellVolt->setAlignment(Qt::AlignCenter);
    m_minCVNo->setAlignment(Qt::AlignCenter);
    m_maxCellTemp->setAlignment(Qt::AlignCenter);
    m_maxCTNo->setAlignment(Qt::AlignCenter);
    m_minCellTemp->setAlignment(Qt::AlignCenter);
    m_minCTNo->setAlignment(Qt::AlignCenter);
    m_maxMoudleCV->setAlignment(Qt::AlignCenter);
    m_maxMCVNo->setAlignment(Qt::AlignCenter);
    m_minMoudleCV->setAlignment(Qt::AlignCenter);
    m_minMCVNo->setAlignment(Qt::AlignCenter);
    m_maxMoudleCt->setAlignment(Qt::AlignCenter);
    m_maxMCTNo->setAlignment(Qt::AlignCenter);
    m_minMoudleCt->setAlignment(Qt::AlignCenter);
    m_minMCTNo->setAlignment(Qt::AlignCenter);

    QLabel *maxCellVoltUnit = new QLabel("mV", this);
    QLabel *minCellVoltUnit = new QLabel("mV", this);
    QLabel *maxCellTempUnit = new QLabel("℃", this);
    QLabel *minCellTempUnit = new QLabel("℃", this);
    QLabel *maxMoudleCVUnit = new QLabel("mV", this);
    QLabel *minMoudleCVUnit = new QLabel("mV", this);
    QLabel *maxMoudleCtUnit = new QLabel("℃", this);
    QLabel *minMoudleCtUnit = new QLabel("℃", this);

    m_cellBasicLayout->addWidget(maxCellVoltLabel, 0, 0);
    m_cellBasicLayout->addWidget(m_maxCellVolt, 0, 1);
    m_cellBasicLayout->addWidget(maxCellVoltUnit, 0, 2);
    m_cellBasicLayout->addWidget(maxCVNoLabel, 0, 4);
    m_cellBasicLayout->addWidget(m_maxCVNo, 0, 5);

    m_cellBasicLayout->addWidget(minCellVoltLabel, 1, 0);
    m_cellBasicLayout->addWidget(m_minCellVolt, 1, 1);
    m_cellBasicLayout->addWidget(minCellVoltUnit, 1, 2);
    m_cellBasicLayout->addWidget(minCVNoLabel, 1, 4);
    m_cellBasicLayout->addWidget(m_minCVNo, 1, 5);

    m_cellBasicLayout->addWidget(maxCellTempLabel, 2, 0);
    m_cellBasicLayout->addWidget(m_maxCellTemp, 2, 1);
    m_cellBasicLayout->addWidget(maxCellTempUnit, 2, 2);
    m_cellBasicLayout->addWidget(maxCTNoLabel, 2, 4);
    m_cellBasicLayout->addWidget(m_maxCTNo, 2, 5);

    m_cellBasicLayout->addWidget(minCellTempLabel, 3, 0);
    m_cellBasicLayout->addWidget(m_minCellTemp, 3, 1);
    m_cellBasicLayout->addWidget(minCellTempUnit, 3, 2);
    m_cellBasicLayout->addWidget(minCTNoLabel, 3, 4);
    m_cellBasicLayout->addWidget(m_minCTNo, 3, 5);

    m_cellBasicLayout->addWidget(maxMoudleCVLabel, 4, 0);
    m_cellBasicLayout->addWidget(m_maxMoudleCV, 4, 1);
    m_cellBasicLayout->addWidget(maxMoudleCVUnit, 4, 2);
    m_cellBasicLayout->addWidget(maxMCVNoLabel, 4, 4);
    m_cellBasicLayout->addWidget(m_maxMCVNo, 4, 5);

    m_cellBasicLayout->addWidget(minMoudleCVLabel, 5, 0);
    m_cellBasicLayout->addWidget(m_minMoudleCV, 5, 1);
    m_cellBasicLayout->addWidget(minMoudleCVUnit, 5, 2);
    m_cellBasicLayout->addWidget(minMCVNoLabel, 5, 4);
    m_cellBasicLayout->addWidget(m_minMCVNo, 5, 5);

    m_cellBasicLayout->addWidget(maxMoudleCtLabel, 6, 0);
    m_cellBasicLayout->addWidget(m_maxMoudleCt, 6, 1);
    m_cellBasicLayout->addWidget(maxMoudleCtUnit, 6, 2);
    m_cellBasicLayout->addWidget(maxMCTNoLabel, 6, 4);
    m_cellBasicLayout->addWidget(m_maxMCTNo, 6, 5);

    m_cellBasicLayout->addWidget(minMoudleCtLabel, 7, 0);
    m_cellBasicLayout->addWidget(m_minMoudleCt, 7, 1);
    m_cellBasicLayout->addWidget(minMoudleCtUnit, 7, 2);
    m_cellBasicLayout->addWidget(minMCTNoLabel, 7, 4);
    m_cellBasicLayout->addWidget(m_minMCTNo, 7, 5);

    m_cellBasicLayout->setColumnStretch(0, 2);
    m_cellBasicLayout->setColumnStretch(1, 3);
    m_cellBasicLayout->setColumnStretch(2, 0.5);
    m_cellBasicLayout->setColumnStretch(3, 2);
    m_cellBasicLayout->setColumnStretch(4, 2);
    m_cellBasicLayout->setColumnStretch(5, 3);
    m_cellBasicLayout->setColumnStretch(6, 0.5);

    m_cellBasicParGroup->setLayout(m_cellBasicLayout);
}


void BMSInfoWidget::BuildCellConfigInfoUI()
{
    m_cellConfigInfoLayout = new QGridLayout();

    QLabel *cellTotalNumLabel = new QLabel("电芯总数：", this);
    QLabel *moudleTotalNumLabel = new QLabel("模组总数：", this);
    QLabel *cellNumInMoudleLabel = new QLabel("单芯串数：", this);
    QLabel *voltageLevelLabel = new QLabel("电芯标称电压：", this);
    QLabel *capAHLabel = new QLabel("电芯容量：", this);
    QLabel *voltageLevelUnit = new QLabel("mV", this);
    QLabel *capAHUnit = new QLabel("AH", this);

    m_cellTotalNum = new QLineEdit(this);
    m_moudleTotalNum = new QLineEdit(this);
    m_cellNumInMoudle = new QLineEdit(this);
    m_voltageLevel = new QLineEdit(this);
    m_capAH = new QLineEdit(this);

    m_cellTotalNum->setAlignment(Qt::AlignCenter);
    m_moudleTotalNum->setAlignment(Qt::AlignCenter);
    m_cellNumInMoudle->setAlignment(Qt::AlignCenter);
    m_voltageLevel->setAlignment(Qt::AlignCenter);
    m_capAH->setAlignment(Qt::AlignCenter);

    OfflineConfig();

    m_cellConfigInfoLayout->addWidget(cellTotalNumLabel, 0, 0);
    m_cellConfigInfoLayout->addWidget(m_cellTotalNum, 0, 1);
    m_cellConfigInfoLayout->addWidget(moudleTotalNumLabel, 0, 4);
    m_cellConfigInfoLayout->addWidget(m_moudleTotalNum, 0, 5);

    m_cellConfigInfoLayout->addWidget(cellNumInMoudleLabel, 1, 0);
    m_cellConfigInfoLayout->addWidget(m_cellNumInMoudle, 1, 1);

    m_cellConfigInfoLayout->addWidget(voltageLevelLabel, 2, 0);
    m_cellConfigInfoLayout->addWidget(m_voltageLevel, 2, 1);
    m_cellConfigInfoLayout->addWidget(voltageLevelUnit, 2, 2);
    m_cellConfigInfoLayout->addWidget(capAHLabel, 2, 4);
    m_cellConfigInfoLayout->addWidget(m_capAH, 2, 5);
    m_cellConfigInfoLayout->addWidget(capAHUnit, 2, 6);

    m_cellConfigInfoLayout->setColumnStretch(0, 2);
    m_cellConfigInfoLayout->setColumnStretch(1, 3);
    m_cellConfigInfoLayout->setColumnStretch(2, 1);
    m_cellConfigInfoLayout->setColumnStretch(3, 1);
    m_cellConfigInfoLayout->setColumnStretch(4, 2);
    m_cellConfigInfoLayout->setColumnStretch(5, 3);
    m_cellConfigInfoLayout->setColumnStretch(6, 1);

    m_cellConfigInfoGroup->setLayout(m_cellConfigInfoLayout);
}


void BMSInfoWidget::BuildCellStatusInfoUI()
{
    m_cellStatusInfoLayout = new QGridLayout();

    QLabel *basicStatusLabel = new QLabel("基础状态：", this);
    QLabel *cyclePeriodLabel = new QLabel("循环周期：", this);
    QLabel *forceChrgStLabel = new QLabel("强制充电状态：", this);
    QLabel *posiRlyStLabel = new QLabel("继电器1闭合状态：", this);
    QLabel *negRlyStLabel = new QLabel("继电器2闭合状态：", this);
    QLabel *rlyStickyLabel = new QLabel("继电器粘滞", this);
    QLabel *almStLabel = new QLabel("故障等级：", this);
    QLabel *moudleCfmLabel = new QLabel("模组数确认状态：", this);
    QLabel *moudleNumLabel = new QLabel("模组数量：", this);
    QLabel *fatalPOSCLabel = new QLabel("自检状态：", this);

    m_basicStatus = new QLineEdit(this);
    m_cyclePeriod = new QLineEdit(this);
    m_forceChrgSt = new QLineEdit(this);
    m_posiRlySt = new QLineEdit(this);
    m_negRlySt = new QLineEdit(this);
    m_rlySticky = new QLineEdit(this);
    m_almSt = new QLineEdit(this);
    m_moudleCfm = new QLineEdit(this);
    m_moudleNum = new QLineEdit(this);
    m_fatalPOSC = new QLineEdit(this);

    m_basicStatus->setEnabled(false);
    m_cyclePeriod->setEnabled(false);
    m_forceChrgSt->setEnabled(false);
    m_posiRlySt->setEnabled(false);
    m_negRlySt->setEnabled(false);
    m_rlySticky->setEnabled(false);
    m_almSt->setEnabled(false);
    m_moudleCfm->setEnabled(false);
    m_fatalPOSC->setEnabled(false);
    m_moudleNum->setEnabled(false);

    m_basicStatus->setAlignment(Qt::AlignCenter);
    m_cyclePeriod->setAlignment(Qt::AlignCenter);
    m_forceChrgSt->setAlignment(Qt::AlignCenter);
    m_posiRlySt->setAlignment(Qt::AlignCenter);
    m_negRlySt->setAlignment(Qt::AlignCenter);
    m_rlySticky->setAlignment(Qt::AlignCenter);
    m_almSt->setAlignment(Qt::AlignCenter);
    m_moudleCfm->setAlignment(Qt::AlignCenter);
    m_fatalPOSC->setAlignment(Qt::AlignCenter);
    m_moudleNum->setAlignment(Qt::AlignCenter);

    m_basicStatus->setStyleSheet("background-color:lightgray");
    m_cyclePeriod->setStyleSheet("background-color:lightgray");
    m_forceChrgSt->setStyleSheet("background-color:lightgray");
    m_posiRlySt->setStyleSheet("background-color:lightgray");
    m_negRlySt->setStyleSheet("background-color:lightgray");
    m_rlySticky->setStyleSheet("background-color:lightgray");
    m_almSt->setStyleSheet("background-color:lightgray");
    m_moudleCfm->setStyleSheet("background-color:lightgray");
    m_fatalPOSC->setStyleSheet("background-color:lightgray");
    m_moudleNum->setStyleSheet("background-color:lightgray");

    m_cellStatusInfoLayout->addWidget(basicStatusLabel, 0, 0);
    m_cellStatusInfoLayout->addWidget(m_basicStatus, 0, 1);
    m_cellStatusInfoLayout->addWidget(cyclePeriodLabel, 0, 3);
    m_cellStatusInfoLayout->addWidget(m_cyclePeriod, 0, 4);

    m_cellStatusInfoLayout->addWidget(forceChrgStLabel, 1, 0);
    m_cellStatusInfoLayout->addWidget(m_forceChrgSt, 1, 1);

    m_cellStatusInfoLayout->addWidget(posiRlyStLabel, 2, 0);
    m_cellStatusInfoLayout->addWidget(m_posiRlySt, 2, 1);
    m_cellStatusInfoLayout->addWidget(negRlyStLabel, 2, 3);
    m_cellStatusInfoLayout->addWidget(m_negRlySt, 2, 4);

    m_cellStatusInfoLayout->addWidget(rlyStickyLabel, 3, 0);
    m_cellStatusInfoLayout->addWidget(m_rlySticky, 3, 1);
    m_cellStatusInfoLayout->addWidget(almStLabel, 3, 3);
    m_cellStatusInfoLayout->addWidget(m_almSt, 3, 4);

    m_cellStatusInfoLayout->addWidget(moudleCfmLabel, 4, 0);
    m_cellStatusInfoLayout->addWidget(m_moudleCfm, 4, 1);
    m_cellStatusInfoLayout->addWidget(moudleNumLabel, 4, 3);
    m_cellStatusInfoLayout->addWidget(m_moudleNum, 4, 4);

    m_cellStatusInfoLayout->addWidget(fatalPOSCLabel, 5, 0);
    m_cellStatusInfoLayout->addWidget(m_fatalPOSC, 5, 1);

    m_cellStatusInfoLayout->setColumnStretch(0, 2);
    m_cellStatusInfoLayout->setColumnStretch(1, 3);
    m_cellStatusInfoLayout->setColumnStretch(2, 1);
    m_cellStatusInfoLayout->setColumnStretch(3, 2);
    m_cellStatusInfoLayout->setColumnStretch(4, 3);

    m_cellStatusInfoGroup->setLayout(m_cellStatusInfoLayout);
}

void BMSInfoWidget::BuildCommandInfoUI()
{
    m_commandInfoLayout = new QGridLayout();

    QLabel *chrgForbidenMarkLabel = new QLabel("充电禁止标志：", this);
    QLabel *dischrgForbidenMarkLabel = new QLabel("放电禁止标志：", this);
    QLabel *sleepCtrlLabel = new QLabel("休眠控制：", this);
    QLabel *chrgEnLabel = new QLabel("充电使能：", this);
    QLabel *dischrgEnLabel = new QLabel("放电使能：", this);
    QLabel *relayForceBreakLabel = new QLabel("总体信息：", this);
    QLabel *note1 = new QLabel("0xAA:有效", this);
    QLabel *note2 = new QLabel("0xAA:有效", this);
    QLabel *note3 = new QLabel("0xAA:使能", this);
    QLabel *note4 = new QLabel("0xAA:使能", this);

    m_chrgForbidenMark = new QLineEdit(this);
    m_dischrgForbidenMark = new QLineEdit(this);
    m_sleepCtrl = new QLineEdit(this);
    m_chrgEn = new QLineEdit(this);
    m_dischrgEn = new QLineEdit(this);
    m_relayForceBreak = new QLineEdit(this);

    m_sleepCtrl->setEnabled(false);
    m_sleepCtrl->setAlignment(Qt::AlignCenter);
    m_relayForceBreak->setEnabled(false);
    m_relayForceBreak->setAlignment(Qt::AlignCenter);

    m_chrgForbidenMark->setAlignment(Qt::AlignCenter);
    m_chrgForbidenMark->setEnabled(false);
    m_dischrgForbidenMark->setAlignment(Qt::AlignCenter);
    m_dischrgForbidenMark->setEnabled(false);
    m_chrgEn->setAlignment(Qt::AlignCenter);
    m_chrgEn->setEnabled(false);
    m_dischrgEn->setAlignment(Qt::AlignCenter);
    m_dischrgEn->setEnabled(false);

    m_chrgForbidenMark->setStyleSheet("background-color:lightgray");
    m_dischrgForbidenMark->setStyleSheet("background-color:lightgray");
    m_chrgEn->setStyleSheet("background-color:lightgray");
    m_dischrgEn->setStyleSheet("background-color:lightgray");
    m_sleepCtrl->setStyleSheet("background-color:lightgray");
    m_relayForceBreak->setStyleSheet("background-color:lightgray");

//    m_sleepCtrl->addItem("休眠", 0);
//    m_sleepCtrl->addItem("唤醒", 1);

//    m_relayForceBreak->addItem("继电器强制断开", 0);
//    m_relayForceBreak->addItem("继电器允许闭合", 1);

    m_commandInfoLayout->addWidget(chrgForbidenMarkLabel, 0, 0);
    m_commandInfoLayout->addWidget(m_chrgForbidenMark, 0, 1);
    m_commandInfoLayout->addWidget(note1, 0, 2);
    m_commandInfoLayout->addWidget(dischrgForbidenMarkLabel, 0, 4);
    m_commandInfoLayout->addWidget(m_dischrgForbidenMark, 0, 5);
    m_commandInfoLayout->addWidget(note2, 0, 6);

    m_commandInfoLayout->addWidget(sleepCtrlLabel, 1, 0);
    m_commandInfoLayout->addWidget(m_sleepCtrl, 1, 1);
    m_commandInfoLayout->addWidget(relayForceBreakLabel, 1, 4);
    m_commandInfoLayout->addWidget(m_relayForceBreak, 1, 5);

    m_commandInfoLayout->addWidget(chrgEnLabel, 2, 0);
    m_commandInfoLayout->addWidget(m_chrgEn, 2, 1);
    m_commandInfoLayout->addWidget(note3, 2, 2);
    m_commandInfoLayout->addWidget(dischrgEnLabel, 2, 4);
    m_commandInfoLayout->addWidget(m_dischrgEn, 2, 5);
    m_commandInfoLayout->addWidget(note4, 2, 6);

    m_commandInfoLayout->setColumnStretch(0, 2);
    m_commandInfoLayout->setColumnStretch(1, 2);
    m_commandInfoLayout->setColumnStretch(2, 2);
    m_commandInfoLayout->setColumnStretch(3, 1);
    m_commandInfoLayout->setColumnStretch(4, 2);
    m_commandInfoLayout->setColumnStretch(5, 2);
    m_commandInfoLayout->setColumnStretch(6, 2);

    m_commandInfoGroup->setLayout(m_commandInfoLayout);
}


void BMSInfoWidget::cellFaultInfoUI()
{
     m_cellFaultInfoLayout = new QGridLayout();

    QLabel *fatalBMUSensorLabel = new QLabel("BMU AFE采样故障：", this);
    QLabel *fatalBMUAFELabel = new QLabel("BMU AFE Fault Pin：", this);
    QLabel *fatalBMUCVLabel = new QLabel("BMU电压采样故障：", this);
    QLabel *fatalBMUCTLabel = new QLabel("BMU温度采样故障：", this);
    QLabel *fatalHVCUComLabel = new QLabel("高压控制器通信故障：", this);
    QLabel *fatalHVCUSensorLabel = new QLabel("高压控制器采样故障：", this);
    QLabel *errVoltSensorLabel = new QLabel("电压传感器故障：", this);
    QLabel *errTempSensorLabel = new QLabel("温度传感器故障：", this);
    QLabel *errInnComLabel = new QLabel("内部通信故障：", this);
    QLabel *errChrgVoltHighLabel = new QLabel("充电电压高故障：", this);
    QLabel *errWireInversedLabel = new QLabel("动力线反接故障：", this);
    QLabel *errRelayStickyLabel = new QLabel("继电器粘滞故障：", this);

    m_fatalBMUSensor = new QLineEdit(this);
    m_fatalBMUAFE = new QLineEdit(this);
    m_fatalBMUCV = new QLineEdit(this);
    m_fatalBMUCT = new QLineEdit(this);
    m_fatalHVCUCom = new QLineEdit(this);
    m_fatalHVCUSensor = new QLineEdit(this);
    m_errVoltSensor = new QLineEdit(this);
    m_errTempSensor = new QLineEdit(this);
    m_errInnCom = new QLineEdit(this);
    m_errChrgVoltHigh = new QLineEdit(this);
    m_errWireInversed = new QLineEdit(this);
    m_errRelaySticky = new QLineEdit(this);

    m_fatalBMUSensor->setStyleSheet("background-color:lightgray");
    m_fatalBMUAFE->setStyleSheet("background-color:lightgray");
    m_fatalBMUCV->setStyleSheet("background-color:lightgray");
    m_fatalBMUCT->setStyleSheet("background-color:lightgray");
    m_fatalHVCUCom->setStyleSheet("background-color:lightgray");
    m_fatalHVCUSensor->setStyleSheet("background-color:lightgray");
    m_errVoltSensor->setStyleSheet("background-color:lightgray");
    m_errTempSensor->setStyleSheet("background-color:lightgray");
    m_errInnCom->setStyleSheet("background-color:lightgray");
    m_errChrgVoltHigh->setStyleSheet("background-color:lightgray");
    m_errWireInversed->setStyleSheet("background-color:lightgray");
    m_errRelaySticky->setStyleSheet("background-color:lightgray");

    m_fatalBMUSensor->setEnabled(false);
    m_fatalBMUAFE->setEnabled(false);
    m_fatalBMUCV->setEnabled(false);
    m_fatalBMUCT->setEnabled(false);
    m_fatalHVCUCom->setEnabled(false);
    m_fatalHVCUSensor->setEnabled(false);
    m_errVoltSensor->setEnabled(false);
    m_errTempSensor->setEnabled(false);
    m_errInnCom->setEnabled(false);
    m_errChrgVoltHigh->setEnabled(false);
    m_errWireInversed->setEnabled(false);
    m_errRelaySticky->setEnabled(false);

    m_cellFaultInfoLayout->addWidget(fatalBMUSensorLabel, 0, 0);
    m_cellFaultInfoLayout->addWidget(m_fatalBMUSensor, 0, 1);
    m_cellFaultInfoLayout->addWidget(fatalBMUAFELabel, 0, 3);
    m_cellFaultInfoLayout->addWidget(m_fatalBMUAFE, 0, 4);
    m_cellFaultInfoLayout->addWidget(fatalBMUCVLabel, 0, 6);
    m_cellFaultInfoLayout->addWidget(m_fatalBMUCV, 0, 7);
    m_cellFaultInfoLayout->addWidget(fatalBMUCTLabel, 0, 9);
    m_cellFaultInfoLayout->addWidget(m_fatalBMUCT, 0, 10);

    m_cellFaultInfoLayout->addWidget(fatalHVCUComLabel, 1, 0);
    m_cellFaultInfoLayout->addWidget(m_fatalHVCUCom, 1, 1);
    m_cellFaultInfoLayout->addWidget(fatalHVCUSensorLabel, 1, 3);
    m_cellFaultInfoLayout->addWidget(m_fatalHVCUSensor, 1, 4);
    m_cellFaultInfoLayout->addWidget(errVoltSensorLabel, 1, 6);
    m_cellFaultInfoLayout->addWidget(m_errVoltSensor, 1, 7);
    m_cellFaultInfoLayout->addWidget(errTempSensorLabel, 1, 9);
    m_cellFaultInfoLayout->addWidget(m_errTempSensor, 1, 10);

    m_cellFaultInfoLayout->addWidget(errInnComLabel, 2, 0);
    m_cellFaultInfoLayout->addWidget(m_errInnCom, 2, 1);
    m_cellFaultInfoLayout->addWidget(errChrgVoltHighLabel, 2, 3);
    m_cellFaultInfoLayout->addWidget(m_errChrgVoltHigh, 2, 4);
    m_cellFaultInfoLayout->addWidget(errWireInversedLabel, 2, 6);
    m_cellFaultInfoLayout->addWidget(m_errWireInversed, 2, 7);
    m_cellFaultInfoLayout->addWidget(errRelayStickyLabel, 2, 9);
    m_cellFaultInfoLayout->addWidget(m_errRelaySticky, 2, 10);

    m_fatalBMUSensor->setMaximumWidth(20);
    m_fatalBMUAFE->setMaximumWidth(20);
    m_fatalBMUCV->setMaximumWidth(20);
    m_fatalBMUCT->setMaximumWidth(20);
    m_fatalHVCUCom->setMaximumWidth(20);
    m_fatalHVCUSensor->setMaximumWidth(20);
    m_errVoltSensor->setMaximumWidth(20);
    m_errTempSensor->setMaximumWidth(20);
    m_errInnCom->setMaximumWidth(20);
    m_errChrgVoltHigh->setMaximumWidth(20);
    m_errWireInversed->setMaximumWidth(20);
    m_errRelaySticky->setMaximumWidth(20);

    m_cellFaultInfoLayout->setColumnStretch(0, 1.5);
    m_cellFaultInfoLayout->setColumnStretch(1, 1);
    m_cellFaultInfoLayout->setColumnStretch(2, 3);
    m_cellFaultInfoLayout->setColumnStretch(3, 1.5);
    m_cellFaultInfoLayout->setColumnStretch(4, 1);
    m_cellFaultInfoLayout->setColumnStretch(5, 3);
    m_cellFaultInfoLayout->setColumnStretch(6, 1.5);
    m_cellFaultInfoLayout->setColumnStretch(7, 1);
    m_cellFaultInfoLayout->setColumnStretch(8, 3);
    m_cellFaultInfoLayout->setColumnStretch(9, 1.5);
    m_cellFaultInfoLayout->setColumnStretch(10, 1);

    m_cellFaultInfoGroup->setLayout(m_cellFaultInfoLayout);
}


void BMSInfoWidget::CellAlarmInfoUI()
{
     m_cellAlarmInfoLayout = new QGridLayout();

     QLabel *almCellVoltLowLabel = new QLabel("单体电压低：", this);
     QLabel *almCellVoltHighLabel = new QLabel("单体电压高：", this);
     QLabel *almPackVoltLowLabel = new QLabel("总体电压低：", this);
     QLabel *almPackVoltHighLabel = new QLabel("总体电压高：", this);
     QLabel *almChrgTempLowLabel = new QLabel("充电温度低：", this);
     QLabel *almChrgTempHighLabel = new QLabel("充电温度高：", this);
     QLabel *almDischrgTempLowLabel = new QLabel("放电温度低：", this);
     QLabel *almDischrgTempHighLabel = new QLabel("放电温度高：", this);
     QLabel *almChrgCurrHighLabel = new QLabel("充电电流大：", this);
     QLabel *almDischrgCurrHighLabel = new QLabel("放电电流大：", this);
     QLabel *almMoudleVoltLowLabel = new QLabel("模组电压低：", this);
     QLabel *almMoudleVoltHighLabel = new QLabel("模组电压高：", this);

     m_almCellVoltLow = new QLineEdit(this);
     m_almCellVoltHigh = new QLineEdit(this);
     m_almPackVoltLow = new QLineEdit(this);
     m_almPackVoltHigh = new QLineEdit(this);
     m_almChrgTempLow = new QLineEdit(this);
     m_almChrgTempHigh = new QLineEdit(this);
     m_almDischrgTempLow = new QLineEdit(this);
     m_almDischrgTempHigh = new QLineEdit(this);
     m_almChrgCurrHigh = new QLineEdit(this);
     m_almDischrgCurrHigh = new QLineEdit(this);
     m_almMoudleVoltLow = new QLineEdit(this);
     m_almMoudleVoltHigh = new QLineEdit(this);

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

     m_almCellVoltLow->setMaximumWidth(20);
     m_almCellVoltHigh->setMaximumWidth(20);
     m_almPackVoltLow->setMaximumWidth(20);
     m_almPackVoltHigh->setMaximumWidth(20);
     m_almChrgTempLow->setMaximumWidth(20);
     m_almChrgTempHigh->setMaximumWidth(20);
     m_almDischrgTempLow->setMaximumWidth(20);
     m_almDischrgTempHigh->setMaximumWidth(20);
     m_almChrgCurrHigh->setMaximumWidth(20);
     m_almDischrgCurrHigh->setMaximumWidth(20);
     m_almMoudleVoltLow->setMaximumWidth(20);
     m_almMoudleVoltHigh->setMaximumWidth(20);

     m_cellAlarmInfoLayout->addWidget(almCellVoltLowLabel, 0, 0);
     m_cellAlarmInfoLayout->addWidget(m_almCellVoltLow, 0, 1);
     m_cellAlarmInfoLayout->addWidget(almCellVoltHighLabel, 0, 3);
     m_cellAlarmInfoLayout->addWidget(m_almCellVoltHigh, 0, 4);
     m_cellAlarmInfoLayout->addWidget(almPackVoltLowLabel, 0, 6);
     m_cellAlarmInfoLayout->addWidget(m_almPackVoltLow, 0, 7);
     m_cellAlarmInfoLayout->addWidget(almPackVoltHighLabel, 0, 9);
     m_cellAlarmInfoLayout->addWidget(m_almPackVoltHigh, 0, 10);

     m_cellAlarmInfoLayout->addWidget(almChrgTempLowLabel, 1, 0);
     m_cellAlarmInfoLayout->addWidget(m_almChrgTempLow, 1, 1);
     m_cellAlarmInfoLayout->addWidget(almChrgTempHighLabel, 1, 3);
     m_cellAlarmInfoLayout->addWidget(m_almChrgTempHigh, 1, 4);
     m_cellAlarmInfoLayout->addWidget(almDischrgTempLowLabel, 1, 6);
     m_cellAlarmInfoLayout->addWidget(m_almDischrgTempLow, 1, 7);
     m_cellAlarmInfoLayout->addWidget(almDischrgTempHighLabel, 1, 9);
     m_cellAlarmInfoLayout->addWidget(m_almDischrgTempHigh, 1, 10);

     m_cellAlarmInfoLayout->addWidget(almChrgCurrHighLabel, 2, 0);
     m_cellAlarmInfoLayout->addWidget(m_almChrgCurrHigh, 2, 1);
     m_cellAlarmInfoLayout->addWidget(almDischrgCurrHighLabel, 2, 3);
     m_cellAlarmInfoLayout->addWidget(m_almDischrgCurrHigh, 2, 4);
     m_cellAlarmInfoLayout->addWidget(almMoudleVoltLowLabel, 2, 6);
     m_cellAlarmInfoLayout->addWidget(m_almMoudleVoltLow, 2, 7);
     m_cellAlarmInfoLayout->addWidget(almMoudleVoltHighLabel, 2, 9);
     m_cellAlarmInfoLayout->addWidget(m_almMoudleVoltHigh, 2, 10);

     m_cellAlarmInfoLayout->setColumnStretch(0, 1.5);
     m_cellAlarmInfoLayout->setColumnStretch(1, 1);
     m_cellAlarmInfoLayout->setColumnStretch(2, 3);
     m_cellAlarmInfoLayout->setColumnStretch(3, 1.5);
     m_cellAlarmInfoLayout->setColumnStretch(4, 1);
     m_cellAlarmInfoLayout->setColumnStretch(5, 3);
     m_cellAlarmInfoLayout->setColumnStretch(6, 1.5);
     m_cellAlarmInfoLayout->setColumnStretch(7, 1);
     m_cellAlarmInfoLayout->setColumnStretch(8, 3);
     m_cellAlarmInfoLayout->setColumnStretch(9, 1.5);
     m_cellAlarmInfoLayout->setColumnStretch(10, 1);

     m_cellAlarmInfoGroup->setLayout(m_cellAlarmInfoLayout);
}


void BMSInfoWidget::CellProInfoUI()
{
     m_cellProInfoLayout = new QGridLayout();

     QLabel *pCellVoltLowLabel = new QLabel("单体电压低：", this);
     QLabel *pCellVoltHighLabel = new QLabel("单体电压高：", this);
     QLabel *pPackVoltLowLabel = new QLabel("总体电压低：", this);
     QLabel *pPackVoltHighLabel = new QLabel("总体电压高：", this);

     QLabel *pChrgTempLowLabel = new QLabel("充电温度低：", this);
     QLabel *pChrgTempHighLabel = new QLabel("充电温度高：", this);
     QLabel *pDischrgTempLowLabel = new QLabel("放电温度低：", this);
     QLabel *pDischrgTempHighLabel = new QLabel("放电温度高：", this);

     QLabel *pChrgCurrHighLabel = new QLabel("充电电流大：", this);
     QLabel *pDischrgCurrHighLabel = new QLabel("放电电流大：", this);
     QLabel *pMoudleVoltLowLabel = new QLabel("模组电压低：", this);
     QLabel *pMoudleVoltHighLabel = new QLabel("模组电压高：", this);

     m_pCellVoltLow = new QLineEdit(this);
     m_pCellVoltHigh = new QLineEdit(this);
     m_pPackVoltLow = new QLineEdit(this);
     m_pPackVoltHigh = new QLineEdit(this);
     m_pChrgTempLow = new QLineEdit(this);
     m_pChrgTempHigh = new QLineEdit(this);
     m_pDischrgTempLow = new QLineEdit(this);
     m_pDischrgTempHigh = new QLineEdit(this);
     m_pChrgCurrHigh = new QLineEdit(this);
     m_pDischrgCurrHigh = new QLineEdit(this);
     m_pMoudleVoltLow = new QLineEdit(this);
     m_pMoudleVoltHigh = new QLineEdit(this);

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

     m_pCellVoltLow->setStyleSheet("background-color:lightgray");   //灰色：超时
     m_pCellVoltHigh->setStyleSheet("background-color:lightgray");   //绿色：正常
     m_pPackVoltLow->setStyleSheet("background-color:lightgray");   //红色：告警
     m_pPackVoltHigh->setStyleSheet("background-color:lightgray");
     m_pChrgTempLow->setStyleSheet("background-color:lightgray");
     m_pChrgTempHigh->setStyleSheet("background-color:lightgray");
     m_pDischrgTempLow->setStyleSheet("background-color:lightgray");
     m_pDischrgTempHigh->setStyleSheet("background-color:lightgray");
     m_pChrgCurrHigh->setStyleSheet("background-color:lightgray");
     m_pDischrgCurrHigh->setStyleSheet("background-color:lightgray");
     m_pMoudleVoltLow->setStyleSheet("background-color:lightgray");
     m_pMoudleVoltHigh->setStyleSheet("background-color:lightgray");

     m_pCellVoltLow->setMaximumWidth(20);
     m_pCellVoltHigh->setMaximumWidth(20);
     m_pPackVoltLow->setMaximumWidth(20);
     m_pPackVoltHigh->setMaximumWidth(20);
     m_pChrgTempLow->setMaximumWidth(20);
     m_pChrgTempHigh->setMaximumWidth(20);
     m_pDischrgTempLow->setMaximumWidth(20);
     m_pDischrgTempHigh->setMaximumWidth(20);
     m_pChrgCurrHigh->setMaximumWidth(20);
     m_pDischrgCurrHigh->setMaximumWidth(20);
     m_pMoudleVoltLow->setMaximumWidth(20);
     m_pMoudleVoltHigh->setMaximumWidth(20);

     m_cellProInfoLayout->addWidget(pCellVoltLowLabel, 0, 0);
     m_cellProInfoLayout->addWidget(m_pCellVoltLow, 0, 1);
     m_cellProInfoLayout->addWidget(pCellVoltHighLabel, 0, 3);
     m_cellProInfoLayout->addWidget(m_pCellVoltHigh, 0, 4);
     m_cellProInfoLayout->addWidget(pPackVoltLowLabel, 0, 6);
     m_cellProInfoLayout->addWidget(m_pPackVoltLow, 0, 7);
     m_cellProInfoLayout->addWidget(pPackVoltHighLabel, 0, 9);
     m_cellProInfoLayout->addWidget(m_pPackVoltHigh, 0, 10);

     m_cellProInfoLayout->addWidget(pChrgTempLowLabel, 1, 0);
     m_cellProInfoLayout->addWidget(m_pChrgTempLow, 1, 1);
     m_cellProInfoLayout->addWidget(pChrgTempHighLabel, 1, 3);
     m_cellProInfoLayout->addWidget(m_pChrgTempHigh, 1, 4);
     m_cellProInfoLayout->addWidget(pDischrgTempLowLabel, 1, 6);
     m_cellProInfoLayout->addWidget(m_pDischrgTempLow, 1, 7);
     m_cellProInfoLayout->addWidget(pDischrgTempHighLabel, 1, 9);
     m_cellProInfoLayout->addWidget(m_pDischrgTempHigh, 1, 10);

     m_cellProInfoLayout->addWidget(pChrgCurrHighLabel, 2, 0);
     m_cellProInfoLayout->addWidget(m_pChrgCurrHigh, 2, 1);
     m_cellProInfoLayout->addWidget(pDischrgCurrHighLabel, 2, 3);
     m_cellProInfoLayout->addWidget(m_pDischrgCurrHigh, 2, 4);
     m_cellProInfoLayout->addWidget(pMoudleVoltLowLabel, 2, 6);
     m_cellProInfoLayout->addWidget(m_pMoudleVoltLow, 2, 7);
     m_cellProInfoLayout->addWidget(pMoudleVoltHighLabel, 2, 9);
     m_cellProInfoLayout->addWidget(m_pMoudleVoltHigh, 2, 10);

     m_cellProInfoLayout->setColumnStretch(0, 1.5);
     m_cellProInfoLayout->setColumnStretch(1, 1);
     m_cellProInfoLayout->setColumnStretch(2, 3);
     m_cellProInfoLayout->setColumnStretch(3, 1.5);
     m_cellProInfoLayout->setColumnStretch(4, 1);
     m_cellProInfoLayout->setColumnStretch(5, 3);
     m_cellProInfoLayout->setColumnStretch(6, 1.5);
     m_cellProInfoLayout->setColumnStretch(7, 1);
     m_cellProInfoLayout->setColumnStretch(8, 3);
     m_cellProInfoLayout->setColumnStretch(9, 1.5);
     m_cellProInfoLayout->setColumnStretch(10, 1);

     m_cellProInfoGroup->setLayout(m_cellProInfoLayout);
}




