#include "bmuinfowidget.h"
#include "widgetdatastructure.h"

BMUData g_BMUSavedData;


BMUInfoWidget::BMUInfoWidget(QWidget *parent)
    :QWidget(parent)
{
    int i = 0;
    qRegisterMetaType<unsigned int>("unsigned int");

    g_BMUSavedData.currentIndex = 0;

    m_bmuInfoLayout = new QGridLayout(this);
    m_selectButGroup = new QGroupBox(this);
    BuildSelectButUI();

    m_basicParGroup = new QGroupBox("BMU基本参数", this);
    BuildBasicParUI();

    m_cellVoltInfoGroup = new QGroupBox("BMU单芯电压", this);
    BuildCellVoltInfoUI();

    m_cellTempInfoGroup = new QGroupBox("BMU单芯温度", this);
    BuildCellTempInfoUI();

    m_versionInfoGroup = new QGroupBox("BMU版本信息", this);
    BuildVersionInfoUI();

    m_balInfoGroup = new QGroupBox("BMU均衡状态", this);
    BuildBalInfoUI();

    m_bmuStatusGroup = new QGroupBox("BMU状态", this);
    BuildBMUStatusUI();

    m_cellConfigGroup = new QGroupBox("BMU模组配置", this);
    BuildCellConfigUI();

    for (i=0; i<18; i++)
    {
        m_bmuInfoLayout->setRowStretch(i, 1);
    }

    m_bmuInfoLayout->addWidget(m_selectButGroup, 0, 0, 1, 1);
    m_bmuInfoLayout->addWidget(m_basicParGroup, 1, 0, 9, 1);
    m_bmuInfoLayout->addWidget(m_cellVoltInfoGroup, 10, 0, 8, 1);
    m_bmuInfoLayout->addWidget(m_versionInfoGroup, 0, 1, 1, 1);
    m_bmuInfoLayout->addWidget(m_balInfoGroup, 1, 1, 5, 1);
    m_bmuInfoLayout->addWidget(m_bmuStatusGroup, 6, 1, 8, 1);
    m_bmuInfoLayout->addWidget(m_cellConfigGroup, 14, 1, 2, 1);
    m_bmuInfoLayout->addWidget(m_cellTempInfoGroup, 16, 1, 2, 1);

    m_bmuInfoLayout->setColumnStretch(0, 2);
    m_bmuInfoLayout->setColumnStretch(1, 3);

    setLayout(m_bmuInfoLayout);

    m_BMUWidgetTimer = new QTimer(this);
    connect(m_BMUWidgetTimer, SIGNAL(timeout()), this, SLOT(UpdateWidget()));
    m_BMUWidgetTimer->start(100);

    m_BMUSignalTimeout = new QTimer(this);
    connect(m_BMUSignalTimeout, SIGNAL(timeout()), this, SLOT(SignalTimeout()));
    m_BMUSignalTimeout->start(10000);
}


BMUInfoWidget::~BMUInfoWidget()
{
    delete m_selectButLayout;
    delete m_basicParLayout;
    delete m_cellVoltInfoLayout;
    delete m_cellTempInfoLayout;
    delete m_versionInfoLayout;
    delete m_balInfoLayout;
    delete m_bmuStatusLayout;
    delete m_cellConfigLayout;
}


void BMUInfoWidget::BuildSelectButUI()
{
    int i = 0;
    m_selectButLayout = new QGridLayout();
    for (i=0; i<MAX_BMU_NUMBER; i++)
    {
        BMUButton[i] = new MyButton(tr("%1").arg(i+1), i, this);
        BMUButton[i]->setMinimumWidth(50);
        m_selectButLayout->addWidget(BMUButton[i], 0, i);
        connect(BMUButton[i], SIGNAL(clicked()), BMUButton[i], SLOT(ClickHandle()));
        connect(BMUButton[i], SIGNAL(myclick(unsigned int)), this, SLOT(ShowCurrentBMU(unsigned int)));
    }

    BMUButton[0]->setStyleSheet("background-color:#6495ED");   //菊蓝色

    m_selectButGroup->setLayout(m_selectButLayout);
}


void BMUInfoWidget::BuildBasicParUI()
{
    m_basicParLayout = new QGridLayout();

    QLabel *socLabel = new QLabel("单板SOC：", this);
    QLabel *sohLabel = new QLabel("单板SOH：", this);
    QLabel *battCycleLabel = new QLabel("电池循环次数：", this);
    QLabel *diffCellVoltLabel = new QLabel("单芯电压差：", this);
    QLabel *diffCellTempLabel = new QLabel("单芯温度差：", this);
    QLabel *moudleVoltLabel = new QLabel("模组电压：", this);
    QLabel *boardTempLabel = new QLabel("板载温度：", this);

    QLabel *maxCellVoltLabel = new QLabel("最高单芯电压：", this);
    QLabel *minCellVoltLabel = new QLabel("最低单芯电压：", this);
    QLabel *avgCellVoltLabel = new QLabel("平均单芯电压：", this);
    QLabel *maxCVNOLabel = new QLabel("最高单芯电压编号：", this);
    QLabel *minCVNOLabel = new QLabel("最低单芯电压编号：", this);

    QLabel *maxCellTempLabel = new QLabel("最高单芯温度：", this);
    QLabel *minCellTempLabel = new QLabel("最低单芯温度：", this);
    QLabel *avgCellTempLabel = new QLabel("平均单芯温度：", this);
    QLabel *maxCTNOLabel = new QLabel("最高单芯温度编号：", this);
    QLabel *minCTNOLabel = new QLabel("最低单芯温度编号：", this);

    QLabel *socUnit = new QLabel("%", this);
    QLabel *sohUnit = new QLabel("%", this);
    QLabel *diffCellVoltUnit = new QLabel("mV", this);
    QLabel *diffCellTempUnit = new QLabel("℃", this);
    QLabel *moudleVoltUnit = new QLabel("V", this);
    QLabel *boardTempUnit = new QLabel("℃", this);

    QLabel *maxCellVoltUnit = new QLabel("mV", this);
    QLabel *minCellVoltUnit = new QLabel("mV", this);
    QLabel *avgCellVoltUnit = new QLabel("mV", this);

    QLabel *maxCellTempUnit = new QLabel("℃", this);
    QLabel *minCellTempUnit = new QLabel("℃", this);
    QLabel *avgCellTempUnit = new QLabel("℃", this);

    m_soc = new QLineEdit(this);
    m_soh = new QLineEdit(this);
    m_battCycle = new QLineEdit(this);
    m_diffCellVolt = new QLineEdit(this);
    m_diffCellTemp = new QLineEdit(this);
    m_moudleVolt = new QLineEdit(this);
    m_boardTemp = new QLineEdit(this);

    m_maxCellVolt = new QLineEdit(this);
    m_minCellVolt = new QLineEdit(this);
    m_avgCellVolt = new QLineEdit(this);
    m_maxCVNO = new QLineEdit(this);
    m_minCVNO = new QLineEdit(this);

    m_maxCellTemp = new QLineEdit(this);
    m_minCellTemp = new QLineEdit(this);
    m_avgCellTemp = new QLineEdit(this);
    m_maxCTNO = new QLineEdit(this);
    m_minCTNO = new QLineEdit(this);

    OfflineBMUBasicP1();
    OfflineBMUBasicP2();
    OfflineBMUBasicP3();
    OfflineBMUBasicP4();

    m_basicParLayout->addWidget(socLabel, 0, 0);
    m_basicParLayout->addWidget(m_soc, 0, 1);
    m_basicParLayout->addWidget(socUnit, 0, 2);
    m_basicParLayout->addWidget(sohLabel, 0, 4);
    m_basicParLayout->addWidget(m_soh, 0, 5);
    m_basicParLayout->addWidget(sohUnit, 0, 6);

    m_basicParLayout->addWidget(diffCellVoltLabel, 1, 0);
    m_basicParLayout->addWidget(m_diffCellVolt, 1, 1);
    m_basicParLayout->addWidget(diffCellVoltUnit, 1, 2);
    m_basicParLayout->addWidget(diffCellTempLabel, 1, 4);
    m_basicParLayout->addWidget(m_diffCellTemp, 1, 5);
    m_basicParLayout->addWidget(diffCellTempUnit, 1, 6);

    m_basicParLayout->addWidget(moudleVoltLabel, 2, 0);
    m_basicParLayout->addWidget(m_moudleVolt, 2, 1);
    m_basicParLayout->addWidget(moudleVoltUnit, 2, 2);
    m_basicParLayout->addWidget(boardTempLabel, 2, 4);
    m_basicParLayout->addWidget(m_boardTemp, 2, 5);
    m_basicParLayout->addWidget(boardTempUnit, 2, 6);

    m_basicParLayout->addWidget(maxCellVoltLabel, 3, 0);
    m_basicParLayout->addWidget(m_maxCellVolt, 3, 1);
    m_basicParLayout->addWidget(maxCellVoltUnit, 3, 2);
    m_basicParLayout->addWidget(maxCVNOLabel, 3, 4);
    m_basicParLayout->addWidget(m_maxCVNO, 3, 5);

    m_basicParLayout->addWidget(minCellVoltLabel, 4, 0);
    m_basicParLayout->addWidget(m_minCellVolt, 4, 1);
    m_basicParLayout->addWidget(minCellVoltUnit, 4, 2);
    m_basicParLayout->addWidget(minCVNOLabel, 4, 4);
    m_basicParLayout->addWidget(m_minCVNO, 4, 5);

    m_basicParLayout->addWidget(maxCellTempLabel, 5, 0);
    m_basicParLayout->addWidget(m_maxCellTemp, 5, 1);
    m_basicParLayout->addWidget(maxCellTempUnit, 5, 2);
    m_basicParLayout->addWidget(maxCTNOLabel, 5, 4);
    m_basicParLayout->addWidget(m_maxCTNO, 5, 5);

    m_basicParLayout->addWidget(minCellTempLabel, 6, 0);
    m_basicParLayout->addWidget(m_minCellTemp, 6, 1);
    m_basicParLayout->addWidget(minCellTempUnit, 6, 2);
    m_basicParLayout->addWidget(minCTNOLabel, 6, 4);
    m_basicParLayout->addWidget(m_minCTNO, 6, 5);

    m_basicParLayout->addWidget(avgCellVoltLabel, 7, 0);
    m_basicParLayout->addWidget(m_avgCellVolt, 7, 1);
    m_basicParLayout->addWidget(avgCellVoltUnit, 7, 2);
    m_basicParLayout->addWidget(avgCellTempLabel, 7, 4);
    m_basicParLayout->addWidget(m_avgCellTemp, 7, 5);
    m_basicParLayout->addWidget(avgCellTempUnit, 7, 6);

    m_basicParLayout->addWidget(battCycleLabel, 8, 0);
    m_basicParLayout->addWidget(m_battCycle, 8, 1);

    m_soc->setAlignment(Qt::AlignCenter);
    m_soh->setAlignment(Qt::AlignCenter);
    m_battCycle->setAlignment(Qt::AlignCenter);
    m_diffCellVolt->setAlignment(Qt::AlignCenter);
    m_diffCellTemp->setAlignment(Qt::AlignCenter);
    m_moudleVolt->setAlignment(Qt::AlignCenter);
    m_boardTemp->setAlignment(Qt::AlignCenter);

    m_maxCellVolt->setAlignment(Qt::AlignCenter);
    m_minCellVolt->setAlignment(Qt::AlignCenter);
    m_avgCellVolt->setAlignment(Qt::AlignCenter);
    m_maxCVNO->setAlignment(Qt::AlignCenter);
    m_minCVNO->setAlignment(Qt::AlignCenter);

    m_maxCellTemp->setAlignment(Qt::AlignCenter);
    m_minCellTemp->setAlignment(Qt::AlignCenter);
    m_avgCellTemp->setAlignment(Qt::AlignCenter);
    m_maxCTNO->setAlignment(Qt::AlignCenter);
    m_minCTNO->setAlignment(Qt::AlignCenter);

    m_basicParLayout->setColumnStretch(0, 2);
    m_basicParLayout->setColumnStretch(1, 3);
    m_basicParLayout->setColumnStretch(2, 0.5);
    m_basicParLayout->setColumnStretch(3, 2);
    m_basicParLayout->setColumnStretch(4, 2);
    m_basicParLayout->setColumnStretch(5, 3);
    m_basicParLayout->setColumnStretch(6, 0.5);

    m_basicParGroup->setLayout(m_basicParLayout);
}


void BMUInfoWidget::BuildCellVoltInfoUI()
{
    m_cellVoltInfoLayout = new QGridLayout();
    QLabel *cellVoltLabel[MAX_CELL_VOLT_NUMBER];
    QLabel *cellVoltUnit[MAX_CELL_VOLT_NUMBER];

    int i = 0;

    for (i=0; i<MAX_CELL_VOLT_NUMBER; i++)
    {
        m_cellVolt[i] = new QLineEdit(this);
        cellVoltLabel[i] = new QLabel(QString("单芯电压%1：").arg(i+1), this);
        cellVoltUnit[i] = new QLabel(QString("mV"), this);
        m_cellVolt[i]->setAlignment(Qt::AlignCenter);
        m_cellVolt[i]->setEnabled(false);
        m_cellVolt[i]->setStyleSheet("background-color:lightgray");
    }

    m_cellVoltInfoLayout->addWidget(cellVoltLabel[0], 0, 0);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[0], 0, 1);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[0], 0, 2);
    m_cellVoltInfoLayout->addWidget(cellVoltLabel[1], 1, 0);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[1], 1, 1);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[1], 1, 2);
    m_cellVoltInfoLayout->addWidget(cellVoltLabel[2], 2, 0);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[2], 2, 1);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[2], 2, 2);
    m_cellVoltInfoLayout->addWidget(cellVoltLabel[3], 3, 0);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[3], 3, 1);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[3], 3, 2);
    m_cellVoltInfoLayout->addWidget(cellVoltLabel[4], 4, 0);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[4], 4, 1);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[4], 4, 2);
    m_cellVoltInfoLayout->addWidget(cellVoltLabel[5], 5, 0);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[5], 5, 1);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[5], 5, 2);
    m_cellVoltInfoLayout->addWidget(cellVoltLabel[6], 6, 0);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[6], 6, 1);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[6], 6, 2);
    m_cellVoltInfoLayout->addWidget(cellVoltLabel[7], 7, 0);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[7], 7, 1);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[7], 7, 2);

    m_cellVoltInfoLayout->addWidget(cellVoltLabel[8], 0, 4);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[8], 0, 5);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[8], 0, 6);
    m_cellVoltInfoLayout->addWidget(cellVoltLabel[9], 1, 4);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[9], 1, 5);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[9], 1, 6);
    m_cellVoltInfoLayout->addWidget(cellVoltLabel[10], 2, 4);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[10], 2, 5);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[10], 2, 6);
    m_cellVoltInfoLayout->addWidget(cellVoltLabel[11], 3, 4);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[11], 3, 5);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[11], 3, 6);
    m_cellVoltInfoLayout->addWidget(cellVoltLabel[12], 4, 4);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[12], 4, 5);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[12], 4, 6);
    m_cellVoltInfoLayout->addWidget(cellVoltLabel[13], 5, 4);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[13], 5, 5);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[13], 5, 6);
    m_cellVoltInfoLayout->addWidget(cellVoltLabel[14], 6, 4);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[14], 6, 5);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[14], 6, 6);
    m_cellVoltInfoLayout->addWidget(cellVoltLabel[15], 7, 4);
    m_cellVoltInfoLayout->addWidget(m_cellVolt[15], 7, 5);
    m_cellVoltInfoLayout->addWidget(cellVoltUnit[15], 7, 6);

    m_cellVoltInfoLayout->setColumnStretch(0, 2);
    m_cellVoltInfoLayout->setColumnStretch(1, 3);
    m_cellVoltInfoLayout->setColumnStretch(2, 0.5);
    m_cellVoltInfoLayout->setColumnStretch(3, 2);
    m_cellVoltInfoLayout->setColumnStretch(4, 2);
    m_cellVoltInfoLayout->setColumnStretch(5, 3);
    m_cellVoltInfoLayout->setColumnStretch(6, 0.5);

    m_cellVoltInfoGroup->setLayout(m_cellVoltInfoLayout);
}


void BMUInfoWidget::BuildCellTempInfoUI()
{
    m_cellTempInfoLayout = new QGridLayout();
    QLabel *cellTempLabel[MAX_CELL_TEMP_NUMBER];
    QLabel *cellTempUnit[MAX_CELL_TEMP_NUMBER];

    int i = 0;

    for (i=0; i<MAX_CELL_TEMP_NUMBER; i++)
    {
        m_cellTemp[i] = new QLineEdit(this);
        cellTempLabel[i] = new QLabel(QString("单芯温度%1：").arg(i+1), this);
        cellTempUnit[i] = new QLabel(QString("℃"), this);
        m_cellTemp[i]->setAlignment(Qt::AlignCenter);
        m_cellTemp[i]->setStyleSheet("background-color:lightgray");
        m_cellTemp[i]->setEnabled(false);
    }

    m_cellTempInfoLayout->addWidget(cellTempLabel[0], 0, 0);
    m_cellTempInfoLayout->addWidget(m_cellTemp[0], 0, 1);
    m_cellTempInfoLayout->addWidget(cellTempUnit[0], 0, 2);
    m_cellTempInfoLayout->addWidget(cellTempLabel[1], 1, 0);
    m_cellTempInfoLayout->addWidget(m_cellTemp[1], 1, 1);
    m_cellTempInfoLayout->addWidget(cellTempUnit[1], 1, 2);

    m_cellTempInfoLayout->addWidget(cellTempLabel[2], 0, 4);
    m_cellTempInfoLayout->addWidget(m_cellTemp[2], 0, 5);
    m_cellTempInfoLayout->addWidget(cellTempUnit[2], 0, 6);
    m_cellTempInfoLayout->addWidget(cellTempLabel[3], 1, 4);
    m_cellTempInfoLayout->addWidget(m_cellTemp[3], 1, 5);
    m_cellTempInfoLayout->addWidget(cellTempUnit[3], 1, 6);

    m_cellTempInfoLayout->setColumnStretch(0, 2);
    m_cellTempInfoLayout->setColumnStretch(1, 3);
    m_cellTempInfoLayout->setColumnStretch(2, 1);
    m_cellTempInfoLayout->setColumnStretch(3, 1);
    m_cellTempInfoLayout->setColumnStretch(4, 2);
    m_cellTempInfoLayout->setColumnStretch(5, 3);
    m_cellTempInfoLayout->setColumnStretch(6, 1);

    m_cellTempInfoGroup->setLayout(m_cellTempInfoLayout);
}


void BMUInfoWidget::BuildVersionInfoUI()
{
    m_versionInfoLayout = new QGridLayout();
    QLabel *softVersionLabel = new QLabel("软件版本：", this);
    QLabel *hardVersionLabel = new QLabel("硬件版本：", this);
    QLabel *updateDateLabel = new QLabel("更新日期：", this);

    m_softwareVersion = new QLineEdit(this);
    m_hardwareVersion = new QLineEdit(this);
    m_updateDate = new QLineEdit(this);

    m_softwareVersion->setAlignment(Qt::AlignCenter);
    m_hardwareVersion->setAlignment(Qt::AlignCenter);
    m_updateDate->setAlignment(Qt::AlignCenter);

    OfflineBMUVersion();

    m_versionInfoLayout->addWidget(softVersionLabel, 0, 0);
    m_versionInfoLayout->addWidget(m_softwareVersion, 0, 1);
    m_versionInfoLayout->addWidget(hardVersionLabel, 0, 3);
    m_versionInfoLayout->addWidget(m_hardwareVersion, 0, 4);
    m_versionInfoLayout->addWidget(updateDateLabel, 0, 6);
    m_versionInfoLayout->addWidget(m_updateDate, 0, 7);

    m_versionInfoLayout->setColumnStretch(0, 1);
    m_versionInfoLayout->setColumnStretch(1, 3.5);
    m_versionInfoLayout->setColumnStretch(2, 1);
    m_versionInfoLayout->setColumnStretch(3, 1);
    m_versionInfoLayout->setColumnStretch(4, 3.5);
    m_versionInfoLayout->setColumnStretch(5, 1);
    m_versionInfoLayout->setColumnStretch(6, 1);
    m_versionInfoLayout->setColumnStretch(7, 3.5);

    m_versionInfoGroup->setLayout(m_versionInfoLayout);
}

void BMUInfoWidget::BuildBalInfoUI()
{
    int i = 0;
    QLabel *cellInBalLabel[MAX_CELL_VOLT_NUMBER];
    m_balInfoLayout = new QGridLayout();
    QLabel *cellBalModeLabel = new QLabel("均衡模式：", this);
    QLabel *cellBalStLabel = new QLabel("均衡状态：", this);

    m_cellBalMode = new QLineEdit(this);
    m_cellBalSt = new QLineEdit(this);

    m_cellBalMode->setMaximumWidth(120);
    m_cellBalSt->setMaximumWidth(120);

    m_cellBalMode->setEnabled(false);
    m_cellBalSt->setEnabled(false);
    m_cellBalMode->setStyleSheet("background-color:lightgray");
    m_cellBalSt->setStyleSheet("background-color:lightgray");

    for (i=0; i<MAX_CELL_VOLT_NUMBER; i++)
    {
        cellInBalLabel[i] = new QLabel(QString("均衡电芯%1：").arg(i+1), this);
        m_cellInBal[i] = new QLineEdit(this);
        m_cellInBal[i]->setStyleSheet("background-color:lightgray");
        m_cellInBal[i]->setEnabled(false);
        m_cellInBal[i]->setMaximumWidth(20);
    }

    m_balInfoLayout->addWidget(cellBalModeLabel, 0 ,0);
    m_balInfoLayout->addWidget(m_cellBalMode, 0 ,1, 1, 2);
    m_balInfoLayout->addWidget(cellBalStLabel, 0 ,6);
    m_balInfoLayout->addWidget(m_cellBalSt, 0 ,7, 1, 2);

    m_balInfoLayout->addWidget(cellInBalLabel[0], 1, 0);
    m_balInfoLayout->addWidget(m_cellInBal[0], 1, 1);
    m_balInfoLayout->addWidget(cellInBalLabel[1], 1, 3);
    m_balInfoLayout->addWidget(m_cellInBal[1], 1, 4);
    m_balInfoLayout->addWidget(cellInBalLabel[2], 1, 6);
    m_balInfoLayout->addWidget(m_cellInBal[2], 1, 7);
    m_balInfoLayout->addWidget(cellInBalLabel[3], 1, 9);
    m_balInfoLayout->addWidget(m_cellInBal[3], 1, 10);

    m_balInfoLayout->addWidget(cellInBalLabel[4], 2, 0);
    m_balInfoLayout->addWidget(m_cellInBal[4], 2, 1);
    m_balInfoLayout->addWidget(cellInBalLabel[5], 2, 3);
    m_balInfoLayout->addWidget(m_cellInBal[5], 2, 4);
    m_balInfoLayout->addWidget(cellInBalLabel[6], 2, 6);
    m_balInfoLayout->addWidget(m_cellInBal[6], 2, 7);
    m_balInfoLayout->addWidget(cellInBalLabel[7], 2, 9);
    m_balInfoLayout->addWidget(m_cellInBal[7], 2, 10);

    m_balInfoLayout->addWidget(cellInBalLabel[8], 3, 0);
    m_balInfoLayout->addWidget(m_cellInBal[8], 3, 1);
    m_balInfoLayout->addWidget(cellInBalLabel[9], 3, 3);
    m_balInfoLayout->addWidget(m_cellInBal[9], 3, 4);
    m_balInfoLayout->addWidget(cellInBalLabel[10], 3, 6);
    m_balInfoLayout->addWidget(m_cellInBal[10], 3, 7);
    m_balInfoLayout->addWidget(cellInBalLabel[11], 3, 9);
    m_balInfoLayout->addWidget(m_cellInBal[11], 3, 10);

    m_balInfoLayout->addWidget(cellInBalLabel[12], 4, 0);
    m_balInfoLayout->addWidget(m_cellInBal[12], 4, 1);
    m_balInfoLayout->addWidget(cellInBalLabel[13], 4, 3);
    m_balInfoLayout->addWidget(m_cellInBal[13], 4, 4);
    m_balInfoLayout->addWidget(cellInBalLabel[14], 4, 6);
    m_balInfoLayout->addWidget(m_cellInBal[14], 4, 7);
    m_balInfoLayout->addWidget(cellInBalLabel[15], 4, 9);
    m_balInfoLayout->addWidget(m_cellInBal[15], 4, 10);

    m_balInfoLayout->setColumnStretch(0, 1.5);
    m_balInfoLayout->setColumnStretch(1, 1);
    m_balInfoLayout->setColumnStretch(2, 3);
    m_balInfoLayout->setColumnStretch(3, 1.5);
    m_balInfoLayout->setColumnStretch(4, 1);
    m_balInfoLayout->setColumnStretch(5, 3);
    m_balInfoLayout->setColumnStretch(6, 1.5);
    m_balInfoLayout->setColumnStretch(7, 1);
    m_balInfoLayout->setColumnStretch(8, 3);
    m_balInfoLayout->setColumnStretch(9, 1.5);
    m_balInfoLayout->setColumnStretch(10, 1);

    m_balInfoGroup->setLayout(m_balInfoLayout);
}


void BMUInfoWidget::BuildBMUStatusUI()
{
     m_bmuStatusLayout = new QGridLayout();

     QLabel *afeSampleLabel = new QLabel("AFE采样状态：", this);
     QLabel *afeFaultLabel = new QLabel("AFE故障状态：", this);
     QLabel *owdStLabel = new QLabel("断线检测状态：", this);
     QLabel *msgAliveLabel = new QLabel("消息计数：", this);

     QLabel *lv1CellVoltLowLabel = new QLabel("单芯电压低一级：", this);
     QLabel *lv1CellVoltHighLabel = new QLabel("单芯电压高一级：", this);
     QLabel *lv1CellVoltDiffLabel = new QLabel("单芯电压差一级：", this);
     QLabel *lv1MoudleVoltLowLabel = new QLabel("模组电压低一级：", this);
     QLabel *lv1MoudleVoltHighLabel = new QLabel("模组电压高一级：", this);
     QLabel *lv1AmbientTempLowLabel = new QLabel("环境温度低一级：", this);
     QLabel *lv1AmbientTempHighLabel = new QLabel("环境温度高一级：", this);

     QLabel *lv1ChrgTempLowLabel = new QLabel("充电温度低一级：", this);
     QLabel *lv1ChrgTempHighLabel = new QLabel("充电温度高一级：", this);
     QLabel *lv1DischrgTempLowLabel = new QLabel("放电温度低一级：", this);
     QLabel *lv1DischrgTempHighLabel = new QLabel("放电温度高一级：", this);

     QLabel *lv2CellVoltLowLabel = new QLabel("单芯电压低二级：", this);
     QLabel *lv2CellVoltHighLabel = new QLabel("单芯电压高二级：", this);
     QLabel *lv2CellVoltDiffLabel = new QLabel("单芯电压差二级：", this);
     QLabel *lv2MoudleVoltLowLabel = new QLabel("模组电压低二级：", this);
     QLabel *lv2MoudleVoltHighLabel = new QLabel("模组电压高二级：", this);
     QLabel *lv2AmbientTempLowLabel = new QLabel("环境温度低二级：", this);
     QLabel *lv2AmbientTempHighLabel = new QLabel("环境温度高二级：", this);

     QLabel *lv2ChrgTempLowLabel = new QLabel("充电温度低二级：", this);
     QLabel *lv2ChrgTempHighLabel = new QLabel("充电温度高二级：", this);
     QLabel *lv2DischrgTempLowLabel = new QLabel("放电温度低二级：", this);
     QLabel *lv2DischrgTempHighLabel = new QLabel("放电温度高二级：", this);

     m_afeSample = new QLineEdit(this);
     m_afeFault = new QLineEdit(this);
     m_owdSt = new QLineEdit(this);
     m_msgAlive = new QLineEdit(this);

     m_afeSample->setMaximumWidth(150);
     m_afeFault->setMaximumWidth(150);
     m_owdSt->setMaximumWidth(150);
     m_msgAlive->setMaximumWidth(150);

//     m_afeSample->addItem("正常", 0);
//     m_afeSample->addItem("故障", 1);

//     m_afeFault->addItem("正常", 0);
//     m_afeFault->addItem("故障", 1);

//     m_owdSt->addItem("检测中", 0);
//     m_owdSt->addItem("正常", 1);
//     m_owdSt->addItem("断线", 2);

     m_lv1CellVoltLow = new QLineEdit(this);
     m_lv1CellVoltHigh = new QLineEdit(this);
     m_lv1CellVoltDiff = new QLineEdit(this);
     m_lv1MoudleVoltLow = new QLineEdit(this);
     m_lv1MoudleVoltHigh = new QLineEdit(this);
     m_lv1AmbientTempLow = new QLineEdit(this);
     m_lv1AmbientTempHigh = new QLineEdit(this);

     m_lv1ChrgTempLow = new QLineEdit(this);
     m_lv1ChrgTempHigh = new QLineEdit(this);
     m_lv1DischrgTempLow = new QLineEdit(this);
     m_lv1DischrgTempHigh = new QLineEdit(this);

     m_lv2CellVoltLow = new QLineEdit(this);
     m_lv2CellVoltHigh = new QLineEdit(this);
     m_lv2CellVoltDiff = new QLineEdit(this);
     m_lv2MoudleVoltLow = new QLineEdit(this);
     m_lv2MoudleVoltHigh = new QLineEdit(this);
     m_lv2AmbientTempLow = new QLineEdit(this);
     m_lv2AmbientTempHigh = new QLineEdit(this);

     m_lv2ChrgTempLow = new QLineEdit(this);
     m_lv2ChrgTempHigh = new QLineEdit(this);
     m_lv2DischrgTempLow = new QLineEdit(this);
     m_lv2DischrgTempHigh = new QLineEdit(this);

     OfflineBMUStatus();

     m_lv1CellVoltLow->setMaximumWidth(20);
     m_lv1CellVoltHigh->setMaximumWidth(20);
     m_lv1CellVoltDiff->setMaximumWidth(20);
     m_lv1MoudleVoltLow->setMaximumWidth(20);
     m_lv1MoudleVoltHigh->setMaximumWidth(20);
     m_lv1AmbientTempLow->setMaximumWidth(20);
     m_lv1AmbientTempHigh->setMaximumWidth(20);

     m_lv1ChrgTempLow->setMaximumWidth(20);
     m_lv1ChrgTempHigh->setMaximumWidth(20);
     m_lv1DischrgTempLow->setMaximumWidth(20);
     m_lv1DischrgTempHigh->setMaximumWidth(20);

     m_lv2CellVoltLow->setMaximumWidth(20);
     m_lv2CellVoltHigh->setMaximumWidth(20);
     m_lv2CellVoltDiff->setMaximumWidth(20);
     m_lv2MoudleVoltLow->setMaximumWidth(20);
     m_lv2MoudleVoltHigh->setMaximumWidth(20);
     m_lv2AmbientTempLow->setMaximumWidth(20);
     m_lv2AmbientTempHigh->setMaximumWidth(20);

     m_lv2ChrgTempLow->setMaximumWidth(20);
     m_lv2ChrgTempHigh->setMaximumWidth(20);
     m_lv2DischrgTempLow->setMaximumWidth(20);
     m_lv2DischrgTempHigh->setMaximumWidth(20);

     m_bmuStatusLayout->addWidget(afeSampleLabel, 0 ,0);
     m_bmuStatusLayout->addWidget(m_afeSample, 0 ,1, 1, 2);
     m_bmuStatusLayout->addWidget(afeFaultLabel, 0 ,6);
     m_bmuStatusLayout->addWidget(m_afeFault, 0 ,7, 1, 2);
     m_bmuStatusLayout->addWidget(owdStLabel, 1 ,0);
     m_bmuStatusLayout->addWidget(m_owdSt, 1 ,1, 1, 2);
     m_bmuStatusLayout->addWidget(msgAliveLabel, 1 ,6);
     m_bmuStatusLayout->addWidget(m_msgAlive, 1 ,7, 1, 2);

     m_bmuStatusLayout->addWidget(lv1CellVoltLowLabel, 2, 0);
     m_bmuStatusLayout->addWidget(m_lv1CellVoltLow, 2, 1);
     m_bmuStatusLayout->addWidget(lv1CellVoltHighLabel, 2, 3);
     m_bmuStatusLayout->addWidget(m_lv1CellVoltHigh, 2, 4);
     m_bmuStatusLayout->addWidget(lv1CellVoltDiffLabel, 2, 6);
     m_bmuStatusLayout->addWidget(m_lv1CellVoltDiff, 2, 7);

     m_bmuStatusLayout->addWidget(lv1MoudleVoltLowLabel, 3, 0);
     m_bmuStatusLayout->addWidget(m_lv1MoudleVoltLow, 3, 1);
     m_bmuStatusLayout->addWidget(lv1MoudleVoltHighLabel, 3, 3);
     m_bmuStatusLayout->addWidget(m_lv1MoudleVoltHigh, 3, 4);
     m_bmuStatusLayout->addWidget(lv1AmbientTempLowLabel, 3, 6);
     m_bmuStatusLayout->addWidget(m_lv1AmbientTempLow, 3, 7);
     m_bmuStatusLayout->addWidget(lv1AmbientTempHighLabel, 3, 9);
     m_bmuStatusLayout->addWidget(m_lv1AmbientTempHigh, 3, 10);

     m_bmuStatusLayout->addWidget(lv1ChrgTempLowLabel, 4, 0);
     m_bmuStatusLayout->addWidget(m_lv1ChrgTempLow, 4, 1);
     m_bmuStatusLayout->addWidget(lv1ChrgTempHighLabel, 4, 3);
     m_bmuStatusLayout->addWidget(m_lv1ChrgTempHigh, 4, 4);
     m_bmuStatusLayout->addWidget(lv1DischrgTempLowLabel, 4, 6);
     m_bmuStatusLayout->addWidget(m_lv1DischrgTempLow, 4, 7);
     m_bmuStatusLayout->addWidget(lv1DischrgTempHighLabel, 4, 9);
     m_bmuStatusLayout->addWidget(m_lv1DischrgTempHigh, 4, 10);

     m_bmuStatusLayout->addWidget(lv2CellVoltLowLabel, 5, 0);
     m_bmuStatusLayout->addWidget(m_lv2CellVoltLow, 5, 1);
     m_bmuStatusLayout->addWidget(lv2CellVoltHighLabel, 5, 3);
     m_bmuStatusLayout->addWidget(m_lv2CellVoltHigh, 5, 4);
     m_bmuStatusLayout->addWidget(lv2CellVoltDiffLabel, 5, 6);
     m_bmuStatusLayout->addWidget(m_lv2CellVoltDiff, 5, 7);

     m_bmuStatusLayout->addWidget(lv2MoudleVoltLowLabel, 6, 0);
     m_bmuStatusLayout->addWidget(m_lv2MoudleVoltLow, 6, 1);
     m_bmuStatusLayout->addWidget(lv2MoudleVoltHighLabel, 6, 3);
     m_bmuStatusLayout->addWidget(m_lv2MoudleVoltHigh, 6, 4);
     m_bmuStatusLayout->addWidget(lv2AmbientTempLowLabel, 6, 6);
     m_bmuStatusLayout->addWidget(m_lv2AmbientTempLow, 6, 7);
     m_bmuStatusLayout->addWidget(lv2AmbientTempHighLabel, 6, 9);
     m_bmuStatusLayout->addWidget(m_lv2AmbientTempHigh, 6, 10);

     m_bmuStatusLayout->addWidget(lv2ChrgTempLowLabel, 7, 0);
     m_bmuStatusLayout->addWidget(m_lv2ChrgTempLow, 7, 1);
     m_bmuStatusLayout->addWidget(lv2ChrgTempHighLabel, 7, 3);
     m_bmuStatusLayout->addWidget(m_lv2ChrgTempHigh, 7, 4);
     m_bmuStatusLayout->addWidget(lv2DischrgTempLowLabel, 7, 6);
     m_bmuStatusLayout->addWidget(m_lv2DischrgTempLow, 7, 7);
     m_bmuStatusLayout->addWidget(lv2DischrgTempHighLabel, 7, 9);
     m_bmuStatusLayout->addWidget(m_lv2DischrgTempHigh, 7, 10);

     m_bmuStatusLayout->setColumnStretch(0, 1.5);
     m_bmuStatusLayout->setColumnStretch(1, 1);
     m_bmuStatusLayout->setColumnStretch(2, 3);
     m_bmuStatusLayout->setColumnStretch(3, 1.5);
     m_bmuStatusLayout->setColumnStretch(4, 1);
     m_bmuStatusLayout->setColumnStretch(5, 3);
     m_bmuStatusLayout->setColumnStretch(6, 1.5);
     m_bmuStatusLayout->setColumnStretch(7, 1);
     m_bmuStatusLayout->setColumnStretch(8, 3);
     m_bmuStatusLayout->setColumnStretch(9, 1.5);
     m_bmuStatusLayout->setColumnStretch(10, 1);

     m_bmuStatusGroup->setLayout(m_bmuStatusLayout);
}


void BMUInfoWidget::BuildCellConfigUI()
{
     m_cellConfigLayout = new QGridLayout();

     QLabel *cellAHLabel = new QLabel("电芯安时数：", this);
     QLabel *cellRateVoltLabel = new QLabel("电芯标称电压：", this);
     QLabel *cellNumLabel = new QLabel("模组电池串数：", this);
     QLabel *tempNumLabel = new QLabel("模组温度采样点数量：", this);

     QLabel *cellAHUnit = new QLabel("AH", this);
     QLabel *cellRateVoltUnit = new QLabel("mV", this);

     m_cellAH = new QLineEdit(this);
     m_cellRateVolt = new QLineEdit(this);
     m_cellNum = new QLineEdit(this);
     m_tempNum = new QLineEdit(this);

     OfflineBMUConfig();

     m_cellAH->setAlignment(Qt::AlignCenter);
     m_cellRateVolt->setAlignment(Qt::AlignCenter);
     m_cellNum->setAlignment(Qt::AlignCenter);
     m_tempNum->setAlignment(Qt::AlignCenter);

     m_cellConfigLayout->addWidget(cellAHLabel, 0, 0);
     m_cellConfigLayout->addWidget(m_cellAH, 0, 1);
     m_cellConfigLayout->addWidget(cellAHUnit, 0, 2);
     m_cellConfigLayout->addWidget(cellRateVoltLabel, 0, 4);
     m_cellConfigLayout->addWidget(m_cellRateVolt, 0, 5);
     m_cellConfigLayout->addWidget(cellRateVoltUnit, 0, 6);

     m_cellConfigLayout->addWidget(cellNumLabel, 1, 0);
     m_cellConfigLayout->addWidget(m_cellNum, 1, 1);
     m_cellConfigLayout->addWidget(tempNumLabel, 1, 4);
     m_cellConfigLayout->addWidget(m_tempNum, 1, 5);

     m_cellConfigLayout->setColumnStretch(0, 2);
     m_cellConfigLayout->setColumnStretch(1, 3);
     m_cellConfigLayout->setColumnStretch(2, 1);
     m_cellConfigLayout->setColumnStretch(3, 1);
     m_cellConfigLayout->setColumnStretch(4, 2);
     m_cellConfigLayout->setColumnStretch(5, 3);
     m_cellConfigLayout->setColumnStretch(6, 1);

     m_cellConfigGroup->setLayout(m_cellConfigLayout);
}










