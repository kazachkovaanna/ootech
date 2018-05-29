#ifndef GRAPHICVERTEX_H
#define GRAPHICVERTEX_H

#include "abstractitem.h"
#include <QPainter>

class GraphicVertex : public AbstractItem
{
public:
    GraphicVertex(QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

protected:
    QRectF _rect;
};

#endif // GRAPHICVERTEX_H
