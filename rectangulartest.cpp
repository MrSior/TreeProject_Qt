#include "rectangulartest.h"

RectangularTest::RectangularTest(int x, int y, int key,
                                 QGraphicsScene *avl_scene, AVL_tree* avl_tree, Treap* treap, Splay_tree* splay_tree, QGraphicsView* avl_view)
{
    x_offset = x;
    y_offset = y;
    this->key = key;
    point = QPoint(x, y);
    this->avl_tree = avl_tree;
    this->avl_scene = avl_scene;
    this->treap = treap;
    this->splay_tree = splay_tree;
    this->avl_view = avl_view;
}

void RectangularTest::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QColor(105, 105, 105));
    painter->setBrush(QColor(155, 155, 155));
    painter->drawEllipse(point, 50, 25);
    painter->setPen(QColor(0, 0, 0));
    QFont font = painter->font() ;
    font.setPointSize(30);
    painter->setFont(font);
    painter->drawText(point.x() - 10, point.y() + 10, QString::fromStdString(std::to_string(key)));
}

QRectF RectangularTest::boundingRect() const
{
    return QRectF(QPointF(-100 + x_offset, -50 + y_offset), QSizeF(200, 100));
}

void RectangularTest::Draw_avl_tree(AVL_node *node, int x, int y)
{
    if(node == nullptr) return;
    int delta_x = std::pow(2, node->height - 1) * 100 / 2;
    if(node->left != nullptr) {
        avl_scene->addLine(x, y, x - delta_x, y + 100, QPen(QColor(255, 255, 255)));
    }
    if(node->right != nullptr) {
        avl_scene->addLine(x, y, x + delta_x, y + 100, QPen(QColor(255, 255, 255)));
    }
    RectangularTest* rectTest;
    rectTest = new RectangularTest(x, y, node->key, avl_scene, avl_tree, treap, splay_tree, avl_view);
    //rectTest->setFlag(QGraphicsItem::ItemIsSelectable, true);
    avl_scene->addItem(rectTest);

    Draw_avl_tree(node->left, x - delta_x, y + 100);
    Draw_avl_tree(node->right, x + delta_x, y + 100);
}

void RectangularTest::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    avl_scene->clear();
//    delete avl_scene;
//    avl_scene = new QGraphicsScene();
//    avl_view->setScene(avl_scene);
    avl_tree->Delete(key);
    treap->Delete(key);
    splay_tree->Delete(key);
    Draw_avl_tree(avl_tree->Get_root(), 0, 0);
}
