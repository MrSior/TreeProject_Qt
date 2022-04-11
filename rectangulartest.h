#ifndef RECTANGULARTEST_H
#define RECTANGULARTEST_H

#include "QGraphicsItem"
#include "QPainter"
#include "QObject"
#include "QMouseEvent"
#include <QKeyEvent>
#include "avl_tree.h"
#include <QGraphicsScene>
#include "QFont"
#include "treap.h"

class RectangularTest: public QObject, public QGraphicsItem
{
public:
    RectangularTest(int x, int y, int key, AVL_tree* avl_tree, QGraphicsScene *avl_scene, Treap* treap);
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

public:
    int x_offset, y_offset;
    int key;
    QPoint point;
    AVL_tree* avl_tree;
    Treap* treap;
    QGraphicsScene *avl_scene;
    void Draw_avl_tree(AVL_node* node, int x, int y);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // RECTANGULARTEST_H
