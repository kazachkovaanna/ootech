#include <QGraphicsSceneMoveEvent>
#include <QUuid>
#include <QStyleOptionGraphicsItem>

#include "abstractitem.h"

QPen AbstractItem::_pen(Qt::black);
QPen AbstractItem::_selectedPen(QBrush(Qt::red), 1, Qt::DashLine);
QBrush AbstractItem::_brush(Qt::gray);
QBrush AbstractItem::_selectedBrush(Qt::lightGray);
QFont AbstractItem::_font("Arial", 10);

AbstractItem::AbstractItem(QGraphicsItem* parent)
    : QGraphicsObject(parent)
    , _uuid(QUuid::createUuid().toString())
{
    setCursor(Qt::PointingHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void AbstractItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(currentPen());
    painter->setBrush(currentBrush());
    painter->drawPath(shape());
}

QRectF AbstractItem::boundingRect() const
{
    return shape().boundingRect();
}

void AbstractItem::setPen(const QPen &pen)
{
    _pen = pen;
}

void AbstractItem::setSelectedPen(const QPen &pen)
{
    _selectedPen = pen;
}

void AbstractItem::setBrush(const QBrush &brush)
{
    _brush = brush;
}

void AbstractItem::setSelectedBrush(const QBrush &brush)
{
    _selectedBrush = brush;
}

void AbstractItem::setFont(const QFont &font)
{
    _font = font;
}

void AbstractItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    QGraphicsObject::mousePressEvent(event);
}

void AbstractItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::PointingHandCursor);
    QGraphicsObject::mouseReleaseEvent(event);
}

void AbstractItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsObject::mouseDoubleClickEvent(event);
    showSettings();
}
