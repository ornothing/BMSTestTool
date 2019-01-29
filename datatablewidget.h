#ifndef DATATABLEWIDGET_H
#define DATATABLEWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QGridLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QTableWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include "signaltreewidget.h"
#include "widgetdatastructure.h"
#include "historychart.h"


class DataTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataTableWidget(QWidget *parent = 0);
    ~DataTableWidget();

    QGridLayout *m_dataTableLayout;
    QGroupBox *m_dataTableGroup;

    /** 设置 **/
    QGridLayout *m_dataTableSelectLayout;

    //信号选择
    SignalTreeWidget *m_signalTree;

    //已选信号
    QTableWidget *m_selectedTable;
    void BuildSelectedSignalTable();

    //控制模块
    void BuildControlModule();
    QGroupBox *m_addGroup;
    QGroupBox *m_timeGroup;
    QGridLayout *m_addLayout;
    QGridLayout *m_timeLayout;
    QPushButton *m_addButton;
    QPushButton *m_deleteButton;
    QCheckBox *m_selectAll;
    QComboBox *m_selectTable;
    QLineEdit *m_beginTime;
    QLineEdit *m_duration;
    QComboBox *m_timeUnit;
    QPushButton *m_searchButton;
    QLineEdit *m_value;
    QComboBox *m_condition;
    QCheckBox *m_conditionFlag;
    QPushButton *m_drawChartButton;

    QTableView *m_tableView;
    QSqlQueryModel *m_dataModel;
    QSqlDatabase m_dataTableDB;
    int CreateDataTableSQLConnection();

    QList<SQLCondition> m_sqlCondition;
    HistoryChartWidget *m_historyChartWidget;

    bool m_connectionFlag;
    int m_signalNumber;
    void InitSlot();
    UINT GetTimeDuration(UINT beginTime, UINT durationNumber);
    QString GetTableString(QString table, UINT beginTime, UINT endTime, float value, QString condition);
    QString GetChartString(QString table, UINT beginTime, UINT endTime, float value, QString condition);
    unsigned int GetParameterID(int bmu, QString par);

public slots:
    void AddSignal();
    void DeleteSignal();
    void SearchSignal();
    void CreateHistoryChart();
};


#endif // DATATABLEWIDGET_H
