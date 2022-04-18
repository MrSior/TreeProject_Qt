#ifndef REDBLACK_GRAPHICS_ITEM_H
#define REDBLACK_GRAPHICS_ITEM_H

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
#include "red_black_tree.h"

class RedBlack_graphics_item : public QGraphicsItem
{
public:
    RedBlack_graphics_item(int x, int y, int key, int color,
                        QGraphicsScene *red_black_scene, AVL_tree* avl_tree, Treap* treap, Splay_tree* splay_tree, Red_Black_tree* rb_tree);
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

public:
    int x_offset, y_offset;
    int key;
    char color;
    QPoint point;
    Treap* treap;
    AVL_tree* avl_tree;
    Splay_tree* splay_tree;
    Red_Black_tree* rb_tree;
    QGraphicsScene *red_black_scene;
    //QGraphicsView* splay_view;
    void Draw_splay_tree(Red_Black_node* node, int x, int y);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // REDBLACK_GRAPHICS_ITEM_H
