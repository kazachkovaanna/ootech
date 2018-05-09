#ifndef GRAPHICVERTEX_H
#define GRAPHICVERTEX_H

#include <QGraphicsObject>
#include <QPainter>

class GraphicVertex : public QGraphicsObject
{
public:
    GraphicVertex(QGraphicsItem * parent = 0);
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
//    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
//    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
//    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

private:
    QColor color;
//    bool dragOver;
};

#endif // GRAPHICVERTEX_H
