#include "graphicsline.h"
#include "graph.h"
#include "graphiclinedialog.h"

#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPainterPath>

GraphicsLine::GraphicsLine(QGraphicsItem* parent)
    : AbstractItem(parent)
    , _start(nullptr)
    , _end(nullptr)
{
//    setCursor(Qt::OpenHandCursor);
//    setAcceptedMouseButtons(Qt::LeftButton);
    setFocus(Qt::MouseFocusReason);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable);

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
}

QPainterPath GraphicsLine::shape() const
{
    QPainterPath painterPath;

    if (!_start || !_end)
        return painterPath;

    painterPath.moveTo(_start->getCenter());
    painterPath.lineTo(_end->getCenter());

    if (!_edges.isEmpty()) {
        QString text;
        for (Sence::Edge<int>* e : _edges) {
            text += QString::number(e->getData()) + " ";
        }
        painterPath.addText(getCenter(), QFont(), text);
    }

    return painterPath;
}

QPointF GraphicsLine::getCenter() const
{
    return (_start->getCenter() + _end->getCenter()) / 2;
}

void GraphicsLine::setEdge(const QList<Sence::Edge<int>*>& edges)
{
    _edges = edges;
    update();
}

void GraphicsLine::showSettings()
{
    GraphicLineDialog d;
    d.setTooltip(toolTip());
    d.setCosts({ _edges[0]->getData() });

    if (GraphicLineDialog::Accepted == d.exec()) {
        setToolTip(d.getTooltip());
        _edges[0]->setData(d.getCosts()[0]);
        update();
    }
}

void GraphicsLine::fullUpdate()
{
    prepareGeometryChange();
    update();
}
