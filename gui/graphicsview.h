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
        EditEdgeMode,
        ViewCostMode
    };

public:
    GraphicsView(QWidget* parent = nullptr);
    GraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);

    inline GraphicsMode getGraphicsMode() const { return _graphicsMode; }
    void setGraphicsMode(GraphicsMode mode);

    inline const Sence::Graph<QString, int>& getGraph() const { return _graph; }

    QPen pen() const;
    QPen selectedPen() const;
    QBrush brush() const;
    QBrush selectedBrush() const;
    QFont font() const;

    void setPen(const QPen& pen);
    void setSelectedPen(const QPen& pen);
    void setBrush(const QBrush& brush);
    void setSelectedBrush(const QBrush& brush);
    void setFont(const QFont& font);

protected:
    virtual void resizeEvent(QResizeEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

    template <typename T>
    T* getItem(const QPointF& point) const;

    template<typename T>
    T* getItem(const QString& uuid) const;

    template <typename T>
    QList<T*> getItems(const QPointF& point) const;

    template <typename T>
    QList<T*> getItems() const;

    friend QDataStream& operator<<(QDataStream& stream, const GraphicsView& view);
    friend QDataStream& operator>>(QDataStream& stream, GraphicsView& view);

protected:
    GraphicsMode _graphicsMode;
    GraphicVertex* _selectedItem;
    Sence::Graph<QString, int> _graph;
};

QDataStream& operator<<(QDataStream& stream, const GraphicsView& view);
QDataStream& operator>>(QDataStream& stream, GraphicsView& view);

#endif // GRAPHICSVIEW_H
