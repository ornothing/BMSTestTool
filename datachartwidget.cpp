#include "datachartwidget.h"
#include <QTreeWidgetItemIterator>
#include <QStringList>
#include <QString>
#include <QFont>
#include <QHeaderView>
#include <QMessageBox>
#include "databasedefine.h"


RealTimeDataChartWidget::RealTimeDataChartWidget(QWidget *parent) :
    QWidget(parent)
{
    m_timeCount = 0;
    m_signalNumber = 0;
    m_tip = NULL;
    m_chart = NULL;
    m_isStopping  = true;
    m_isCleaning = true;

    BuildRealTimeControlUI();

    m_realTimeLayout = new QGridLayout(this);
    m_realTimeLayout->addWidget(m_realTimeGroup, 0 ,0);

    m_realTimeLayout->setColumnStretch(0, 2);
    m_realTimeLayout->setColumnStretch(1, 7.5);
    InitSlot();
}


RealTimeDataChartWidget::~RealTimeDataChartWidget()
{
    delete m_realTimeControlLayout;
    delete m_controlLayout;
    m_realTimeControlLayout = NULL;
    m_controlLayout = NULL;
}


void RealTimeDataChartWidget::BuildRealTimeControlUI()
{
    int i = 0;
    m_realTimeGroup = new QGroupBox(this);
    m_realTimeControlLayout = new QGridLayout();

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
    m_selectedTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
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

    //控制模块
    m_controlGroup = new QGroupBox("信号控制", this);
    m_controlLayout = new QGridLayout();

    m_addButton = new QPushButton(this);
    m_deleteButton = new QPushButton(this);
    m_cleanButton = new QPushButton(this);
    m_stopButton = new QPushButton(this);
    m_addButton->setText("添加");
    m_deleteButton->setText("删除");
    m_cleanButton->setText("清除");
    m_stopButton->setText("开始");

    m_controlLayout->addWidget(m_addButton, 0, 0);
    m_controlLayout->addWidget(m_deleteButton, 0, 1);
    m_controlLayout->addWidget(m_stopButton, 1, 0);
    m_controlLayout->addWidget(m_cleanButton, 1, 1);
    m_controlGroup->setLayout(m_controlLayout);

    m_realTimeControlLayout->addWidget(m_signalTree, 0, 0);
    m_realTimeControlLayout->addWidget(m_selectedTable, 1, 0);
    m_realTimeControlLayout->addWidget(m_controlGroup, 2, 0);

    m_realTimeControlLayout->setRowStretch(0, 5);
    m_realTimeControlLayout->setRowStretch(1, 2);
    m_realTimeControlLayout->setRowStretch(2, 1);
    m_realTimeGroup->setLayout(m_realTimeControlLayout);
}


