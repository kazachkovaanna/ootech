#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <QBrush>
#include <QGraphicsObject>
#include <QList>
#include <QPainter>
#include <QPen>
#include <QPointF>

class AbstractItem : public QGraphicsObject {
    Q_OBJECT

public:
    AbstractItem(QGraphicsItem* parent = nullptr);

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    virtual QRectF boundingRect() const override;

    inline bool itemSelected() const { return _itemSelected; }
    void setItemSelected(bool selected);

    inline QPen pen() const { return itemSelected() ? _selectedPen : _pen; }
    inline QBrush brush() const { return itemSelected() ? _selectedBrush : _brush; }

    inline QString getUuid() const { return _uuid; }

    virtual QPointF getCenter() const = 0;
    virtual void showSettings() = 0;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

protected:
    bool _itemSelected;

    QPen _pen;
    QPen _selectedPen;

    QBrush _brush;
    QBrush _selectedBrush;

    QString _uuid;
};

#endif // ABSTRACTITEM_H
