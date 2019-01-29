#include <QFont>
#include <QBrush>
#include <QPalette>
#include <QApplication>
#include <QDesktopWidget>
#include "MainDialog.h"

bool g_DBConnectionFlag;
bool g_CanConnectionFlag;
extern BMSUIData g_GetCANBMSData;
extern QList<UINT> g_BMSVersionList;

BMSMainDialog::BMSMainDialog(QWidget *parent)
    : QDialog(parent)
{
    m_versionFlag = RECV_SIGNAL_FAIL;
    m_tabWidget = new QTabWidget(this);
    m_bmsInfoWidget = new BMSInfoWidget(this);
    m_bmuInfoWidget = new BMUInfoWidget(this);
    m_realTimeChartWidget = new RealTimeDataChartWidget(this);
    m_systemSetting = new CANSQLSettingWidget(this);
    m_dataTableWidget = new DataTableWidget(this);

    m_tabWidget->addTab(m_bmsInfoWidget, "BMS信息");
    m_tabWidget->addTab(m_bmuInfoWidget, "BMU信息");
    m_tabWidget->addTab(m_realTimeChartWidget, "实时数据");
    m_tabWidget->addTab(m_dataTableWidget, "历史数据");
    m_tabWidget->addTab(m_systemSetting, "串口与数据库连接配置");

    m_statusBar = new QStatusBar(this);
    m_statusWidget = new QWidget(m_statusBar);
    CreateStatusWidget();

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_tabWidget);
    m_mainLayout->addWidget(m_statusBar);
    setLayout(m_mainLayout);

    /** 添加最大化、最小化按钮和关闭按钮 **/
    setWindowTitle("BMS测试工具（V1.4）");
    Qt::WindowFlags flags = Qt::Dialog;
    flags |=Qt::WindowMinMaxButtonsHint;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    showNormal();

    m_setVersionTimer = new QTimer(this);
    connect(m_setVersionTimer, SIGNAL(timeout()), this, SLOT(SetBMSVersion()));
    m_setVersionTimer->start(100);

    m_versionTimeout = new QTimer(this);
    connect(m_versionTimeout, SIGNAL(timeout()), this, SLOT(VersionTimeout()));
    m_versionTimeout->start(5000);

    m_statusTimer = new QTimer(this);
    connect(m_statusTimer, SIGNAL(timeout()), this, SLOT(SetStatus()));
    m_statusTimer->start(100);
}


BMSMainDialog::~BMSMainDialog()
{

}


void BMSMainDialog::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}


void BMSMainDialog::SetBMSVersion()
{
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::black);

    while(!g_BMSVersionList.isEmpty())
    {
        g_BMSVersionList.removeFirst();
        m_softwareVersion->setPalette(palette);
        m_hardwareVersion->setPalette(palette);
        m_softwareVersion->setText(tr("%1-%2-%3").arg(g_GetCANBMSData.bmsVersionInfo.swVersionV)\
                                   .arg(g_GetCANBMSData.bmsVersionInfo.swVersionB)\
                                   .arg(g_GetCANBMSData.bmsVersionInfo.swVersionS));
        m_hardwareVersion->setText(tr("%1-%2-%3-%4").arg(g_GetCANBMSData.bmsVersionInfo.hwVersion)\
                                   .arg(g_GetCANBMSData.bmsVersionInfo.hwVersionSP)\
                                   .arg(g_GetCANBMSData.bmsVersionInfo.hwVersionV)\
                                   .arg(g_GetCANBMSData.bmsVersionInfo.hwVersionR));
        m_versionFlag = RECV_SIGNAL_SUCCESSFUL;
    }
}


void BMSMainDialog::SetStatus()
{
    QPalette online;
    online.setColor(QPalette::WindowText, Qt::darkGreen);
    QPalette offline;
    offline.setColor(QPalette::WindowText, Qt::red);
    QPalette error;
    error.setColor(QPalette::WindowText, Qt::darkBlue);

    if (g_DBConnectionFlag)   //在线
    {
        m_dbConnection->setText(QString("连接"));
        m_dbConnection->setPalette(online);
    }
    else   //离线
    {
        m_dbConnection->setText(QString("断开"));
        m_dbConnection->setPalette(offline);
    }

    if (g_CanConnectionFlag)
    {
        m_canConnection->setText(QString("连接"));
        m_canConnection->setPalette(online);
    }
    else
    {
        m_canConnection->setText(QString("断开"));
        m_canConnection->setPalette(offline);
    }
}


void BMSMainDialog::VersionTimeout()
{
    if (!m_versionFlag)
    {
        QPalette palette;
        palette.setColor(QPalette::WindowText, Qt::lightGray);
        m_softwareVersion->setPalette(palette);
        m_hardwareVersion->setPalette(palette);
    }
    m_versionFlag = RECV_SIGNAL_FAIL;
}


void BMSMainDialog::CreateStatusWidget()
{
    QGridLayout *statusLayout = new QGridLayout(this);
    QLabel *softVersionLabel = new QLabel("BMS软件版本：", this);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::red);
    m_softwareVersion = new QLabel(this);
    QLabel *separator = new QLabel("  |  ", this);
    QLabel *hardVersionLabel = new QLabel("BMS硬件版本：", this);
    m_hardwareVersion = new QLabel(this);
    QLabel *separator1 = new QLabel("  |  ", this);
    QLabel *dbConnectionLabel = new QLabel("数据库连接：", this);
    QLabel *canConnectionLabel = new QLabel("串口连接：", this);
    m_dbConnection = new QLabel("断开", this);
    QLabel *separator2 = new QLabel("  |  ", this);
    m_canConnection = new QLabel("断开", this);
    m_dbConnection->setPalette(palette);
    m_canConnection->setPalette(palette);

    statusLayout->addWidget(softVersionLabel, 0, 0);
    statusLayout->addWidget(m_softwareVersion, 0, 1);
    statusLayout->addWidget(separator, 0, 2);
    statusLayout->addWidget(hardVersionLabel, 0, 3);
    statusLayout->addWidget(m_hardwareVersion, 0, 4);
    statusLayout->addWidget(separator1, 0, 5);
    statusLayout->addWidget(dbConnectionLabel, 0, 6);
    statusLayout->addWidget(m_dbConnection, 0, 7);
    statusLayout->addWidget(separator2, 0, 8);
    statusLayout->addWidget(canConnectionLabel, 0, 9);
    statusLayout->addWidget(m_canConnection, 0, 10);

    m_statusWidget->setLayout(statusLayout);
    m_statusBar->addWidget(m_statusWidget);
}
