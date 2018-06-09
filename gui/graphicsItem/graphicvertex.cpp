#include "graphicvertex.h"
#include "graph.h"
#include "vertexsettings.h"

#include <QCursor>
#include <QDebug>
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QWidget>

GraphicVertex::GraphicVertex(QGraphicsItem* parent)
    : AbstractItem(parent)
    , _rect(0, 0, 30, 30)
    , _vertex(nullptr)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setZValue(100);
}

QPainterPath GraphicVertex::shape() const
{
    QPainterPath path;
    path.addEllipse(_rect);

    if (_vertex && !_vertex->getData().isEmpty()) {
        path.addText(_rect.topRight(), _font, _vertex->getData());
    }

    return path;
}

QPointF GraphicVertex::getCenter() const
{
    return pos() + (_rect.topLeft() + _rect.bottomRight()) / 2;
}

void GraphicVertex::setVertex(Sence::Vertex<QString>* vertex)
{
    _vertex = vertex;
    if (_vertex)
        _vertexUuid = vertex->getUuid();
    update();
}

QWidget *GraphicVertex::getSettingsForm()
{
    VertexSettings* settings = new VertexSettings(*this);
    return settings;
}

QDataStream &operator<<(QDataStream &stream, GraphicVertex *vertex)
{
    stream.resetStatus();

    stream << vertex->_uuid;
    stream << vertex->_vertexUuid;
    stream << vertex->_rect;
    stream << vertex->pos();
    stream << vertex->toolTip();

    return stream;
}

QDataStream &operator>>(QDataStream &stream, GraphicVertex *&vertex)
{
    stream.startTransaction();

    vertex = new GraphicVertex;
    stream >> vertex->_uuid;
    stream >> vertex->_vertexUuid;
    stream >> vertex->_rect;
    QPointF pos;
    stream >> pos;
    vertex->setPos(pos);
    QString tooltip;
    stream >> tooltip;
    vertex->setToolTip(tooltip);

    if (!stream.commitTransaction()) {

    }

    return stream;
}
