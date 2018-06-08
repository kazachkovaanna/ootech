#include "graphicsline.h"
#include <graphicvertex.h>
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
    , _edge(nullptr)
{
    setZValue(450);
}

void GraphicsLine::setStart(GraphicVertex* start, bool changeControlPoint)
{
    if (_start) {
        disconnect(_start, &QGraphicsObject::xChanged, this, &GraphicsLine::fullUpdate);
        disconnect(_start, &QGraphicsObject::yChanged, this, &GraphicsLine::fullUpdate);
    }

    prepareGeometryChange();
    _start = start;

    if (_start) {
        _startUuid = _start->getUuid();
        connect(_start, &QGraphicsObject::xChanged, this, &GraphicsLine::fullUpdate);
        connect(_start, &QGraphicsObject::yChanged, this, &GraphicsLine::fullUpdate);
    }

    if (_start && _end && changeControlPoint) {
        _controlPoint = (_start->getCenter() + _end->getCenter()) / 2;
    }

    update();
}

void GraphicsLine::setEnd(GraphicVertex* end,  bool changeControlPoint)
{
    if (_end) {
        disconnect(_end, &QGraphicsObject::xChanged, this, &GraphicsLine::fullUpdate);
        disconnect(_end, &QGraphicsObject::yChanged, this, &GraphicsLine::fullUpdate);
    }

    prepareGeometryChange();
    _end = end;

    if (_end) {
        _endUuid = _end->getUuid();
        connect(_end, &QGraphicsObject::xChanged, this, &GraphicsLine::fullUpdate);
        connect(_end, &QGraphicsObject::yChanged, this, &GraphicsLine::fullUpdate);
    }

    if (_start && _end && changeControlPoint) {
        _controlPoint = (_start->getCenter() + _end->getCenter()) / 2;
    }

    update();
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
    if (_edge)
        _edgeUuid = _edge->getUuid();

    update();
}

void GraphicsLine::showSettings()
{
    GraphicLineDialog d;
    d.setTooltip(toolTip());
    if (_edge)
        d.setCost(_edge->getData());

    if (GraphicLineDialog::Accepted == d.exec()) {
        setToolTip(d.getTooltip());
        if (_edge)
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

QDataStream& operator<<(QDataStream& stream, GraphicsLine* line)
{
    stream.resetStatus();

    stream << line->_uuid;
    stream << line->_startUuid;
    stream << line->_endUuid;
    stream << line->_edgeUuid;
    stream << line->_controlPoint;
    stream << line->toolTip();

    return stream;
}

QDataStream &operator>>(QDataStream &stream, GraphicsLine *&line)
{
    stream.startTransaction();

    line = new GraphicsLine;
    stream >> line->_uuid;
    stream >> line->_startUuid;
    stream >> line->_endUuid;
    stream >> line->_edgeUuid;
    stream >> line->_controlPoint;
    QString tooltip;
    stream >> tooltip;
    line->setToolTip(tooltip);

    if (!stream.commitTransaction()) {

    }

    return stream;
}
