#include <QGraphicsSceneMoveEvent>

#include "abstractitem.h"

AbstractItem::AbstractItem(QGraphicsItem *parent)
    : QGraphicsObject(parent)
    , _itemSelected(false)
    , _hasBrush(false)
    , _selection(nullptr)
    , _pen(Qt::black)
    , _selectedPen(Qt::DashLine)
    , _brush(Qt::gray)
    , _selectedBrush(Qt::lightGray)
{
    _selectedPen.setColor(QColor(255,0,0));
}

void AbstractItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawPath(shape());
}

void AbstractItem::setItemSelected(bool selected)
{
    _itemSelected = selected;
    update();
}

void AbstractItem::setBrush(bool brush)
{
    _hasBrush = brush;
}

void AbstractItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    _pressPosition = event->scenePos();
    event->accept();
}

void AbstractItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (_pressPosition == event->scenePos()) {
        clickMouseEvent(event);
        return;
    }
}

void AbstractItem::clickMouseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)

    setItemSelected(true);
}
