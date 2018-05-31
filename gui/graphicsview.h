#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

#include "graph.h"

class QResizeEvent;
class GraphicVertex;

class GraphicsView : public QGraphicsView {
public:
    enum GraphicsMode {
        ViewMode,
        EditVertexMode,
        EditEdgeMode
        //        MoveMode
    };

public:
    GraphicsView(QWidget* parent = nullptr);
    GraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);

    inline GraphicsMode getGraphicsMode() const { return _graphicsMode; }
    void setGraphicsMode(GraphicsMode mode);

    inline const Sence::Graph<QString, int>& getGraph() const { return _graph; }

protected:
    virtual void resizeEvent(QResizeEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

    template <typename T>
    T* getItem(const QPointF& point) const;

    template <typename T>
    QList<T*> getItems(const QPointF& point) const;

protected:
    GraphicsMode _graphicsMode;
    GraphicVertex* _selectedItem;
    Sence::Graph<QString, int> _graph;
};

#endif // GRAPHICSVIEW_H
