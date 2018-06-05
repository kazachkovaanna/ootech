#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <QBrush>
#include <QGraphicsObject>
#include <QList>
#include <QPainter>
#include <QPen>
#include <QPointF>

class AbstractItem : public QGraphicsObject {
public:
    AbstractItem(QGraphicsItem* parent = nullptr);

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    virtual QRectF boundingRect() const override;

    inline QPen currentPen() const { return isSelected() ? _selectedPen : _pen; }
    inline QBrush currentBrush() const { return isSelected() ? _selectedBrush : _brush; }

    inline QString getUuid() const { return _uuid; }

    virtual QPointF getCenter() const = 0;
    virtual void showSettings() = 0;

public:
    static void setPen(const QPen& pen);
    static void setSelectedPen(const QPen& pen);
    static void setBrush(const QBrush& brush);
    static void setSelectedBrush(const QBrush& brush);
    static void setFont(const QFont& font);

    inline static QPen pen() { return _pen; }
    inline static QPen selectedPen() { return _selectedPen; }
    inline static QBrush brush() { return _brush; }
    inline static QBrush selectedBrush() { return _selectedBrush; }
    inline static QFont font() { return _font; }

protected:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

protected:
    static QPen _pen;
    static QPen _selectedPen;

    static QBrush _brush;
    static QBrush _selectedBrush;

    static QFont _font;

    QString _uuid;
};

#endif // ABSTRACTITEM_H
