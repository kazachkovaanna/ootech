#include "graphicsline.h"

#include <QPainter>
#include <QPainterPath>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

GraphicsLine::GraphicsLine(QGraphicsItem *parent)
    : AbstractItem(parent)
{
    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);

    setZValue(50);
}

QRectF GraphicsLine::boundingRect() const
{
    return shape().boundingRect();
}

void GraphicsLine::setPoints(const QList<QPointF> &points)
{
    prepareGeometryChange();
    _points = points;

    update();
}

QPainterPath GraphicsLine::shape() const
{
    QPainterPath painterPath;
    if (!_points.isEmpty()) {
        painterPath.moveTo(_points[0]);
        QPointF end = _points.last();
        for (int i = 1; i < _points.size() - 1; i++) {
            painterPath.quadTo(_points[i], end);
        }
    }

    return painterPath;
}
