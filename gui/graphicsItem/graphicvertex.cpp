#include "graphicvertex.h"

#include <QCursor>
#include <QGraphicsSceneEvent>
#include <QGraphicsScene>
#include <QWidget>
#include <QDebug>

GraphicVertex::GraphicVertex(QGraphicsItem *parent)
    : AbstractItem(parent)
    , _rect(0, 0, 30, 30)
{
    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);

    setZValue(100);

    setBrush(true);
}

QRectF GraphicVertex::boundingRect() const
{
    return _rect;
}

QPainterPath GraphicVertex::shape() const
{
    QPainterPath path;
    path.addEllipse(_rect);

    return path;
}
