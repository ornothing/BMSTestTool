#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>
#include <QRubberBand>

QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView
{
public:
    ChartView(QChart *chart, QWidget *parent = 0);
    ~ChartView();

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool isClicking;

    int xOld;
    int yOld;
};


#endif // CHARTVIEW_H
