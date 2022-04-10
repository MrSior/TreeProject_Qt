#ifndef TREAP_GRAPHICS_ITEM_H
#define TREAP_GRAPHICS_ITEM_H

#include "QGraphicsItem"
#include "QPainter"
#include "QObject"
#include "QMouseEvent"
#include <QKeyEvent>
#include "treap.h"
#include <QGraphicsScene>
#include "QFont"

class Treap_graphics_item: public QObject, public QGraphicsItem
{
public:
    Treap_graphics_item(int x, int y, int key, int priority, Treap* treap, QGraphicsScene *treap_scene);
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

public:
    int x_offset, y_offset;
    int key;
    int priority;
    QPoint point;
    Treap* treap;
    QGraphicsScene *treap_scene;
    void Draw_treap(Treap_node* node, int x, int y);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // TREAP_GRAPHICS_ITEM_H
