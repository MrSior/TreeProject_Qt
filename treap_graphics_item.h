#ifndef TREAP_GRAPHICS_ITEM_H
#define TREAP_GRAPHICS_ITEM_H

#include "QGraphicsItem"
#include "QPainter"
#include "QObject"
#include "QMouseEvent"
#include <QKeyEvent>
#include "treap.h"
#include <QGraphicsScene>
#include "QGraphicsView"
#include "QFont"
#include "avl_tree.h"
#include "splay_tree.h"

class Treap_graphics_item: public QObject, public QGraphicsItem
{
public:
    Treap_graphics_item(int x, int y, int key, int priority,
                        QGraphicsScene *treap_scene, AVL_tree* avl_tree, Treap* treap, Splay_tree* splay_tree, QGraphicsView* treap_view);
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

public:
    int x_offset, y_offset;
    int key;
    int priority;
    QPoint point;
    Treap* treap;
    AVL_tree* avl_tree;
    Splay_tree* splay_tree;
    QGraphicsScene *treap_scene;
    QGraphicsView* treap_view;
    void Draw_treap(Treap_node* node, int x, int y);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // TREAP_GRAPHICS_ITEM_H
