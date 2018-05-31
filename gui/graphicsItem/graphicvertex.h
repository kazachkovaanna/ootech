#ifndef GRAPHICVERTEX_H
#define GRAPHICVERTEX_H

#include "abstractitem.h"

namespace Sence {
template <typename V>
class Vertex;
}

class GraphicVertex : public AbstractItem {
public:
    GraphicVertex(QGraphicsItem* parent = nullptr);

    virtual QPainterPath shape() const override;
    virtual QPointF getCenter() const override;

    inline Sence::Vertex<QString>* getVertex() const { return _vertex; }
    void setVertex(Sence::Vertex<QString>* vertex);

    virtual void showSettings() override;

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

protected:
    QRectF _rect;
    Sence::Vertex<QString>* _vertex;
};

#endif // GRAPHICVERTEX_H
