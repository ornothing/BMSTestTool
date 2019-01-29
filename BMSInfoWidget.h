#ifndef REALTIMEINFO_H
#define REALTIMEINFO_H

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QTextEdit>
#include <QTimer>
#include "widgetdatastructure.h"

class BMSInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BMSInfoWidget(QWidget *parent = 0);
    ~BMSInfoWidget();

    /** BMS **/
    QGridLayout *m_bmsInfoLayout;

    /** 电池模组参数 **/
    void BuildCellModuleParameterUI();
    QGroupBox *m_cellModuleParGroup;
    QGridLayout *m_cellModuleLayout;
    QLineEdit *m_pollGlobalInfo;
    QLineEdit *m_packVolt;
    QLineEdit *m_packcurr;
    QLineEdit *m_ambientTempOut;
    QLineEdit *m_soc;
    QLineEdit *m_soh;
    QLineEdit *m_packPwr;
    QLineEdit *m_ambientTempIn;
    QLineEdit *m_chgCutoffVolt;
    QLineEdit *m_dischgCutoffVolt;
    QLineEdit *m_maxChgCurr;
    QLineEdit *m_maxDischgCurr;

    /** 电池基本参数 **/
    void BuildCellBasicParameterUI();
    QGroupBox *m_cellBasicParGroup;
    QGridLayout *m_cellBasicLayout;
    QLineEdit *m_maxCellVolt;
    QLineEdit *m_minCellVolt;
    QLineEdit *m_maxCVNo;
    QLineEdit *m_minCVNo;

    QLineEdit *m_maxCellTemp;
    QLineEdit *m_minCellTemp;
    QLineEdit *m_maxCTNo;
    QLineEdit *m_minCTNo;

    QLineEdit *m_maxMoudleCV;
    QLineEdit *m_minMoudleCV;
    QLineEdit *m_maxMCVNo;
    QLineEdit *m_minMCVNo;

    QLineEdit *m_maxMoudleCt;
    QLineEdit *m_minMoudleCt;
    QLineEdit *m_maxMCTNo;
    QLineEdit *m_minMCTNo;

    /** 电池配置信息 **/
    void BuildCellConfigInfoUI();
    QGroupBox *m_cellConfigInfoGroup;
    QGridLayout *m_cellConfigInfoLayout;
    QLineEdit *m_cellTotalNum;
    QLineEdit *m_moudleTotalNum;
    QLineEdit *m_cellNumInMoudle;
    QLineEdit *m_voltageLevel;
    QLineEdit *m_capAH;

    /** 电池状态信息 **/
    void BuildCellStatusInfoUI();
    QGroupBox *m_cellStatusInfoGroup;
    QGridLayout *m_cellStatusInfoLayout;
    QLineEdit *m_basicStatus;
    QLineEdit *m_cyclePeriod;
    QLineEdit *m_forceChrgSt;
    QLineEdit *m_posiRlySt;
    QLineEdit *m_negRlySt;
    QLineEdit *m_rlySticky;
    QLineEdit *m_almSt;
    QLineEdit *m_moudleCfm;
    QLineEdit *m_moudleNum;
    QLineEdit *m_fatalPOSC;
    void SetBasicStatus();
    void SetForceChrgSt();
    void SetPosiRlySt();
    void SetNegRlySt();
    void SetRlySticky();
    void SetAlmSt();
    void SetMoudleCfm();
    void SetFatalPOSC();

    /** 指令 **/
    void BuildCommandInfoUI();
    QGroupBox *m_commandInfoGroup;
    QGridLayout *m_commandInfoLayout;
    QLineEdit *m_chrgForbidenMark;
    QLineEdit *m_dischrgForbidenMark;
    QLineEdit *m_sleepCtrl;
    QLineEdit *m_chrgEn;
    QLineEdit *m_dischrgEn;
    QLineEdit *m_relayForceBreak;

    /** 电池故障信息 **/
    void cellFaultInfoUI();
    QGroupBox *m_cellFaultInfoGroup;
    QGridLayout *m_cellFaultInfoLayout;
    QLineEdit *m_fatalBMUSensor;
    QLineEdit *m_fatalBMUAFE;
    QLineEdit *m_fatalBMUCV;
    QLineEdit *m_fatalBMUCT;
    QLineEdit *m_fatalHVCUCom;
    QLineEdit *m_fatalHVCUSensor;

    QLineEdit *m_errVoltSensor;
    QLineEdit *m_errTempSensor;
    QLineEdit *m_errInnCom;
    QLineEdit *m_errChrgVoltHigh;
    QLineEdit *m_errWireInversed;
    QLineEdit *m_errRelaySticky;

    /** 电池告警信息 **/
    void CellAlarmInfoUI();
    QGroupBox *m_cellAlarmInfoGroup;
    QGridLayout *m_cellAlarmInfoLayout;
    QLineEdit *m_almCellVoltLow;
    QLineEdit *m_almCellVoltHigh;
    QLineEdit *m_almPackVoltLow;
    QLineEdit *m_almPackVoltHigh;
    QLineEdit *m_almChrgTempLow;
    QLineEdit *m_almChrgTempHigh;
    QLineEdit *m_almDischrgTempLow;
    QLineEdit *m_almDischrgTempHigh;
    QLineEdit *m_almChrgCurrHigh;
    QLineEdit *m_almDischrgCurrHigh;
    QLineEdit *m_almMoudleVoltLow;
    QLineEdit *m_almMoudleVoltHigh;

    /** 电池保护信息 **/
    void CellProInfoUI();
    QGroupBox *m_cellProInfoGroup;
    QGridLayout *m_cellProInfoLayout;

    QLineEdit *m_pCellVoltLow;
    QLineEdit *m_pCellVoltHigh;
    QLineEdit *m_pPackVoltLow;
    QLineEdit *m_pPackVoltHigh;

    QLineEdit *m_pChrgTempLow;
    QLineEdit *m_pChrgTempHigh;
    QLineEdit *m_pDischrgTempLow;
    QLineEdit *m_pDischrgTempHigh;

    QLineEdit *m_pChrgCurrHigh;
    QLineEdit *m_pDischrgCurrHigh;
    QLineEdit *m_pMoudleVoltLow;
    QLineEdit *m_pMoudleVoltHigh;

    QTimer *m_BMSWidgetTimer;
    QTimer *m_BMSSignalTimeout;

    void SetBMSWidget(UINT id);
    void SetBMSCellModelPara(UINT id);
    void SetBMSCellBasicPara(UINT id);
    void SetBMSCellConfig(UINT id);
    void SetBMSCommand(UINT id);
    void SetBMSFaultStatus(UINT id);
    void SetBMSCellStatus(UINT id);
    void SetBMSErrorStatus(UINT id);

    void OnlineModuleP();
    void OfflineModuleP();
    void OnlineModuleP1();
    void OfflineModuleP1();
    void OnlineModuleP2();
    void OfflineModuleP2();
    void OnlineModuleP3();
    void OfflineModuleP3();
    void OnlineBasicP1();
    void OfflineBasicP1();
    void OnlineBasicP2();
    void OfflineBasicP2();
    void OnlineBasicP3();
    void OfflineBasicP3();
    void OnlineBasicP4();
    void OfflineBasicP4();
    void OnlineConfig();
    void OfflineConfig();

private slots:
    void UpdateWidget();
    void SignalTimeout();
};



#endif // REALTIMEINFO_H
