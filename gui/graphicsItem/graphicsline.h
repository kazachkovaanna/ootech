#ifndef GRAPHICSLINE_H
#define GRAPHICSLINE_H

#include "abstractitem.h"

namespace Sence {
template <typename E>
class Edge;
}

class GraphicVertex;

class GraphicsLine : public AbstractItem {
    Q_OBJECT

public:
    GraphicsLine(QGraphicsItem* parent = nullptr);

    inline GraphicVertex* start() const { return _start; }
    inline GraphicVertex* end() const { return _end; }

    inline QString getStartUuid() const { return _startUuid; }
    inline QString getEndUuid() const { return _endUuid; }

    void setStart(GraphicVertex* start, bool changeControlPoint = true);
    void setEnd(GraphicVertex* end,  bool changeControlPoint = true);

    virtual QPainterPath shape() const override;

    virtual QPointF getCenter() const override;

    inline Sence::Edge<int>* getEdge() const { return _edge; }
    void setEdge(Sence::Edge<int>* edge);

    inline QString getEdgeUuid() const { return _edgeUuid; }

    virtual void showSettings() override;

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

protected slots:
    void fullUpdate();

    friend QDataStream& operator<<(QDataStream& stream, GraphicsLine* line);
    friend QDataStream& operator>>(QDataStream& stream, GraphicsLine*& line);

protected:
    GraphicVertex* _start;
    GraphicVertex* _end;

    QString _startUuid;
    QString _endUuid;

    QPointF _controlPoint;

    Sence::Edge<int>* _edge;

    QString _edgeUuid;
};

QDataStream& operator<<(QDataStream& stream, GraphicsLine* line);
QDataStream& operator>>(QDataStream& stream, GraphicsLine*& line);

#endif // GRAPHICSLINE_H
