#ifndef GRAPHICSLINE_H
#define GRAPHICSLINE_H

#include "abstractitem.h"

namespace Sence {
template <typename E>
class Edge;
}

class GraphicsLine : public AbstractItem {
    Q_OBJECT

public:
    GraphicsLine(QGraphicsItem* parent = nullptr);

    inline AbstractItem* start() const { return _start; }
    inline AbstractItem* end() const { return _end; }

    void setStart(AbstractItem* start);
    void setEnd(AbstractItem* end);

    virtual QPainterPath shape() const override;

    virtual QPointF getCenter() const override;

    inline Sence::Edge<int>* getEdge() const { return _edge; }
    void setEdge(Sence::Edge<int>* edge);

    virtual void showSettings() override;

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

protected slots:
    void fullUpdate();

protected:
    AbstractItem* _start;
    AbstractItem* _end;
    QPointF _controlPoint;
    Sence::Edge<int>* _edge;
};

#endif // GRAPHICSLINE_H
