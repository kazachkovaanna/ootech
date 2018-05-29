#include "graphicsview.h"
#include <QResizeEvent>
#include <QTransform>
#include <QDebug>

GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
}

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    if (!scene())
        return;

    scene()->setSceneRect(0, 0, event->size().width(), event->size().height());
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (scene()) {
        for (QGraphicsItem* item : scene()->items()) {
            if (auto i = dynamic_cast<AbstractItem*>(item)) {
                i->setItemSelected(false);
            }
        }
    }

    QGraphicsView::mousePressEvent(event);
}
