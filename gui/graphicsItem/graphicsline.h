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

    inline QList<Sence::Edge<int>*> getEdge() const { return _edges; }
    void setEdge(const QList<Sence::Edge<int>*>& edges);

    virtual void showSettings() override;

protected slots:
    void fullUpdate();

protected:
    AbstractItem* _start;
    AbstractItem* _end;
    QList<Sence::Edge<int>*> _edges;
};

#endif // GRAPHICSLINE_H
