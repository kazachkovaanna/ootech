#ifndef GRAPHICSLINE_H
#define GRAPHICSLINE_H

#include "abstractitem.h"

class GraphicsLine : public AbstractItem
{
public:
    GraphicsLine(QGraphicsItem* parent = nullptr);

    virtual QRectF boundingRect() const override;

    inline QList<QPointF> points() const { return _points; }
    void setPoints(const QList<QPointF>& points);

    virtual QPainterPath shape() const override;

protected:
    QList<QPointF> _points;
};

#endif // GRAPHICSLINE_H
