#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

#include "abstractitem.h"

class QResizeEvent;

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent = nullptr);
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

protected:
    QList<AbstractItem*> _items;
};

#endif // GRAPHICSVIEW_H
