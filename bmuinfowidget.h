#ifndef BMUINFOWIDGET_H
#define BMUINFOWIDGET_H
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QTimer>
#include "widgetdatastructure.h"
#include "mybutton.h"


class BMUInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BMUInfoWidget(QWidget *parent = 0);
    ~BMUInfoWidget();

    /** BMU **/
    QGridLayout *m_bmuInfoLayout;

    /** 编号按钮 **/
    void BuildSelectButUI();
    QGroupBox *m_selectButGroup;
    QGridLayout *m_selectButLayout;
    MyButton *BMUButton[MAX_BMU_NUMBER];

    /** 基本参数 **/
    void BuildBasicParUI();
    QGroupBox *m_basicParGroup;
    QGridLayout *m_basicParLayout;

    QLineEdit *m_soc;
    QLineEdit *m_soh;
    QLineEdit *m_battCycle;
    QLineEdit *m_diffCellVolt;
    QLineEdit *m_diffCellTemp;
    QLineEdit *m_moudleVolt;
    QLineEdit *m_boardTemp;
    QLineEdit *m_maxCellVolt;
    QLineEdit *m_minCellVolt;
    QLineEdit *m_avgCellVolt;
    QLineEdit *m_maxCVNO;
    QLineEdit *m_minCVNO;
    QLineEdit *m_maxCellTemp;
    QLineEdit *m_minCellTemp;
    QLineEdit *m_avgCellTemp;
    QLineEdit *m_maxCTNO;
    QLineEdit *m_minCTNO;

    /** 单芯电压 **/
    void BuildCellVoltInfoUI();
    QGroupBox *m_cellVoltInfoGroup;
    QGridLayout *m_cellVoltInfoLayout;
    QLineEdit *m_cellVolt[MAX_CELL_VOLT_NUMBER];

    /** 单芯温度 **/
    void BuildCellTempInfoUI();
    QGroupBox *m_cellTempInfoGroup;
    QGridLayout *m_cellTempInfoLayout;
    QLineEdit *m_cellTemp[MAX_CELL_TEMP_NUMBER];

    /** 版本信息 **/
    void BuildVersionInfoUI();
    QGroupBox *m_versionInfoGroup;
    QGridLayout *m_versionInfoLayout;

    QLineEdit *m_softwareVersion;
    QLineEdit *m_hardwareVersion;
    QLineEdit *m_updateDate;

    /** 均衡状态 **/
    void BuildBalInfoUI();
    QGroupBox *m_balInfoGroup;
    QGridLayout *m_balInfoLayout;
    QLineEdit *m_cellBalMode;
    QLineEdit *m_cellBalSt;
    QLineEdit *m_cellInBal[MAX_CELL_VOLT_NUMBER];
    void SetCellBalMode(UINT index);
    void SetCellBalSt(UINT index);

    /** BMU状态 **/
    void BuildBMUStatusUI();
    QGroupBox *m_bmuStatusGroup;
    QGridLayout *m_bmuStatusLayout;

    QLineEdit *m_afeSample;
    QLineEdit *m_afeFault;
    QLineEdit *m_owdSt;
    QLineEdit *m_msgAlive;

    QLineEdit *m_lv1CellVoltLow;
    QLineEdit *m_lv1CellVoltHigh;
    QLineEdit *m_lv1CellVoltDiff;
    QLineEdit *m_lv1MoudleVoltLow;
    QLineEdit *m_lv1MoudleVoltHigh;
    QLineEdit *m_lv1AmbientTempLow;
    QLineEdit *m_lv1AmbientTempHigh;
    QLineEdit *m_lv1ChrgTempLow;
    QLineEdit *m_lv1ChrgTempHigh;
    QLineEdit *m_lv1DischrgTempLow;
    QLineEdit *m_lv1DischrgTempHigh;

    QLineEdit *m_lv2CellVoltLow;
    QLineEdit *m_lv2CellVoltHigh;
    QLineEdit *m_lv2CellVoltDiff;
    QLineEdit *m_lv2MoudleVoltLow;
    QLineEdit *m_lv2MoudleVoltHigh;
    QLineEdit *m_lv2AmbientTempLow;
    QLineEdit *m_lv2AmbientTempHigh;
    QLineEdit *m_lv2ChrgTempLow;
    QLineEdit *m_lv2ChrgTempHigh;
    QLineEdit *m_lv2DischrgTempLow;
    QLineEdit *m_lv2DischrgTempHigh;

    void SetAFESample(UINT index);
    void SetAFEFault(UINT index);
    void SetOWDSt(UINT index);

    /** 模组配置 **/
    void BuildCellConfigUI();
    QGroupBox *m_cellConfigGroup;
    QGridLayout *m_cellConfigLayout;

    QLineEdit *m_cellAH;
    QLineEdit *m_cellRateVolt;
    QLineEdit *m_cellNum;
    QLineEdit *m_tempNum;

    QTimer *m_BMUWidgetTimer;
    QTimer *m_BMUSignalTimeout;

    void SetBMUWidget(UINT id);
    void SetBMUBasicPara(UINT id);
    void SetBMUBalance(UINT id);
    void SetBMUStatus(UINT id);
    void SetBMUValue(UINT index);
    void SetBMUTimeout(UINT index);

    void OnlineBMUBasicP1();
    void OfflineBMUBasicP1();
    void OnlineBMUBasicP2();
    void OfflineBMUBasicP2();
    void OnlineBMUBasicP3();
    void OfflineBMUBasicP3();
    void OnlineBMUBasicP4();
    void OfflineBMUBasicP4();
    void OnlineBMUConfig();
    void OfflineBMUConfig();
    void OnlineBMUVersion();
    void OfflineBMUVersion();
    void OnlineBMUCellVolt(int num);
    void OfflineBMUCellVolt(int num);
    void OnlineBMUCellTemp();
    void OfflineBMUCellTemp();
    void OnlineBMUBalStatus();
    void OfflineBMUBalStatus();
    void OnlineBMUStatus();
    void OfflineBMUStatus();

    void SetStatusValue(UINT index);
    void SetBasicP1Value(UINT index);
    void SetBasicP3Value(UINT index);
    void SetBasicP4Value(UINT index);
    void SetConfigValue(UINT index);

private slots:
    void ShowCurrentBMU(unsigned int index);
    void UpdateWidget();
    void SignalTimeout();

};

#endif // BMUINFOWIDGET_H
