#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <QGraphicsObject>
#include <QPen>
#include <QBrush>
#include <QList>
#include <QPointF>
#include <QPainter>

class AbstractItem : public QGraphicsObject
{
public:
    AbstractItem(QGraphicsItem* parent = nullptr);

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    inline bool itemSelected() const { return _itemSelected; }
    void setItemSelected(bool selected);

    inline bool hasBrush() const { return _hasBrush; }
    void setBrush(bool brush);

    inline QPen pen() const { return itemSelected() ? _selectedPen : _pen; }
    inline QBrush brush() const { return hasBrush() ? itemSelected() ? _selectedBrush : _brush : QBrush(Qt::NoBrush); }


protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void clickMouseEvent(QGraphicsSceneMouseEvent *event);

protected:
    bool _itemSelected;
    bool _hasBrush;
    QGraphicsItem* _selection;
    QPen _pen;
    QPen _selectedPen;
    QBrush _brush;
    QBrush _selectedBrush;
    QPointF _pressPosition;
};

#endif // ABSTRACTITEM_H
