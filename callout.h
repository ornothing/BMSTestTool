#ifndef CALLOUT_H
#define CALLOUT_H

#include <QChartGlobal>
#include <QGraphicsItem>
#include <QFont>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Callout : public QGraphicsItem
{
public:
    Callout(QChart *parent);
    ~Callout();

    void setText(const QString &text);
    void setAnchor(QPointF point);
    void updateGeometry();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    QString text;
    QRectF textRect;
    QRectF rect;
    QPointF anchor;
    QFont font;
    QChart *m_myChart;
};

#endif // CALLOUT_H
