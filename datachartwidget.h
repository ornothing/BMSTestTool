#ifndef DATACHARTWIDGET_H
#define DATACHARTWIDGET_H

#include <QWidget>
#include <QChart>
#include <QLineSeries>
#include <QVector>
#include <QTimer>
#include <QValueAxis>
#include <QGridLayout>
#include <QPushButton>
#include <QTreeWidget>
#include <QGroupBox>
#include <QTableWidget>

#include "widgetdatastructure.h"
#include "chartview.h"
#include "callout.h"
#include "signaltreewidget.h"

using namespace QtCharts;

typedef struct
{
    QLineSeries *ChartSeries;
    QTimer *ChartTimer;
}SERIES_AND_TIMER;


class RealTimeDataChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RealTimeDataChartWidget(QWidget *parent = 0);
    virtual ~RealTimeDataChartWidget();

    void wheelEvent(QWheelEvent *event);

    QGridLayout *m_realTimeLayout;
    QGroupBox *m_realTimeGroup;

    /** 设置 **/
    void BuildRealTimeControlUI();
    QGridLayout *m_realTimeControlLayout;

    //信号选择
    SignalTreeWidget *m_signalTree;

    //已选信号
    QTableWidget *m_selectedTable;

    //控制模块
    QGroupBox *m_controlGroup;
    QGridLayout *m_controlLayout;
    QPushButton *m_addButton;
    QPushButton *m_deleteButton;
    QPushButton *m_cleanButton;
    QPushButton *m_stopButton;

    /** 图形显示 **/
    quint64 m_timeCount;
    int m_signalNumber;
    bool m_isCleaning;
    UINT m_lastTime;
    UINT m_unixTime;
    ChartView *m_chartView;
    QChart *m_chart;
    Callout *m_tip;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    QList<SERIES_AND_TIMER> m_seriesAndTimer;
    int m_maxY;
    int m_minY;
    QList<int> m_minYList;
    QList<int> m_maxYList;

    void UpdateChart(int signalNumber);
    void InitChart();
    void InitSlot();
    void GetYRange();
    bool GetBMSValueYRange(int signalNumber);
    bool GetBMSStatusYRange(int signalNumber);
    bool GetBMUValueYRange(int signalNumber);
    bool GetBMUStatusYRange(int signalNumber);

private:
    bool m_isStopping;
    int GetTimerInterval(int signalNumber);

public slots:
    void ControlButtonSlot();
    void TipSlot(QPointF position, bool isHovering);
    void AddSignal();
    void DeleteSignal();
    void CleanSignal();

private slots:
    void TimerSlot();
};


#endif // DATACHARTWIDGET_H
