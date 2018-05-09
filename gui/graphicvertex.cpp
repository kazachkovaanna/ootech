#include "graphicvertex.h"

GraphicVertex::GraphicVertex(QGraphicsItem *parent)
    :QGraphicsObject (parent), color(Qt::lightGray)
{
    setAcceptDrops(true);
}

QRectF GraphicVertex::boundingRect() const
{
    return QRectF(0., 0., 1., 1.);
}

void GraphicVertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-12, -12, 30, 30);
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QBrush(color));
    painter->drawEllipse(-15, -15, 30, 30);
}
