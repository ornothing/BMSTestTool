#include "datatablewidget.h"
#include "widgetdatastructure.h"
#include "databasedefine.h"
#include "systemdefine.h"
#include <QDebug>
#include <QSqlError>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QTreeWidgetItemIterator>
#include <QDateTime>
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QSqlQuery>

extern SQLInfo g_SQLInfo;

DataTableWidget::DataTableWidget(QWidget *parent)
    :QWidget(parent)
{
    m_dataModel = NULL;
    m_signalNumber = 0;
    m_connectionFlag = false;
    m_dataTableLayout = new QGridLayout(this);
    m_tableView  = new QTableView(this);

    BuildSelectedSignalTable();
    BuildControlModule();

    m_dataTableLayout->addWidget(m_dataTableGroup, 0, 0);
    m_dataTableLayout->addWidget(m_tableView, 0, 1);
    m_dataTableLayout->setColumnStretch(0, 1);
    m_dataTableLayout->setColumnStretch(1, 3);
    InitSlot();
}


DataTableWidget::~DataTableWidget()
{

}

void DataTableWidget::InitSlot()
{
    connect(m_searchButton, SIGNAL(clicked()), this, SLOT(SearchSignal()));
    connect(m_addButton, SIGNAL(clicked()), this, SLOT(AddSignal()));
    connect(m_deleteButton, SIGNAL(clicked()), this, SLOT(DeleteSignal()));
    connect(m_drawChartButton, SIGNAL(clicked()), this, SLOT(CreateHistoryChart()));
}


void DataTableWidget::BuildControlModule()
{
    m_dataTableGroup = new QGroupBox(this);
    m_dataTableSelectLayout = new QGridLayout();

    m_addGroup = new QGroupBox("信号控制", this);
    m_timeGroup = new QGroupBox(this);
    m_addLayout = new QGridLayout();
    m_timeLayout = new QGridLayout();

    m_addButton = new QPushButton(QString("添加"), this);
    m_deleteButton = new QPushButton(QString("删除"),this);
    m_selectAll = new QCheckBox(this);
    m_selectTable = new QComboBox(this);
    m_selectTable->addItem(QString("近期数据"), 0);
    m_selectTable->addItem(QString("历史数据"), 1);
    m_beginTime = new QLineEdit(this);
    m_beginTime->setText(QString("2019-01-11 11:00:00"));
    m_duration = new QLineEdit(this);
    m_duration->setText(QString("2"));

    m_searchButton = new QPushButton(QString("搜索"), this);
    m_value = new QLineEdit(this);
    m_condition = new QComboBox(this);
    m_conditionFlag = new QCheckBox(this);
    m_drawChartButton = new QPushButton(QString("绘制曲线"), this);

    QLabel *selectAllLabel = new QLabel(QString("全选"), this);
    QLabel *beginTimeLabel = new QLabel(QString("时间："), this);
    QLabel *durationLabel = new QLabel(QString("时长："), this);
    QLabel *valueLabel = new QLabel(QString("值："), this);
    QLabel *conditionFlag = new QLabel(QString("值过滤："), this);
    m_timeUnit = new QComboBox(this);
    m_timeUnit->addItem(QString("秒"), 0);
    m_timeUnit->addItem(QString("分"), 1);
    m_timeUnit->addItem(QString("时"), 2);
    m_timeUnit->addItem(QString("天"), 3);
    m_timeUnit->setCurrentIndex(2);

    m_condition->addItem(QString("="), 0);
    m_condition->addItem(QString(">"), 1);
    m_condition->addItem(QString("<"), 2);
    m_condition->addItem(QString(">="), 3);
    m_condition->addItem(QString("<="), 4);

    m_addLayout->addWidget(m_addButton, 0, 0);
    m_addLayout->addWidget(m_deleteButton, 0, 1);
    m_addLayout->addWidget(m_selectAll, 0, 3);
    m_addLayout->addWidget(selectAllLabel, 0, 4);
    m_addLayout->setColumnStretch(0, 1);
    m_addLayout->setColumnStretch(1, 1);
    m_addLayout->setColumnStretch(2, 0.5);
    m_addLayout->setColumnStretch(3, 0.5);
    m_addLayout->setColumnStretch(4, 0.5);
    m_addGroup->setLayout(m_addLayout);

    m_timeLayout->addWidget(beginTimeLabel, 0, 0);
    m_timeLayout->addWidget(m_beginTime, 0, 1, 1, 2);
    m_timeLayout->addWidget(m_selectTable, 0, 4);

    m_timeLayout->addWidget(durationLabel, 1, 0);
    m_timeLayout->addWidget(m_duration, 1, 1, 1, 2);
    m_timeLayout->addWidget(m_timeUnit, 1, 4);

    m_timeLayout->addWidget(valueLabel, 2, 0);
    m_timeLayout->addWidget(m_condition, 2, 1, 1, 2);
    m_timeLayout->addWidget(m_value, 2, 4);

    m_timeLayout->addWidget(conditionFlag, 3, 0);
    m_timeLayout->addWidget(m_conditionFlag, 3, 1);
    m_timeLayout->addWidget(m_searchButton, 3, 2);
    m_timeLayout->addWidget(m_drawChartButton, 3, 4);

    m_timeLayout->setColumnStretch(0, 0.5);
    m_timeLayout->setColumnStretch(1, 1);
    m_timeLayout->setColumnStretch(2, 1);
    m_timeLayout->setColumnStretch(3, 0.5);
    m_timeLayout->setColumnStretch(4, 1);
    m_timeGroup->setLayout(m_timeLayout);

    m_dataTableSelectLayout->addWidget(m_signalTree, 0, 0);
    m_dataTableSelectLayout->addWidget(m_selectedTable, 1, 0);
    m_dataTableSelectLayout->addWidget(m_addGroup, 2, 0);
    m_dataTableSelectLayout->addWidget(m_timeGroup, 3, 0);

    m_dataTableSelectLayout->setRowStretch(0, 5);
    m_dataTableSelectLayout->setRowStretch(1, 2);
    m_dataTableSelectLayout->setRowStretch(2, 0.5);
    m_dataTableSelectLayout->setRowStretch(3, 0.5);
    m_dataTableGroup->setLayout(m_dataTableSelectLayout);
}


void DataTableWidget::BuildSelectedSignalTable()
{
    int i = 0;

    //信号选择
    m_signalTree = new SignalTreeWidget();
    m_signalTree->setParent(this);

    //已选信号
    m_selectedTable = new QTableWidget(this);

    m_selectedTable->setColumnCount(2); //设置列数
    m_selectedTable->setRowCount(MAX_SELECTED_SIGNAL_NUMBER);

    QStringList header;
    header << QString("已选信号") << QString("所属模块");
    m_selectedTable->setHorizontalHeaderLabels(header);
    m_selectedTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#6495ED;}"); //设置表头背景色
    m_selectedTable->horizontalHeader()->setSectionsClickable(false);
    m_selectedTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //先自适应宽度
    m_selectedTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    m_selectedTable->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度，在最后一列填充
    m_selectedTable->horizontalHeader()->setFixedHeight(31);
    m_selectedTable->setStyleSheet("selection-background-color:gray;"); //设置选中背景色
    m_selectedTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_selectedTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_selectedTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_selectedTable->setFocusPolicy(Qt::NoFocus);

    for (i=0; i<MAX_SELECTED_SIGNAL_NUMBER; i++)
    {
        m_selectedTable->setRowHeight(i, 31);
    }
}


int DataTableWidget::CreateDataTableSQLConnection()
{
    m_dataTableDB = QSqlDatabase::addDatabase("QMYSQL", "DataTableSQL");
    m_dataTableDB.setHostName(g_SQLInfo.hostName);
    m_dataTableDB.setDatabaseName(g_SQLInfo.dbName);
    m_dataTableDB.setUserName(g_SQLInfo.userName);
    m_dataTableDB.setPassword(g_SQLInfo.password);

    if (!m_dataTableDB.open())
    {
        QMessageBox::warning(NULL, "警告", QString("数据库打开失败！\n") + m_dataTableDB.lastError().text(),
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
#ifdef DEBUG_MODE
        qDebug() << m_dataTableDB.lastError();
#endif
        m_connectionFlag = false;
        return -1;
    }

    return 1;
}


void DataTableWidget::SearchSignal()
{
    QString queryString = NULL;
    UINT baginUnixTime = 0;
    QString timeString = m_beginTime->text();
    QDateTime dateTime = QDateTime::fromString(timeString, "yyyy-MM-dd hh:mm:ss");
    baginUnixTime = dateTime.toTime_t();
    float queryValue = m_value->text().toFloat();
    QString queryCondition = m_condition->currentText();

#ifdef DEBUG_MODE
    qDebug() << baginUnixTime;
#endif

    UINT durationNumber = m_duration->text().toUInt();
    UINT endUnixTime = GetTimeDuration(baginUnixTime, durationNumber);

#ifdef DEBUG_MODE
    qDebug() << endUnixTime;
#endif

    if (endUnixTime > 0)
    {
        QString selectedTable = NULL;

        if (m_selectTable->currentIndex() == 0)
        {
            selectedTable = RECENT_RECORD;
        }
        else
        {
            selectedTable = HISTORY_RECORD;
        }
#ifdef DEBUG_MODE
        qDebug() << selectedTable;
#endif

        if (!m_connectionFlag)
        {
            if (CreateDataTableSQLConnection() != -1)
            {
                m_connectionFlag = true;
            }
            else
            {
                return;
            }
        }

        if (!m_dataModel)
        {
            m_dataModel = new QSqlQueryModel();
        }
//        if (!m_sqlCondition.isEmpty())
//        {
//            m_sqlCondition.clear();
//        }

        if (m_selectAll->isChecked())   //全选
        {
            queryString = QString("select * from %1 where Time >= %2 and Time <= %3 order by SerialNumber")\
                    .arg(selectedTable).arg(baginUnixTime).arg(endUnixTime);
            m_dataModel->setQuery(queryString, m_dataTableDB);
            if (m_dataModel->lastError().isValid())
            {
                QMessageBox::warning(NULL, "错误", QString("数据库操作失败！\n") + m_dataModel->lastError().text(),
                                     QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                m_connectionFlag = false;
                return;
            }
        }
        else   //条件选择
        {
            queryString = GetTableString(selectedTable, baginUnixTime, endUnixTime, queryValue, queryCondition);
            if (queryString != NULL)
            {
                m_dataModel->setQuery(queryString, m_dataTableDB);

                if (m_dataModel->lastError().isValid())
                {
                    QMessageBox::warning(NULL, "错误", QString("数据库操作失败！\n") + m_dataModel->lastError().text(),
                                         QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    m_connectionFlag = false;
                    return;
                }

                while (m_dataModel->canFetchMore())
                    m_dataModel->fetchMore();
            }
            else
            {
                QMessageBox::warning(NULL, "警告", "请添加需要查询的参数！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                return;
            }
        }

        if (selectedTable == RECENT_RECORD)
        {
            m_dataModel->setHeaderData(0, Qt::Horizontal, QString("序号"));
            m_dataModel->setHeaderData(1, Qt::Horizontal, QString("时间"));
            m_dataModel->setHeaderData(2, Qt::Horizontal, QString("测试编号"));
            m_dataModel->setHeaderData(3, Qt::Horizontal, QString("信号ID"));
            m_dataModel->setHeaderData(4, Qt::Horizontal, QString("参数名称"));
            m_dataModel->setHeaderData(5, Qt::Horizontal, QString("值"));
            m_dataModel->setHeaderData(6, Qt::Horizontal, QString("值类型（1:原始/2:平均）"));
            m_tableView->setModel(m_dataModel);
            m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            m_tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
        }
        if (selectedTable == HISTORY_RECORD)
        {
            m_dataModel->setHeaderData(0, Qt::Horizontal, QString("序号"));
            m_dataModel->setHeaderData(1, Qt::Horizontal, QString("时间"));
            m_dataModel->setHeaderData(2, Qt::Horizontal, QString("测试编号"));
            m_dataModel->setHeaderData(3, Qt::Horizontal, QString("信号ID"));
            m_dataModel->setHeaderData(4, Qt::Horizontal, QString("参数名称"));
            m_dataModel->setHeaderData(5, Qt::Horizontal, QString("最大值"));
            m_dataModel->setHeaderData(6, Qt::Horizontal, QString("最小值"));
            m_dataModel->setHeaderData(7, Qt::Horizontal, QString("平均值"));
            m_dataModel->setHeaderData(8, Qt::Horizontal, QString("值类型（1:原始/2:平均）"));
            m_tableView->setModel(m_dataModel);
            m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            m_tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
            m_tableView->horizontalHeader()->setSectionResizeMode(8, QHeaderView::ResizeToContents);
        }
    }
}


QString DataTableWidget::GetTableString(QString table, UINT beginTime, UINT endTime, float value, QString condition)
{
    int size = m_sqlCondition.size();
    QString sqlString = NULL;

    switch(size)
    {
    case 0:
        return NULL;
    case 1:
        if (m_conditionFlag->isChecked())
        {
            sqlString = QString("select * from %1 where Time >= %2 and Time <= %3 and (ParameterName = '%4' and SignalID = %5) and Value %6 %7 order by SerialNumber")\
                    .arg(table).arg(beginTime).arg(endTime)\
                    .arg(m_sqlCondition.at(0).parameterName).arg(m_sqlCondition.at(0).signalID).arg(condition).arg(value);
        }
        else
        {
            sqlString = QString("select * from %1 where Time >= %2 and Time <= %3 and (ParameterName = '%4' and SignalID = %5) order by SerialNumber")\
                    .arg(table).arg(beginTime).arg(endTime)\
                    .arg(m_sqlCondition.at(0).parameterName).arg(m_sqlCondition.at(0).signalID).arg(condition).arg(value);
        }
#ifdef DEBUG_MODE
        qDebug() << sqlString;
#endif
        return sqlString;
    case 2:
       sqlString = QString("select * from %1 where Time >= %2 and Time <= %3 and ((ParameterName = '%4' and SignalID = %5) "\
                            "or (ParameterName = '%6' and SignalID = %7)) order by SerialNumber")\
                .arg(table).arg(beginTime).arg(endTime)\
                .arg(m_sqlCondition.at(0).parameterName).arg(m_sqlCondition.at(0).signalID)\
                .arg(m_sqlCondition.at(1).parameterName).arg(m_sqlCondition.at(1).signalID);
#ifdef DEBUG_MODE
        qDebug() << sqlString;
#endif
        return sqlString;
    case 3:
        sqlString = QString("select * from %1 where Time >= %2 and Time <= %3 and ((ParameterName = '%4' and SignalID = %5) "\
                            "or (ParameterName = '%6' and SignalID = %7) or (ParameterName = '%8' and SignalID = %9)) order by SerialNumber")\
                .arg(table).arg(beginTime).arg(endTime)\
                .arg(m_sqlCondition.at(0).parameterName).arg(m_sqlCondition.at(0).signalID)\
                .arg(m_sqlCondition.at(1).parameterName).arg(m_sqlCondition.at(1).signalID)\
                .arg(m_sqlCondition.at(2).parameterName).arg(m_sqlCondition.at(2).signalID);
#ifdef DEBUG_MODE
        qDebug() << sqlString;
#endif
        return sqlString;
    case 4:
        sqlString = QString("select * from %1 where Time >= %2 and Time <= %3 and ((ParameterName = '%4' and SignalID = %5) "\
                            "or (ParameterName = '%6' and SignalID = %7) or (ParameterName = '%8' and SignalID = %9) " \
                            "or (ParameterName = '%10' and SignalID = %11)) order by SerialNumber")\
                .arg(table).arg(beginTime).arg(endTime)\
                .arg(m_sqlCondition.at(0).parameterName).arg(m_sqlCondition.at(0).signalID)\
                .arg(m_sqlCondition.at(1).parameterName).arg(m_sqlCondition.at(1).signalID)\
                .arg(m_sqlCondition.at(2).parameterName).arg(m_sqlCondition.at(2).signalID)\
                .arg(m_sqlCondition.at(3).parameterName).arg(m_sqlCondition.at(3).signalID);
#ifdef DEBUG_MODE
        qDebug() << sqlString;
#endif
        return sqlString;
    case 5:
        sqlString = QString("select * from %1 where Time >= %2 and Time <= %3 and ((ParameterName = '%4' and SignalID = %5) "\
                            "or (ParameterName = '%6' and SignalID = %7) or (ParameterName = '%8' and SignalID = %9)" \
                            "or (ParameterName = '%10' and SignalID = %11) or (ParameterName = '%12' and SignalID = %13)) order by SerialNumber")\
                .arg(table).arg(beginTime).arg(endTime)\
                .arg(m_sqlCondition.at(0).parameterName).arg(m_sqlCondition.at(0).signalID)\
                .arg(m_sqlCondition.at(1).parameterName).arg(m_sqlCondition.at(1).signalID)\
                .arg(m_sqlCondition.at(2).parameterName).arg(m_sqlCondition.at(2).signalID)\
                .arg(m_sqlCondition.at(3).parameterName).arg(m_sqlCondition.at(3).signalID)\
                .arg(m_sqlCondition.at(4).parameterName).arg(m_sqlCondition.at(4).signalID);
#ifdef DEBUG_MODE
        qDebug() << sqlString;
#endif
        return sqlString;
    case 6:
        sqlString = QString("select * from %1 where Time >= %2 and Time <= %3 and ((ParameterName = '%4' and SignalID = %5) "\
                            "or (ParameterName = '%6' and SignalID = %7) or (ParameterName = '%8' and SignalID = %9)" \
                            "or (ParameterName = '%10' and SignalID = %11) or (ParameterName = '%12' and SignalID = %13)"\
                            "or (ParameterName = '%14' and SignalID = %15)) order by SerialNumber")\
                .arg(table).arg(beginTime).arg(endTime)\
                .arg(m_sqlCondition.at(0).parameterName).arg(m_sqlCondition.at(0).signalID)\
                .arg(m_sqlCondition.at(1).parameterName).arg(m_sqlCondition.at(1).signalID)\
                .arg(m_sqlCondition.at(2).parameterName).arg(m_sqlCondition.at(2).signalID)\
                .arg(m_sqlCondition.at(3).parameterName).arg(m_sqlCondition.at(3).signalID)\
                .arg(m_sqlCondition.at(4).parameterName).arg(m_sqlCondition.at(4).signalID)\
                .arg(m_sqlCondition.at(5).parameterName).arg(m_sqlCondition.at(5).signalID);
#ifdef DEBUG_MODE
        qDebug() << sqlString;
#endif
        return sqlString;
    default:
        return NULL;
    }
}


unsigned int DataTableWidget::GetParameterID(int bmu, QString par)
{
    //BMS
    if ((par == BMS_POLL_GLOBAL_INFO) && (bmu == -1))
        return SIG_0x4200;
    else if (((par == BMS_PACK_VOLT) && (bmu == -1)) || ((par == BMS_PACK_CURR) && (bmu == -1)) ||\
             ((par == BMS_AMBIENT_TEMP_OUT) && (bmu == -1)) || ((par == BMS_SOC) && (bmu == -1)))
        return SIG_0x4210;
    else if (((par == BMS_PACK_PWR) && (bmu == -1)) || ((par == BMS_AMBIENT_TEMP_IN) && (bmu == -1)))
        return SIG_0x18FF02C0;
    else if (((par == BMS_MAX_CHG_CURR) && (bmu == -1)) || ((par == BMS_MAX_DISCHG_CURR) && (bmu == -1)))
        return SIG_0x4220;
    else if (((par == BMS_MAX_CELL_VLOT) && (bmu == -1)) || ((par == BMS_MIN_CELL_VOLT) && (bmu == -1)) ||\
             ((par == BMS_MAX_CV_NO) && (bmu == -1)) || ((par == BMS_MIN_CV_NO) && (bmu == -1)))
        return SIG_0x4230;
    else if (((par == BMS_MAX_CELL_TEMP) && (bmu == -1)) || ((par == BMS_MIN_CELL_TEMP) && (bmu == -1)) ||\
             ((par == BMS_MAX_CT_NO) && (bmu == -1)) || ((par == BMS_MIN_CT_NO) && (bmu == -1)))
        return SIG_0x4240;
    else if (((par == BMS_MAX_MODULE_CV) && (bmu == -1)) || ((par == BMS_MIN_MODULE_CV) && (bmu == -1)) ||\
             ((par == BMS_MAX_MCV_NO) && (bmu == -1)) || ((par == BMS_MIN_MCV_NO) && (bmu == -1)))
        return SIG_0x4260;
    else if (((par == BMS_MAX_MODULE_CT) && (bmu == -1)) || ((par == BMS_MIN_MOUDLE_CT) && (bmu == -1)) ||\
             ((par == BMS_MAX_MCT_NO) && (bmu == -1)) || ((par == BMS_MIN_MCT_NO) && (bmu == -1)))
        return SIG_0x4270;
    else if (((par == BMS_BASIC_STATUS) && (bmu == -1)) || ((par == BMS_ERR_VOLT_SENSOR) && (bmu == -1)) ||\
             ((par == BMS_ERR_TEMP_SENSOR) && (bmu == -1)) || ((par == BMS_ERR_INN_COM) && (bmu == -1)) ||\
             ((par == BMS_ERR_CHRG_VOLT_HIGH) && (bmu == -1)) || ((par == BMS_ERR_WIRE_INVERSED) && (bmu == -1)) ||\
             ((par == BMS_ERR_RELAY_STICKY) && (bmu == -1)) || ((par == BMS_ALM_CELL_VOLT_LOW) && (bmu == -1)) ||\
             ((par == BMS_ALM_CELL_VOLT_HIGH) && (bmu == -1)) || ((par == BMS_ALM_PACK_VOLT_LOW) && (bmu == -1)) ||\
             ((par == BMS_ALM_PACK_VOLT_HIGH) && (bmu == -1)) || ((par == BMS_ALM_CHRG_TEMP_LOW) && (bmu == -1)) ||\
             ((par == BMS_ALM_CHRG_TEMP_HIGH) && (bmu == -1)) || ((par == BMS_ALM_DISCHRG_TEMP_LOW) && (bmu == -1)) ||\
             ((par == BMS_ALM_DISCHRG_TEMP_HIGH) && (bmu == -1)) || ((par == BMS_ALM_CHRG_CURR_HIGH) && (bmu == -1)) ||\
             ((par == BMS_ALM_DISCHRG_CURR_HIGH) && (bmu == -1)) || ((par == BMS_ALM_MODULE_VOLT_LOW) && (bmu == -1)) ||\
             ((par == BMS_ALM_MODULE_VOLT_HIGH) && (bmu == -1)) || ((par == BMS_P_CELL_VOLT_LOW) && (bmu == -1)) ||\
             ((par == BMS_P_CELL_VOLT_HIGH) && (bmu == -1)) || ((par == BMS_P_PACK_VOLT_LOW) && (bmu == -1)) ||\
             ((par == BMS_P_PACK_VOLT_HIGH) && (bmu == -1)) || ((par == BMS_P_CHRG_TEMP_LOW) && (bmu == -1)) ||\
             ((par == BMS_P_CHRG_TEMP_HIGH) && (bmu == -1)) || ((par == BMS_P_DISCHRG_TEMP_LOW) && (bmu == -1)) ||\
             ((par == BMS_P_DISCHRG_TEMP_HIGH) && (bmu == -1)) || ((par == BMS_P_CHRG_CURR_HIGH) && (bmu == -1)) ||\
             ((par == BMS_P_DISCHRG_CURR_HIGH) && (bmu == -1)) || ((par == BMS_P_MODULE_VOLT_LOW) && (bmu == -1)) ||\
             ((par == BMS_P_MODULE_VOLT_HIGH) && (bmu == -1)))
        return SIG_0x4250;
    else if (((par == BMS_FORCE_CHRG_ST) && (bmu == -1)) || ((par == BMS_POSI_RLY_ST) && (bmu == -1)) ||\
             ((par == BMS_NEG_RLY_ST) && (bmu == -1)) || ((par == BMS_RLY_STICKY) && (bmu == -1)) || ((par == BMS_ALM_ST) && (bmu == -1)))
        return SIG_0x18FF02A0;
    else if (((par == BMS_FATAL_BMU_SENSOR) && (bmu == -1)) || ((par == BMS_FATAL_BMU_AFE) && (bmu == -1)) ||\
             ((par == BMS_FATAL_BMU_CV) && (bmu == -1)) || ((par == BMS_FATAL_BMU_VT) && (bmu == -1)) ||\
             ((par == BMS_FATAL_HVCU_COM) && (bmu == -1)) || ((par == BMS_FATAL_HVCU_SENSOR) && (bmu == -1)))
        return SIG_0x18FF04A0;
    else if (((par == BMS_CHRG_FORBIDEN_MARK) && (bmu == -1)) || ((par == BMS_DISCHRG_FORBIDEN_MARK) && (bmu == -1)))
        return SIG_0x4280;
    else if ((par == BMS_SLEEP_CTRL) && (bmu == -1))
        return SIG_0x8200;
    else if (((par == BMS_CHRG_EN) && (bmu == -1)) || ((par == BMS_DISCHRG_EN) && (bmu == -1)))
        return SIG_0x8210;
    else if ((par == BMS_RELAY_FORCE_BREAK) && (bmu == -1))
        return SIG_0x8220;
    //BMU
    else if (((par == BMU_AFE_SAMPLE) && (bmu != -1)) || ((par == BMU_AFE_FAULT) && (bmu != -1)) || ((par == BMU_OWD_ST) && (bmu != -1)) ||\
             ((par == BMU_LV1_CELL_VOLT_LOW) && (bmu != -1)) || ((par == BMU_LV1_CELL_VOLT_HIGH) && (bmu != -1)) || ((par == BMU_LV1_CELL_VOLT_DIFF) && (bmu != -1)) ||\
             ((par == BMU_LV1_MODULE_VOLT_LOW) && (bmu != -1)) || ((par == BMU_LV1_MODULE_VOLT_HIGH) && (bmu != -1)) || ((par == BMU_LV1_AMBIENT_TEMP_LOW) && (bmu != -1)) ||\
             ((par == BMU_LV1_AMBIENT_TEMP_HIGH) && (bmu != -1)) || ((par == BMU_LV1_CHRG_TEMP_LOW) && (bmu != -1)) || ((par == BMU_LV1_CHRG_TEMP_HIGH) && (bmu != -1)) ||\
             ((par == BMU_LV1_DISCHRG_TEMP_LOW) && (bmu != -1)) || ((par == BMU_LV1_DISCHRG_TEMP_HIGH) && (bmu != -1)) || ((par == BMU_LV2_CELL_VOLT_LOW) && (bmu != -1)) ||\
             ((par == BMU_LV2_CELL_VOLT_HIGH) && (bmu != -1)) || ((par == BMU_LV2_CELL_VOLT_DIFF) && (bmu != -1)) || ((par == BMU_LV2_MODULE_VOLT_LOW) && (bmu != -1)) ||\
             ((par == BMU_LV2_MODULE_VOLT_HIGH) && (bmu != -1)) || ((par == BMU_LV2_AMBIENT_TEMP_LOW) && (bmu != -1)) || ((par == BMU_LV2_AMBIENT_TEMP_HIGH) && (bmu != -1)) ||\
             ((par == BMU_LV2_CHRG_TEMP_LOW) && (bmu != -1)) || ((par == BMU_LV2_CHRG_TEMP_HIGH) && (bmu != -1)) ||\
             ((par == BMU_LV2_DISCHRG_TEMP_LOW) && (bmu != -1)) || ((par == BMU_LV2_DISCHRG_TEMP_HIGH) && (bmu != -1)))
        return SIG_0x18FF00B0 + bmu;
    else if (((par == BMU_SOC) && (bmu != -1)) || ((par == BMU_DIFF_CELL_VOLT) && (bmu != -1)) || ((par == BMU_DIFF_CELL_TEMP) && (bmu != -1)))
        return SIG_0x18FF01B0 + bmu;
    else if (((par == BMU_MODULE_VOLT) && (bmu != -1)) || ((par == BMU_BOARD_TEMP) && (bmu != -1)))
        return SIG_0x18FF02B0 + bmu;
    else if (((par == BMU_MAX_CELL_VOLT) && (bmu != -1)) || ((par == BMU_MIN_CELL_VOLT) && (bmu != -1)) || ((par == BMU_AVG_CELL_VOLT) && (bmu != -1)) ||\
             ((par == BMU_MAX_CV_NO) && (bmu != -1)) || ((par == BMU_MIN_CV_NO) && (bmu != -1)))
        return SIG_0x18FF10B0 + bmu;
    else if (((par == BMU_MAX_CELL_TEMP) && (bmu != -1)) || ((par == BMU_MIN_CELL_TEMP) && (bmu != -1)) || ((par == BMU_AVG_CELL_TEMP) && (bmu != -1)) ||\
             ((par == BMU_MAX_CT_NO) && (bmu != -1)) || ((par == BMU_MIN_CT_NO) && (bmu != -1)))
        return SIG_0x18FF20B0 + bmu;
    else if (((par == BMU_CELL_BAL_MODE) && (bmu != -1)) || ((par == BMU_CELL_BAL_ST) && (bmu != -1)) || ((par.left(4) == STRING_BMU_CELL_IN_BAL) && (bmu != -1)))
        return SIG_0x18FF30B0 + bmu;
    else if (((par == BMU_CELL_VOLT_0) && (bmu != -1)) || ((par == BMU_CELL_VOLT_1) && (bmu != -1)) ||\
             ((par == BMU_CELL_VOLT_2) && (bmu != -1)) || ((par == BMU_CELL_VOLT_3) && (bmu != -1)))
        return SIG_0x18FF40B0 + bmu;
    else if (((par == BMU_CELL_VOLT_4) && (bmu != -1)) || ((par == BMU_CELL_VOLT_5) && (bmu != -1)) ||\
             ((par == BMU_CELL_VOLT_6) && (bmu != -1)) || ((par == BMU_CELL_VOLT_7) && (bmu != -1)))
        return SIG_0x18FF41B0 + bmu;
    else if (((par == BMU_CELL_VOLT_8) && (bmu != -1)) || ((par == BMU_CELL_VOLT_9) && (bmu != -1)) ||\
             ((par == BMU_CELL_VOLT_10) && (bmu != -1)) || ((par == BMU_CELL_VOLT_11) && (bmu != -1)))
        return SIG_0x18FF42B0 + bmu;
    else if (((par == BMU_CELL_VOLT_12) && (bmu != -1)) || ((par == BMU_CELL_VOLT_13) && (bmu != -1)) ||\
             ((par == BMU_CELL_VOLT_14) && (bmu != -1)) || ((par == BMU_CELL_VOLT_15) && (bmu != -1)))
        return SIG_0x18FF43B0 + bmu;
    else if (((par.left(7) == STRING_BMU_CELL_TEMP) && (bmu != -1)))
        return SIG_0x18FF50B0 + bmu;
    else if (((par == BMU_CELL_AH) && (bmu != -1)) || ((par == BMU_CELL_RATE_VOLT) && (bmu != -1)) ||\
             ((par == BMU_CELL_NUM) && (bmu != -1)) || ((par == BMU_TEMP_NUM) && (bmu != -1)))
        return SIG_0x18FF60B0 + bmu;
    else
        return 0;
}


UINT DataTableWidget::GetTimeDuration(UINT beginTime, UINT durationNumber)
{
    UINT endTime = 0;
    if ((beginTime > 0) && (durationNumber > 0))
    {
        switch (m_timeUnit->currentIndex())
        {
        case 0:
            endTime = beginTime + durationNumber * 1;
            return endTime;
        case 1:
            endTime = beginTime + durationNumber * 60;
            return endTime;
        case 2:
            endTime = beginTime + durationNumber * 3600;
            return endTime;
        case 3:
            endTime = beginTime + durationNumber * 86400;
            return endTime;
        default :
            return 0;
        }
    }
    else
    {
        QMessageBox::warning(NULL, "提示", "时间设置错误");
        return 0;
    }
}


void DataTableWidget::AddSignal()
{
    int i = 0;
    bool existFlag = false;
    QTreeWidgetItemIterator itemIterator(m_signalTree);
    QString signalModule = NULL;
    QString signalName = NULL;
    QTableWidgetItem *moduleItem = NULL;
    QTableWidgetItem *signalItem = NULL;
    QString BMUNumber;
    SQLCondition addNode;
    UINT signalID = 0;

    while (*itemIterator)
    {
        if ((*itemIterator)->checkState(0) == Qt::Checked)
        {
            BMUNumber = QString("-1");
            signalName = (*itemIterator)->text(0);
            QTreeWidgetItem *parentItem = (*itemIterator)->parent();

            while (parentItem)
            {
                parentItem = parentItem->parent();
                if (parentItem)
                {
                    if (parentItem->text(0).left(3) == QString("BMU"))
                    {
                        signalModule = parentItem->text(0).left(3) + (*itemIterator)->parent()->text(0);
                        BMUNumber = (*itemIterator)->parent()->text(0);
                    }
                    else
                    {
                        signalModule = parentItem->text(0).left(3);
                    }
                }
            }

            signalID = GetParameterID(BMUNumber.toInt(), signalName);

            for (i=0; i<m_sqlCondition.size(); i++)
            {
                if ((m_sqlCondition.at(i).parameterName == signalName) &&\
                        (m_sqlCondition.at(i).signalID == signalID))
                {
                    existFlag = true;
                    break;
                }
            }

            if (!existFlag)
            {
                if (m_signalNumber >= MAX_SELECTED_SIGNAL_NUMBER)
                {
#ifdef DEBUG_MODE
                    qDebug() << m_signalNumber;
                    qDebug() << "Add Result :";
                    for (i=0; i<m_sqlCondition.size(); i++)
                    {
                        qDebug() << m_sqlCondition.at(i).parameterName << m_sqlCondition.at(i).signalID;
                    }
                    qDebug() << "";
#endif
                    QMessageBox::warning(NULL, "提示", "添加信号数超过上限");
                    return;
                }
                addNode.parameterName = signalName;
                addNode.signalID = signalID;
                m_sqlCondition.append(addNode);
                signalItem = new QTableWidgetItem(QString("%1").arg(signalName));
                moduleItem = new QTableWidgetItem(QString("%1").arg(signalModule));
                m_selectedTable->setItem(m_signalNumber, 0, signalItem);
                m_selectedTable->setItem(m_signalNumber, 1, moduleItem);

                m_signalNumber++;
            }
            existFlag = false;
        }
        itemIterator++;
    }
#ifdef DEBUG_MODE
    qDebug() << "Add Result :";
    for (i=0; i<m_sqlCondition.size(); i++)
    {
        qDebug() << m_sqlCondition.at(i).parameterName << m_sqlCondition.at(i).signalID;
    }
    qDebug() << "";
#endif
}


void DataTableWidget::DeleteSignal()
{
    int i = 0;
    int j = 0;
    int k = 0;
    QString signalName = NULL;
    QString signalModule = NULL;
    QList<int> rowList;
    int selectedRow;
    QString BUMNumber;
    UINT signalID = 0;

    QList<QTableWidgetSelectionRange>ranges = m_selectedTable->selectedRanges();

    int count = ranges.count();
    for(i=0; i<count; i++)
    {
        int topRow = ranges.at(i).topRow();
        int bottomRow = ranges.at(i).bottomRow();

        //获取并排序
        for (k=topRow; k<=bottomRow; k++)
        {
            rowList.append(k);
        }
    }

    qSort(rowList.begin(), rowList.end());   //必须先对所选行进行排序，然后从后面开始删除，否则会出现错误。

    while(!rowList.isEmpty())
    {
        selectedRow = rowList.takeLast();

        if ((m_selectedTable->item(selectedRow, 0) != 0) && (m_selectedTable->item(selectedRow, 1) != 0))
        {
            BUMNumber = QString("-1");
            signalName = m_selectedTable->item(selectedRow, 0)->text();
            signalModule = m_selectedTable->item(selectedRow, 1)->text();

            if (signalModule.length() == 4)
            {
                BUMNumber = signalModule.right(1);
            }

            signalID = GetParameterID(BUMNumber.toInt(), signalName);

            for (j=0; j<m_sqlCondition.size(); j++)
            {
                if ((signalName == m_sqlCondition.at(j).parameterName) &&\
                        (signalID == m_sqlCondition.at(j).signalID))
                {
                    m_sqlCondition.removeAt(j);
                }
            }

            m_selectedTable->removeRow(selectedRow);
            m_signalNumber--;

            QTreeWidgetItemIterator it(m_signalTree);   //取消信号选择表中对应的选中项
            if (BUMNumber == QString("-1"))
            {
                while (*it)
                {
                    if (((*it)->text(0) == signalName))
                        (*it)->setCheckState(0, Qt::Unchecked);
                    ++it;
                }
            }
            else
            {
                while (*it)
                {
                    if (((*it)->text(0) == signalName) && ((*it)->parent()->text(0) == BUMNumber))
                        (*it)->setCheckState(0, Qt::Unchecked);
                    ++it;
                }
            }
        }
    }

    if (m_signalNumber < MAX_SELECTED_SIGNAL_NUMBER)
    {
        m_selectedTable->setRowCount(MAX_SELECTED_SIGNAL_NUMBER);
    }
    else
    {
        m_selectedTable->setRowCount(m_signalNumber);
    }
#ifdef DEBUG_MODE
    qDebug() << "Delete Result :";
    for (i=0; i<m_sqlCondition.size(); i++)
    {
        qDebug() << m_sqlCondition.at(i).parameterName << m_sqlCondition.at(i).signalID;
    }
    qDebug() << "";
#endif
}


QString DataTableWidget::GetChartString(QString table, UINT beginTime, UINT endTime, float value, QString condition)
{
    int size = m_sqlCondition.size();
    QString sqlString = NULL;

    switch(size)
    {
    case 0:
        QMessageBox::warning(NULL, "提示", "请添加需要查询的参数！");
        return NULL;
    case 1:
        if (m_conditionFlag->isChecked())
        {
            sqlString = QString("select Time, Value from %1 where Time >= %2 and Time <= %3 and (ParameterName = '%4' and SignalID = %5) and Value %6 %7 order by SerialNumber")\
                    .arg(table).arg(beginTime).arg(endTime)\
                    .arg(m_sqlCondition.at(0).parameterName).arg(m_sqlCondition.at(0).signalID).arg(condition).arg(value);
        }
        else
        {
            sqlString = QString("select Time, Value from %1 where Time >= %2 and Time <= %3 and (ParameterName = '%4' and SignalID = %5) order by SerialNumber")\
                    .arg(table).arg(beginTime).arg(endTime)\
                    .arg(m_sqlCondition.at(0).parameterName).arg(m_sqlCondition.at(0).signalID).arg(condition).arg(value);
        }
#ifdef DEBUG_MODE
        qDebug() << sqlString;
#endif
        return sqlString;
    default:
        QMessageBox::warning(NULL, "提示", "所选参数过多（请只设置一个参数）！");
        return NULL;
    }
}


void DataTableWidget::CreateHistoryChart()
{
    QList<HistoryChartNode> chartData;
    HistoryChartNode node;
    QString selectedTable = NULL;
    UINT baginUnixTime = 0;
    QString timeString = m_beginTime->text();
    QDateTime dateTime = QDateTime::fromString(timeString, "yyyy-MM-dd hh:mm:ss");
    baginUnixTime = dateTime.toTime_t();
    UINT durationNumber = m_duration->text().toUInt();
    UINT endUnixTime = GetTimeDuration(baginUnixTime, durationNumber);
    float queryValue = m_value->text().toFloat();
    QString queryCondition = m_condition->currentText();
    QString widgetName = NULL;

    if (endUnixTime > 0)
    {
        if (m_selectTable->currentIndex() == 0)
        {
            selectedTable = RECENT_RECORD;
        }
        else
        {
            selectedTable = HISTORY_RECORD;
        }

        if (!m_connectionFlag)
        {
            if (CreateDataTableSQLConnection() != -1)
            {
                m_connectionFlag = true;
            }
            else
            {
                return;
            }
        }

        QSqlQuery query = QSqlQuery(m_dataTableDB);
        QString sqlLine = GetChartString(selectedTable, baginUnixTime, endUnixTime, queryValue, queryCondition);

        if (sqlLine != NULL)
        {
            query.exec(sqlLine);
            if (!query.lastError().isValid())
            {
                while(query.next())
                {
                    node.time = query.value(0).toUInt();
                    node.value = query.value(1).toFloat();
                    chartData.append(node);
                }

                if (m_conditionFlag->isChecked())
                {
                    widgetName = QString("%1 开始时间:%2 时长:%3%4 值:%5%6").arg(m_sqlCondition.at(0).parameterName).arg(timeString)\
                            .arg(m_duration->text()).arg(m_timeUnit->currentText()).arg(m_condition->currentText()).arg(m_value->text());

                }
                else
                {
                    widgetName = QString("%1 开始时间:%2 时长:%3%4").arg(m_sqlCondition.at(0).parameterName).arg(timeString)\
                            .arg(m_duration->text()).arg(m_timeUnit->currentText());
                }

                m_historyChartWidget = new HistoryChartWidget(chartData, widgetName);
            }
            else
            {
                QMessageBox::warning(NULL, "错误", QString("数据库查询失败！\n") + query.lastError().text(),
                                     QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                m_connectionFlag = false;
                return;
            }
        }
    }
}
