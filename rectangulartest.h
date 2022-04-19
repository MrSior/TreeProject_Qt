#ifndef RECTANGULARTEST_H
#define RECTANGULARTEST_H

#include "QGraphicsItem"
#include "QPainter"
#include "QObject"
#include "QMouseEvent"
#include <QKeyEvent>
#include "avl_tree.h"
#include <QGraphicsScene>
#include "QGraphicsView"
#include "QFont"
#include "treap.h"
#include "splay_tree.h"
#include "shadow_tree_node.h"
#include "queue"
#include "red_black_tree.h"

class RectangularTest: public QObject, public QGraphicsItem
{
public:
    RectangularTest(int x, int y, int key,
                    QGraphicsScene *avl_scene, AVL_tree* avl_tree, Treap* treap, Splay_tree* splay_tree, Red_Black_tree* rb_tree);
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

public:
    int x_offset, y_offset;
    int key;
    QPoint point;
    AVL_tree* avl_tree;
    Treap* treap;
    Splay_tree* splay_tree;
    Red_Black_tree* rb_tree;
    QGraphicsScene *avl_scene;
    void Draw_avl_tree(AVL_node* node, int x, int y);
    Shadow_tree_node* build_shadow_tree(AVL_node* node, int level, int& column);

    int space_x;
    int space_y;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // RECTANGULARTEST_H
