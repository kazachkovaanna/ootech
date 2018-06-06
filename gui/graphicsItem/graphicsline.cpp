#include "graphicsline.h"
#include "graph.h"
#include "graphiclinedialog.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>

GraphicsLine::GraphicsLine(QGraphicsItem* parent)
    : AbstractItem(parent)
    , _start(nullptr)
    , _end(nullptr)
{
    setZValue(450);
}

void GraphicsLine::setStart(AbstractItem* start)
{
    if (_start) {
        disconnect(_start, &QGraphicsObject::xChanged, this, &GraphicsLine::fullUpdate);
        disconnect(_start, &QGraphicsObject::yChanged, this, &GraphicsLine::fullUpdate);
    }

    prepareGeometryChange();
    _start = start;
    update();

    if (_start) {
        connect(_start, &QGraphicsObject::xChanged, this, &GraphicsLine::fullUpdate);
        connect(_start, &QGraphicsObject::yChanged, this, &GraphicsLine::fullUpdate);
    }

    if (_start && _end) {
        _controlPoint = (_start->getCenter() + _end->getCenter()) / 2;
    }
}

void GraphicsLine::setEnd(AbstractItem* end)
{
    if (_end) {
        disconnect(_end, &QGraphicsObject::xChanged, this, &GraphicsLine::fullUpdate);
        disconnect(_end, &QGraphicsObject::yChanged, this, &GraphicsLine::fullUpdate);
    }

    prepareGeometryChange();
    _end = end;
    update();

    if (_end) {
        connect(_end, &QGraphicsObject::xChanged, this, &GraphicsLine::fullUpdate);
        connect(_end, &QGraphicsObject::yChanged, this, &GraphicsLine::fullUpdate);
    }

    if (_start && _end) {
        _controlPoint = (_start->getCenter() + _end->getCenter()) / 2;
    }
}

QPainterPath GraphicsLine::shape() const
{
    QPainterPath painterPath;

    if (!_start || !_end)
        return painterPath;

    painterPath.moveTo(_start->getCenter());
    painterPath.quadTo(_controlPoint, _end->getCenter());
    QPainterPathStroker stroker(Qt::NoPen);
    painterPath = stroker.createStroke(painterPath);

    if (_edge) {
        painterPath.addText(getCenter(), _font, QString::number(_edge->getData()));
    }

    return painterPath;
}

QPointF GraphicsLine::getCenter() const
{
    const double t = 0.5;
    const double _t = 1 - t;

    return qPow(_t, 2) * _start->getCenter() + 2 * t * _t * _controlPoint + qPow(t, 2) * _end->getCenter();
}

void GraphicsLine::setEdge(Sence::Edge<int>* edge)
{
    _edge = edge;
    update();
}

void GraphicsLine::showSettings()
{
    GraphicLineDialog d;
    d.setTooltip(toolTip());
    d.setCost(_edge->getData());

    if (GraphicLineDialog::Accepted == d.exec()) {
        setToolTip(d.getTooltip());
        _edge->setData(d.getCost());
        update();
    }
}

void GraphicsLine::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    _controlPoint = event->scenePos();
    update();
    AbstractItem::mouseMoveEvent(event);
}

void GraphicsLine::fullUpdate()
{
    prepareGeometryChange();
    update();
}
