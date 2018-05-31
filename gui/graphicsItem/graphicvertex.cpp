#include "graphicvertex.h"
#include "graph.h"
#include "graphicsvertexdialog.h"

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
    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);

    setZValue(100);
}

QPainterPath GraphicVertex::shape() const
{
    QPainterPath path;
    path.addEllipse(_rect);

    if (_vertex && !_vertex->getData().isEmpty()) {
        path.addText(_rect.topRight(), QFont(), _vertex->getData());
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
    update();
}

void GraphicVertex::showSettings()
{
    GraphicsVertexDialog d;
    d.setName(_vertex->getData());
    d.setTooltip(toolTip());

    if (GraphicsVertexDialog::Accepted == d.exec()) {
        _vertex->setData(d.getName());
        setToolTip(d.getTooltip());
    }
}

void GraphicVertex::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    setPos(event->scenePos());
}
