#include <QGraphicsSceneMoveEvent>
#include <QUuid>

#include "abstractitem.h"

AbstractItem::AbstractItem(QGraphicsItem* parent)
    : QGraphicsObject(parent)
    , _itemSelected(false)
    , _pen(Qt::black, 2)
    , _selectedPen(Qt::DashLine)
    , _brush(Qt::gray)
    , _selectedBrush(Qt::lightGray)
    , _uuid(QUuid::createUuid().toString())
{
    _selectedPen.setColor(QColor(255, 0, 0));
}

void AbstractItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawPath(shape());
}

QRectF AbstractItem::boundingRect() const
{
    return shape().boundingRect();
}

void AbstractItem::setItemSelected(bool selected)
{
    _itemSelected = selected;
    update();
}

void AbstractItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    _pressPosition = event->scenePos();
    event->accept();

    setItemSelected(true);
}

void AbstractItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    showSettings();
}
