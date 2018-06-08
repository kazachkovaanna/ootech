#include "graphicsview.h"
#include "abstractitem.h"
#include "graphicsline.h"
#include "graphicvertex.h"
#include "exception.h"

#include <QDebug>
#include <QResizeEvent>
#include <QTransform>

GraphicsView::GraphicsView(QWidget* parent)
    : QGraphicsView(parent)
    , _graphicsMode(ViewMode)
{
    setRenderHint(QPainter::Antialiasing);
}

GraphicsView::GraphicsView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
    , _graphicsMode(ViewMode)
{
    setRenderHint(QPainter::Antialiasing);
}

void GraphicsView::setGraphicsMode(GraphicsView::GraphicsMode mode)
{
    _graphicsMode = mode;
}

QPen GraphicsView::pen() const
{
    return AbstractItem::pen();
}

QPen GraphicsView::selectedPen() const
{
    return AbstractItem::selectedPen();
}

QBrush GraphicsView::brush() const
{
    return AbstractItem::brush();
}

QBrush GraphicsView::selectedBrush() const
{
    return AbstractItem::selectedBrush();
}

QFont GraphicsView::font() const
{
    return AbstractItem::font();
}

void GraphicsView::setPen(const QPen &pen)
{
    AbstractItem::setPen(pen);
}

void GraphicsView::setSelectedPen(const QPen &pen)
{
    AbstractItem::setSelectedPen(pen);
}

void GraphicsView::setBrush(const QBrush &brush)
{
    AbstractItem::setBrush(brush);
}

void GraphicsView::setSelectedBrush(const QBrush &brush)
{
    AbstractItem::setSelectedBrush(brush);
}

void GraphicsView::setFont(const QFont &font)
{
    AbstractItem::setFont(font);
}

void GraphicsView::resizeEvent(QResizeEvent* event)
{
    QGraphicsView::resizeEvent(event);

    if (!scene())
        return;

    scene()->setSceneRect(0, 0, event->size().width(), event->size().height());
}

void GraphicsView::mousePressEvent(QMouseEvent* event)
{
    switch (_graphicsMode) {
    case ViewMode: {
        for (QGraphicsItem* item : items()) {
            if (auto i = dynamic_cast<AbstractItem*>(item)) {
                i->setSelected(false);
            }
        }
        QGraphicsView::mousePressEvent(event);
        return;
    }
    case EditVertexMode: {
        GraphicVertex* vertex = new GraphicVertex;
        vertex->setPos(event->pos());
        vertex->setVertex(new Sence::Vertex<QString>);
        scene()->addItem(vertex);
        _graph.add(vertex->getVertex());

        return;
    }
    case EditEdgeMode: {
        _selectedItem = getItem<GraphicVertex>(event->pos());
        return;
    }
    }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    if (_graphicsMode != EditEdgeMode) {
        QGraphicsView::mouseReleaseEvent(event);
        return;
    }

    GraphicVertex* end = getItem<GraphicVertex>(event->pos());

    if (!_selectedItem || !end || _selectedItem == end) {
        QGraphicsView::mouseReleaseEvent(event);
        return;
    }

    Sence::Vertex<QString>* from = _selectedItem->getVertex();
    Sence::Vertex<QString>* to = end->getVertex();

    Sence::Edge<int>* edge = new Sence::Edge<int>;

    GraphicsLine* line = new GraphicsLine;
    line->setStart(_selectedItem);
    line->setEnd(end);
    line->setEdge(edge);

    scene()->addItem(line);
    _graph.add(from, to, edge);

    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (ViewMode == _graphicsMode) {
        QGraphicsView::mouseDoubleClickEvent(event);
    }
}

template <typename T>
T* GraphicsView::getItem(const QPointF& point) const
{
    for (QGraphicsItem* item : items(point.toPoint())) {
        if (T* i = dynamic_cast<T*>(item)) {
            return i;
        }
    }

    return nullptr;
}

template<typename T>
T *GraphicsView::getItem(const QString &uuid) const
{
    for (QGraphicsItem* item : items()) {
        T* i = dynamic_cast<T*>(item);
        if (i && i->getUuid() == uuid) {
            return i;
        }
    }

    return nullptr;
}

template <typename T>
QList<T*> GraphicsView::getItems(const QPointF& point) const
{
    QList<T*> _items;

    for (QGraphicsItem* item : items(point.toPoint())) {
        if (T* i = dynamic_cast<T*>(item)) {
            _items.append(i);
        }
    }

    return _items;
}

template<typename T>
QList<T*> GraphicsView::getItems() const
{
    QList<T*> _items;

    for (QGraphicsItem* item : items()) {
        if (T* i = dynamic_cast<T*>(item)) {
            _items.append(i);
        }
    }

    return _items;
}

QDataStream &operator<<(QDataStream &stream, const GraphicsView &view)
{
    stream.resetStatus();

    stream << setVersion(QDataStream::Qt_5_10);
    stream << view._graph;
    stream << view.getItems<GraphicVertex>();
    stream << view.getItems<GraphicsLine>();

    return stream;
}

QDataStream &operator>>(QDataStream &stream, GraphicsView &view)
{
    stream.startTransaction();

    stream << setVersion(QDataStream::Qt_5_10);
    Sence::Graph<QString, int> graph;
    stream >> graph;

    QList<GraphicVertex*> vertices;
    stream >> vertices;

    QList<GraphicsLine*> lines;
    stream >> lines;

    if (!stream.commitTransaction()) {
        QString message("Can't deserialize graphics scene.");
        qWarning() << Q_FUNC_INFO << message;
        throw Sence::DeserializeException(message);
    }

    view.scene()->clear();

    for (GraphicVertex* item : vertices) {
        Sence::Vertex<QString>* v = graph.getVertex(item->getVertexUuid());
        item->setVertex(v);
        view.scene()->addItem(item);
    }

    for (GraphicsLine* item : lines) {
        Sence::Edge<int>* e = graph.getEdge(item->getEdgeUuid());
        item->setEdge(e);
        item->setStart(view.getItem<GraphicVertex>(item->getStartUuid()), false);
        item->setEnd(view.getItem<GraphicVertex>(item->getEndUuid()), false);
        view.scene()->addItem(item);
        item->update();
    }

    view._graph = graph;

    return stream;
}
