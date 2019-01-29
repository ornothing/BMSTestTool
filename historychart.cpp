#include <QDateTime>
#include "historychart.h"

HistoryChartWidget::HistoryChartWidget(QList<HistoryChartNode> data, QString widgetName)
{
    m_historySeries = new QLineSeries();
    HistoryChartNode pointData;
    m_tip = NULL;
    int AxisX = 0;
    UINT minAxisX = 0;
    UINT maxAxisX = 10;
    float minAxisY = 0;
    float maxAxisY = 10;

    if (data.size() > 0)
    {
        minAxisX = data.first().time;
        maxAxisX = data.last().time;
        minAxisY = data.first().value;
        maxAxisY = data.first().value;
    }

    while(!data.isEmpty())
    {
        pointData = data.takeFirst();
        m_historySeries->append(pointData.time, pointData.value);

        if (pointData.value < minAxisY)
            minAxisY = pointData.value;
        if (pointData.value > maxAxisY)
            maxAxisY = pointData.value;
        AxisX ++;
    }

    InitChart(minAxisX, maxAxisX, minAxisY, maxAxisY);
    m_historySeries->setName(widgetName);
    connect(m_historySeries, SIGNAL(hovered(QPointF, bool)), this, SLOT(TipSlot(QPointF, bool)));
    m_historyChart = new QChart();
    m_historyChart->addSeries(m_historySeries);
    m_historyChart->createDefaultAxes();

    m_historyChart->setAxisX(m_axisX, m_historySeries);   //为chart设置X轴,并把轴附加到series线上
    m_historyChart->setAxisY(m_axisY, m_historySeries);   //为chart设置Y轴,并把轴附加到series线上

    m_historyuChartView = new ChartView(m_historyChart);
    m_historyuChartView->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(m_historyuChartView);
    resize(800, 600);
    show();
}


void HistoryChartWidget::InitChart(UINT minX, UINT maxX, float minY, float maxY)
{
    m_axisX = new QValueAxis();
    m_axisY = new QValueAxis();

    m_axisX->setRange(minX, maxX);    //设置范围
    m_axisX->setTickCount(10);       //设置多少格
    m_axisX->setMinorTickCount(1);   //设置每格小刻度线的数目

    m_axisX->setLabelFormat("%d");   //设置刻度的格式
    m_axisX->setGridLineVisible(true);   //网格线可见
    m_axisX->setTitleText("时间");

    m_axisY->setRange(minY, maxY);
    m_axisY->setGridLineVisible(true);
    m_axisY->setTickCount(10);
    m_axisY->setLabelFormat("%.2f");
    m_axisY->setMinorTickCount(4);
    m_axisY->setTitleText("值");
}


HistoryChartWidget::~HistoryChartWidget()
{
    m_historySeries->clear();
    delete m_historySeries;
    delete m_historyChart;
    delete m_historyuChartView;

    m_historySeries = NULL;
    m_historyChart = NULL;
    m_historyuChartView = NULL;
}


void HistoryChartWidget::TipSlot(QPointF position, bool isHovering)
{
    if (m_tip == 0)
        m_tip = new Callout(m_historyChart);

    if (isHovering)
    {
        QDateTime time= QDateTime::fromTime_t(position.x());
        QString timeString = time.toString("MM/dd hh:mm:ss");
        m_tip->setText(QString("X: %1 \nY: %2 \n%3").arg((UINT)(position.x())).arg(position.y()).arg(timeString));
        m_tip->setAnchor(position);
        m_tip->setZValue(11);  //该设置与图形的层次有关，值越大，越上层。
        m_tip->updateGeometry();
        m_tip->show();
    }
    else
    {
        m_tip->hide();
    }
}


void HistoryChartWidget::wheelEvent(QWheelEvent *event)
{
    if (m_historyChart != NULL)
    {
        if (event->angleDelta().y() > 0) {
            m_historyChart->zoom(1.1);
        } else {
            m_historyChart->zoom(0.9);
        }
    }

    QWidget::wheelEvent(event);
}
