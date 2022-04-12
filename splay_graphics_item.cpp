#include "splay_graphics_item.h"

Splay_graphics_item::Splay_graphics_item(int x, int y, int key,
                                         QGraphicsScene *splay_scene, AVL_tree *avl_tree, Treap *treap, Splay_tree *splay_tree,
                                         QGraphicsView* splay_view)
{
    x_offset = x;
    y_offset = y;
    point = QPoint(x, y);
    this->key = key;
    this->splay_scene = splay_scene;
    this->avl_tree = avl_tree;
    this->treap = treap;
    this->splay_tree = splay_tree;
    this->splay_view = splay_view;
}

void Splay_graphics_item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

QRectF Splay_graphics_item::boundingRect() const
{
    return QRectF(QPointF(-60 + x_offset, -25 + y_offset), QSizeF(120, 50));
}

void Splay_graphics_item::Draw_splay_tree(Splay_node *node, int x, int y)
{
    if(node == nullptr) return;
    int delta_x = std::pow(2, node->height - 1) * 100 / 2;
    if(node->left != nullptr) {
        splay_scene->addLine(x, y, x - delta_x, y + 100, QPen(QColor(255, 255, 255)));
    }
    if(node->right != nullptr) {
        splay_scene->addLine(x, y, x + delta_x, y + 100, QPen(QColor(255, 255, 255)));
    }
    Splay_graphics_item* rectTest;
    rectTest = new Splay_graphics_item(x, y, node->key, splay_scene, avl_tree, treap, splay_tree, splay_view);
    //rectTest->setFlag(QGraphicsItem::ItemIsSelectable, true);
    splay_scene->addItem(rectTest);

    Draw_splay_tree(node->left, x - delta_x, y + 100);
    Draw_splay_tree(node->right, x + delta_x, y + 100);
}

void Splay_graphics_item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    splay_scene->clear();
//    delete splay_scene;
//    splay_scene = new QGraphicsScene();
//    splay_view->setScene(splay_scene);
    splay_tree->Delete(key);
    treap->Delete(key);
    avl_tree->Delete(key);
    Draw_splay_tree(splay_tree->Get_root(), 0, 0);
}
