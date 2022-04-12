#ifndef SPLAY_GRAPHICS_ITEM_H
#define SPLAY_GRAPHICS_ITEM_H

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

class Splay_graphics_item : public QGraphicsItem
{
public:
    Splay_graphics_item(int x, int y, int key,
                        QGraphicsScene *splay_scene, AVL_tree* avl_tree, Treap* treap, Splay_tree* splay_tree, QGraphicsView* splay_view);
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

public:
    int x_offset, y_offset;
    int key;
    QPoint point;
    Treap* treap;
    AVL_tree* avl_tree;
    Splay_tree* splay_tree;
    QGraphicsScene *splay_scene;
    QGraphicsView* splay_view;
    void Draw_splay_tree(Splay_node* node, int x, int y);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // SPLAY_GRAPHICS_ITEM_H
