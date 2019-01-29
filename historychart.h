#ifndef HISTORYCHART_H
#define HISTORYCHART_H

#include <QMainWindow>
#include <QLineSeries>
#include <QChartView>
#include <QValueAxis>
#include <callout.h>
#include "chartview.h"
#include "historyrecorddefine.h"

using namespace QtCharts;

class HistoryChartWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit HistoryChartWidget(QList<HistoryChartNode> data, QString widgetName);
    ~HistoryChartWidget();
    void InitChart(UINT minX, UINT maxX, float minY, float maxY);

    void wheelEvent(QWheelEvent *event);

    QLineSeries *m_historySeries;
    QChart *m_historyChart;
    ChartView *m_historyuChartView;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    Callout *m_tip;

private slots:
    void TipSlot(QPointF position, bool isHovering);
};

#endif // HISTORYCHART_H
