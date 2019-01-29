#include "cansqlsettingwidget.h"
#include "databasedefine.h"
#include "ControlCAN.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtSql>
 #include <unistd.h>

SQLInfo g_SQLInfo;
unsigned char g_TestNumber;
extern bool g_DBConnectionFlag;

CANSQLSettingWidget::CANSQLSettingWidget(QWidget *parent)
    :QWidget(parent)
{
    qRegisterMetaType<QString>("QString");
    m_connectionFlag = 0;
    m_valueThread = NULL;

    m_systemSettingLayout = new QGridLayout(this);

    m_sqlSettingGroup = new QGroupBox("步骤1：数据库链接设置", this);
    StartSQLSetting();

    m_startCANGroup = new QGroupBox("步骤3：串口设置", this);
    StartCanSetting();

    m_canSendGroup = new QGroupBox("串口收发", this);
    CANSendGUI();

    m_testConfigGroup = new QGroupBox("步骤2：测试描述与历史保存", this);
    TestConfig();

    m_systemSettingLayout->addWidget(m_sqlSettingGroup, 0, 0);
    m_systemSettingLayout->addWidget(m_startCANGroup, 0, 1);
    m_systemSettingLayout->addWidget(m_testConfigGroup, 1, 0);
    m_systemSettingLayout->addWidget(m_canSendGroup, 1, 1);

    m_systemSettingLayout->setRowStretch(0, 1);
    m_systemSettingLayout->setRowStretch(1, 2);
    m_systemSettingLayout->setRowStretch(2, 2);

    setLayout(m_systemSettingLayout);

    m_dbConnectionTimer = new QTimer(this);
    connect(m_dbConnectionTimer, SIGNAL(timeout()), this, SLOT(HandleSqlConnectionStatus()));
    m_dbConnectionTimer->start(100);
}


CANSQLSettingWidget::~CANSQLSettingWidget()
{
    delete m_sqlSettingLayout;
    delete m_startCANLayout;
}

void CANSQLSettingWidget::StartSQLSetting()
{
    m_sqlSettingLayout = new QGridLayout();
    QLabel *hostLabel = new QLabel("服务器地址：", this);
    QLabel *databaseLabel = new QLabel("数据库名称：", this);
    QLabel *userLabel = new QLabel("用户名：", this);
    QLabel *PasswordLabel = new QLabel("密码：", this);
//    m_hostEdit = new QLineEdit("192.168.1.4", this);
//    m_userEdit = new QLineEdit("alex", this);
    m_hostEdit = new QLineEdit("localhost", this);
    m_userEdit = new QLineEdit("root", this);
    m_databaseEdit = new QLineEdit("BMSTestData", this);
    m_PasswordEdit = new QLineEdit("123456", this);
    m_PasswordEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);  //编辑时输入字符显示输入内容，否则用小黑点代替
    m_sqlConnectBut = new QPushButton("开始连接", this);
    QLabel *warnInfo = new  QLabel(this);
    warnInfo->setText(QString("（提示：断网之后，重连数据库的同时，也要重连串口！）"));
    m_cleanRecentBut = new QPushButton("清空近期数据", this);
    m_cleanHistoryBut = new QPushButton("清空历史数据", this);
    m_cleanRecentBut->setEnabled(false);
    m_cleanHistoryBut->setEnabled(false);

    m_sqlSettingLayout->addWidget(hostLabel, 0, 0);
    m_sqlSettingLayout->addWidget(m_hostEdit, 0, 1, 1, 2);
    m_sqlSettingLayout->addWidget(databaseLabel, 0, 4, 1, 1);
    m_sqlSettingLayout->addWidget(m_databaseEdit, 0, 5, 1, 1);
    m_sqlSettingLayout->addWidget(userLabel, 1, 0);
    m_sqlSettingLayout->addWidget(m_userEdit, 1, 1, 1, 2);
    m_sqlSettingLayout->addWidget(PasswordLabel, 1, 4, 1, 1);
    m_sqlSettingLayout->addWidget(m_PasswordEdit, 1, 5, 1, 1);
    m_sqlSettingLayout->addWidget(warnInfo, 2, 0, 1, 3);
    m_sqlSettingLayout->addWidget(m_cleanRecentBut, 3, 0, 1, 1);
    m_sqlSettingLayout->addWidget(m_cleanHistoryBut, 3, 2, 1, 1);
    m_sqlSettingLayout->addWidget(m_sqlConnectBut, 3, 5, 1, 1);

    m_sqlSettingLayout->setColumnStretch(0, 1);
    m_sqlSettingLayout->setColumnStretch(1, 1);
    m_sqlSettingLayout->setColumnStretch(2, 4);
    m_sqlSettingLayout->setColumnStretch(3, 1);
    m_sqlSettingLayout->setColumnStretch(4, 1);
    m_sqlSettingLayout->setColumnStretch(5, 5);

    m_sqlSettingGroup->setLayout(m_sqlSettingLayout);

    connect(m_sqlConnectBut, SIGNAL(clicked()), this, SLOT(OnConnectDatabase()));
    connect(m_cleanRecentBut, SIGNAL(clicked()), this, SLOT(CleanRecentDB()));
    connect(m_cleanHistoryBut, SIGNAL(clicked()), this, SLOT(CleanHistoryDB()));
}


void CANSQLSettingWidget::StartCanSetting()
{
    //必须在信号中注册uint64_t类型，否则无法将接收帧计数发送到界面程序。
    qRegisterMetaType<uint64_t>("uint64_t");

    int i = 0;
    m_startCANLayout = new QGridLayout();

    m_devTypeCombo = new QComboBox(this);
    m_devTypeCombo->addItem("VCI_USBCAN1", VCI_USBCAN1);
    m_devTypeCombo->addItem("VCI_USBCAN2", VCI_USBCAN2);
    m_devTypeCombo->addItem("VCI_USBCAN2A", VCI_USBCAN2A);
    m_devTypeCombo->addItem("VCI_USBCAN_E_U", VCI_USBCAN_E_U);
    m_devTypeCombo->addItem("VCI_USBCAN_2E_U", VCI_USBCAN_2E_U);
    m_devTypeCombo->setCurrentIndex(1);

    m_devIndexCombo = new QComboBox(this);
    for (i=0; i<32; i++)
    {
        m_devIndexCombo->addItem(QString("%1").arg(i), i);
    }

    m_channelCombo = new QComboBox(this);
    m_channelCombo->addItem("0", 0);
    m_channelCombo->addItem("1", 1);

    m_openAllCANBox = new QCheckBox(this);

    m_baudCombo = new QComboBox(this);
    m_baudCombo->addItem("10Kbps", BAUD_10);
    m_baudCombo->addItem("20Kbps", BAUD_20);
    m_baudCombo->addItem("50Kbps", BAUD_50);
    m_baudCombo->addItem("100Kbps", BAUD_100);
    m_baudCombo->addItem("200Kbps", BAUD_200);
    m_baudCombo->addItem("250Kbps", BAUD_250);
    m_baudCombo->addItem("500Kbps", BAUD_500);
    m_baudCombo->addItem("800Kbps", BAUD_800);
    m_baudCombo->addItem("1000Kbps", BAUD_1000);
    m_baudCombo->setCurrentIndex(6);

    m_modeCombo = new QComboBox(this);
    m_modeCombo->addItem("正常收发", NORMAL_MODE);
    m_modeCombo->addItem("只听模式", LISTEN_ONLY_MODE);
    m_modeCombo->addItem("自发自收", INTERNAL_LOOPBACK_MODE);

    QLabel *devTypeLabel = new QLabel("设备类型：", this);
    QLabel *devIndexLabel = new QLabel("设备索引号：", this);
    QLabel *channelLabel = new QLabel("通道号：", this);
    QLabel *openAllCANLabel = new QLabel("打开全部CAN通道", this);
    QLabel *baudLabel = new QLabel("波特率：", this);
    QLabel *modeLabel = new QLabel("工作模式：", this);
    m_canConnectBut = new QPushButton("连接", this);
    m_canDisconnectBut = new QPushButton("断开", this);

    m_startCANLayout->addWidget(devTypeLabel, 0, 0);
    m_startCANLayout->addWidget(m_devTypeCombo, 0, 1);
    m_startCANLayout->addWidget(devIndexLabel, 0, 3);
    m_startCANLayout->addWidget(m_devIndexCombo, 0, 4);
    m_startCANLayout->addWidget(channelLabel, 1, 0);
    m_startCANLayout->addWidget(m_channelCombo, 1, 1);
    m_startCANLayout->addWidget(openAllCANLabel, 1, 3);
    m_startCANLayout->addWidget(m_openAllCANBox, 1, 4);
    m_startCANLayout->addWidget(baudLabel, 2, 0);
    m_startCANLayout->addWidget(m_baudCombo, 2, 1);
    m_startCANLayout->addWidget(modeLabel, 2, 3);
    m_startCANLayout->addWidget(m_modeCombo, 2, 4);
    m_startCANLayout->addWidget(m_canConnectBut, 3, 1, 1, 1);
    m_startCANLayout->addWidget(m_canDisconnectBut, 3, 4, 1, 1);
    m_startCANLayout->setColumnStretch(0, 1);
    m_startCANLayout->setColumnStretch(1, 5);
    m_startCANLayout->setColumnStretch(2, 1);
    m_startCANLayout->setColumnStretch(3, 1);
    m_startCANLayout->setColumnStretch(4, 5);

    m_startCANGroup->setLayout(m_startCANLayout);

    connect(m_canConnectBut, SIGNAL(clicked()), this, SLOT(OnConncetCAN()));
    connect(m_canDisconnectBut, SIGNAL(clicked()), this, SLOT(OnDisconnectCAN()));
}


void CANSQLSettingWidget::CANSendGUI()
{
    m_canSendLayout = new QGridLayout();
    QLabel *sendIDLabel = new QLabel("发送ID：", this);
    QLabel *sendDataLabel = new QLabel("发送数据：", this);

    m_sendID = new QLineEdit(this);
    m_sendData = new QLineEdit(this);
    m_sendButton = new QPushButton("发送", this);
    m_dispalyCAN = new QTextEdit(this);
    m_dispalyCAN->document()->setMaximumBlockCount(1000);   //设置TextEdit的最大行数

    m_sendID->setText("0000008A");
    m_sendData->setText("01 02 03 04 05 06 07 08 ");

    m_canSendLayout->addWidget(sendIDLabel, 0, 0, 1, 1);
    m_canSendLayout->addWidget(m_sendID, 0, 1, 1, 1);
    m_canSendLayout->addWidget(sendDataLabel, 1, 0, 1, 1);
    m_canSendLayout->addWidget(m_sendData, 1, 1, 1, 1);
    m_canSendLayout->addWidget(m_sendButton, 1, 3, 1, 2);
    m_canSendLayout->addWidget(m_dispalyCAN, 2, 0, 1, 5);

    m_canSendLayout->setColumnStretch(0, 1);
    m_canSendLayout->setColumnStretch(1, 5);
    m_canSendLayout->setColumnStretch(2, 1);
    m_canSendLayout->setColumnStretch(3, 1);
    m_canSendLayout->setColumnStretch(4, 5);

    m_canSendGroup->setLayout(m_canSendLayout);

    connect(m_sendButton, SIGNAL(clicked()), this, SLOT(OnCANSend()));
}


void CANSQLSettingWidget::TestConfig()
{
    m_testConfigLayout = new QGridLayout();
    QLabel *testNumberLabel = new QLabel("测试编号：", this);
    QLabel *bmuNumberLabel = new QLabel("BMU数量：", this);

    m_testNumber = new QLineEdit(this);
    m_bmuNumber = new QLineEdit(this);
    m_saveText = new QPushButton("保存测试说明", this);
    m_testDescription = new QTextEdit(this);

    m_testNumber->setText("0");
    m_bmuNumber->setText("8");

    m_testConfigLayout->addWidget(testNumberLabel, 0, 0, 1, 1);
    m_testConfigLayout->addWidget(m_testNumber, 0, 1, 1, 1);
    m_testConfigLayout->addWidget(bmuNumberLabel, 1, 0, 1, 1);
    m_testConfigLayout->addWidget(m_bmuNumber, 1, 1, 1, 1);
    m_testConfigLayout->addWidget(m_saveText, 1, 3, 1, 2);
    m_testConfigLayout->addWidget(m_testDescription, 2, 0, 1, 5);

    m_testConfigLayout->setColumnStretch(0, 1);
    m_testConfigLayout->setColumnStretch(1, 5);
    m_testConfigLayout->setColumnStretch(2, 1);
    m_testConfigLayout->setColumnStretch(3, 1);
    m_testConfigLayout->setColumnStretch(4, 5);

    m_testConfigGroup->setLayout(m_testConfigLayout);

    connect(m_saveText, SIGNAL(clicked()), this, SLOT(SaveTestCase()));
}


void CANSQLSettingWidget::SaveTestCase()
{
    QSqlQuery query = QSqlQuery(m_mainDB);
    QString sqlLine = NULL;
    QString describtion = NULL;
    int bmuNumber = 0;

    if (g_DBConnectionFlag)
    {
        g_TestNumber = m_testNumber->text().toUShort();
        describtion = m_testDescription->toPlainText();
        bmuNumber = m_bmuNumber->text().toInt();

        sqlLine = QString("insert into %1 (TestNumber, Time, BMUNumber, Describtion) values (%2, UNIX_TIMESTAMP(), %3, '%4')")
                .arg(TEST_CASE).arg(g_TestNumber).arg(bmuNumber).arg(describtion);

        query.exec(sqlLine);

        if (query.lastError().isValid())
        {
            QMessageBox::warning(NULL, "错误", QString("数据库操作失败！\n") + query.lastError().text(),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            g_DBConnectionFlag = false;
            return;
        }
    }
}


void CANSQLSettingWidget::CleanRecentDB()
{
    QSqlQuery query = QSqlQuery(m_mainDB);
    QString sqlLine = NULL;

    if (g_DBConnectionFlag)
    {
        sqlLine = QString("drop table %1").arg(RECENT_RECORD);
        query.exec(sqlLine);

        if (query.lastError().isValid())
        {
            QMessageBox::warning(NULL, "错误", QString("删除历史数据库失败！\n") + query.lastError().text(),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return;
        }

        sqlLine = QString("CREATE TABLE `%1` ("
                          "`SerialNumber` int(10) unsigned NOT NULL AUTO_INCREMENT,"
                          "`Time` int(11) NOT NULL DEFAULT '0',"
                          "`TestNumber` smallint(5) unsigned DEFAULT NULL,"
                          "`SignalID` int(10) unsigned DEFAULT NULL,"
                          "`ParameterName` varchar(21) DEFAULT NULL,"
                          "`Value` float(15,5) DEFAULT NULL,"
                          "`Type` tinyint(4) DEFAULT NULL,"
                          "PRIMARY KEY (`SerialNumber`),"
                          "KEY `RecvTime` (`Time`),"
                          "KEY `TestNumber` (`TestNumber`),"
                          "KEY `SignalID` (`SignalID`),"
                          "KEY `ParameterName` (`ParameterName`),"
                          "KEY `Type` (`Type`)"
                          ") ENGINE=InnoDB AUTO_INCREMENT=0 DEFAULT CHARSET=utf8;").arg(RECENT_RECORD);
        query.exec(sqlLine);

        if (query.lastError().isValid())
        {
            QMessageBox::warning(NULL, "错误", QString("删除历史数据库失败！\n") + query.lastError().text(),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return;
        }
        m_cleanRecentBut->setText(QString("清空近期完成"));
    }
    else
    {
        QMessageBox::warning(NULL, "错误", QString("数据库操作失败！\n") + query.lastError().text(),
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
}


void CANSQLSettingWidget::CleanHistoryDB()
{
    QSqlQuery query = QSqlQuery(m_mainDB);
    QString sqlLine = NULL;

    if (g_DBConnectionFlag)
    {
        sqlLine = QString("drop table %1").arg(HISTORY_RECORD);
        query.exec(sqlLine);

        if (query.lastError().isValid())
        {
            QMessageBox::warning(NULL, "错误", QString("删除历史数据库失败！\n") + query.lastError().text(),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return;
        }
        sqlLine = QString("CREATE TABLE `%1` "
                          "(`SerialNumber` int(10) unsigned NOT NULL AUTO_INCREMENT,"
                          "`Time` int(11) NOT NULL DEFAULT '0',"
                          "`TestNumber` smallint(5) unsigned DEFAULT NULL,"
                          "`SignalID` int(10) unsigned DEFAULT NULL,"
                          "`ParameterName` varchar(21) DEFAULT NULL,"
                          "`MaxValue` float(15,5) DEFAULT NULL,"
                          "`MinValue` float(15,5) DEFAULT NULL,"
                          "`Value` float(15,5) DEFAULT NULL,"
                          "`Type` tinyint(4) DEFAULT NULL,"
                          "PRIMARY KEY (`SerialNumber`),"
                          "KEY `StartTime` (`Time`),"
                          "KEY `TestNumber` (`TestNumber`),"
                          "KEY `SignalID` (`SignalID`),"
                          "KEY `ParameterName` (`ParameterName`),"
                          "KEY `Type` (`Type`)"
                          ") ENGINE=InnoDB AUTO_INCREMENT=0 DEFAULT CHARSET=utf8;").arg(HISTORY_RECORD);
        query.exec(sqlLine);

        if (query.lastError().isValid())
        {
            QMessageBox::warning(NULL, "错误", QString("删除历史数据库失败！\n") + query.lastError().text(),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return;
        }
        m_cleanHistoryBut->setText(QString("清空历史完成"));
    }
    else
    {
        QMessageBox::warning(NULL, "错误", QString("数据库操作失败！\n") + query.lastError().text(),
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
}


void CANSQLSettingWidget::OnConnectDatabase()
{
    g_SQLInfo.hostName = m_hostEdit->text();
    g_SQLInfo.dbName = m_databaseEdit->text();
    g_SQLInfo.userName = m_userEdit->text();
    g_SQLInfo.password = m_PasswordEdit->text();

    m_mainDB = QSqlDatabase::addDatabase("QMYSQL", "MainSQL");
    m_mainDB.setHostName(g_SQLInfo.hostName);
    m_mainDB.setDatabaseName(g_SQLInfo.dbName);
    m_mainDB.setUserName(g_SQLInfo.userName);
    m_mainDB.setPassword(g_SQLInfo.password);
    if (!m_mainDB.open())
    {
#ifdef DEBUG_MODE
        qDebug() << m_mainDB.lastError();
#endif
        QMessageBox::warning(NULL, "错误", QString("数据库连接失败！\n") + m_mainDB.lastError().text(),
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        g_DBConnectionFlag = false;
        return;
    }
    g_DBConnectionFlag = true;

    if (m_valueThread == NULL)
    {
        m_valueThread = new ValueThread();
        m_valueThread->start();
        connect(m_valueThread, SIGNAL(ErrorInfo(QString)), this, SLOT(PinrtErrorInfo(QString)), Qt::QueuedConnection);
    }
}


void CANSQLSettingWidget::HandleSqlConnectionStatus()
{
    if (g_DBConnectionFlag)
    {
        m_sqlConnectBut->setEnabled(false);
    }
    else
    {
        if (m_valueThread != NULL)
        {
            m_valueThread->terminate();
            m_valueThread->wait();
            delete m_valueThread;   //销毁子线程
            m_valueThread = NULL;
        }
        m_sqlConnectBut->setEnabled(true);
    }
}


void CANSQLSettingWidget::RebuildRecentTable(QString currentTime)
{
    QSqlQuery query = QSqlQuery(m_mainDB);
    QString sqlLine = NULL;
    unsigned int valueCount = 0;

    if (g_DBConnectionFlag)
    {
        sqlLine = QString("select count(*) from %1 where `Time` >= '%2 00:00:00'").arg(RECENT_RECORD).arg(currentTime.left(10));
        query.exec(sqlLine);

        if (query.lastError().isValid())
        {
            QMessageBox::warning(NULL, "错误", QString("数据库操作失败！\n") + query.lastError().text(),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            g_DBConnectionFlag = false;
            return;
        }

        while(query.next())
        {
            valueCount = query.value(0).toUInt();
        }

        if (valueCount == 0)
        {
            sqlLine = QString("drop table %1").arg(RECENT_RECORD);
            query.exec(sqlLine);

            if (query.lastError().isValid())
            {
                QMessageBox::warning(NULL, "错误", QString("数据库操作失败！\n") + query.lastError().text(),
                                     QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                g_DBConnectionFlag = false;
                return;
            }

            sqlLine = QString(" CREATE TABLE `RecentRecord` (\
                              `SerialNumber` int(10) unsigned NOT NULL AUTO_INCREMENT,\
                              `Time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,\
                              `TestNumber` smallint(5) unsigned DEFAULT NULL,\
                              `SignalID` int(10) unsigned DEFAULT NULL,\
                              `ParameterName` varchar(20) DEFAULT NULL,\
                              `Value` smallint(5) unsigned DEFAULT NULL,\
                              `Ratio` float(2,1) DEFAULT '1.0',\
                              `Offset` smallint(5) unsigned DEFAULT '0',\
                              PRIMARY KEY (`SerialNumber`),\
                              KEY `Time` (`Time`),\
                              KEY `TestNumber` (`TestNumber`),\
                              KEY `SignalID` (`SignalID`),\
                              KEY `ParameterName` (`ParameterName`))\
                    ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=latin1");
                    query.exec(sqlLine);

            if (query.lastError().isValid())
            {
                QMessageBox::warning(NULL, "错误", QString("数据库操作失败！\n") + query.lastError().text(),
                                     QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                g_DBConnectionFlag = false;
                return;
            }
        }
    }
}


