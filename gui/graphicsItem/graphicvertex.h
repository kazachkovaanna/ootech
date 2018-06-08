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

    inline QString getVertexUuid() const { return _vertexUuid; }

    virtual QWidget* getSettingsForm() override;

    friend QDataStream& operator<<(QDataStream& stream, GraphicVertex* vertex);
    friend QDataStream& operator>>(QDataStream& stream, GraphicVertex*& vertex);

protected:
    QRectF _rect;
    Sence::Vertex<QString>* _vertex;
    QString _vertexUuid;
};

QDataStream& operator<<(QDataStream& stream, GraphicVertex* vertex);
QDataStream& operator>>(QDataStream& stream, GraphicVertex*& vertex);

#endif // GRAPHICVERTEX_H
