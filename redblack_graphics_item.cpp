#include "redblack_graphics_item.h"

RedBlack_graphics_item::RedBlack_graphics_item(int x, int y, int key, int color,
                                               QGraphicsScene *red_black_scene,
                                               AVL_tree *avl_tree, Treap *treap, Splay_tree *splay_tree, Red_Black_tree *rb_tree)
{
    x_offset = x;
    y_offset = y;
    point = QPoint(x, y);
    this->color = color;
    this->key = key;
    this->red_black_scene = red_black_scene;
    this->avl_tree = avl_tree;
    this->treap = treap;
    this->splay_tree = splay_tree;
    this->rb_tree = rb_tree;
}

void RedBlack_graphics_item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(color == 'R'){
//        painter->setPen(QColor(241, 145, 155));
        painter->setPen(QColor(204, 68, 75));
        painter->setBrush(QColor(223, 115, 115));
    } else {
        painter->setPen(QColor(50, 50, 50));
        painter->setBrush(QColor(90, 90, 90));
    }
    painter->drawEllipse(point, 50, 25);
    painter->setPen(QColor(0, 0, 0));
    QFont font = painter->font() ;
    font.setPointSize(30);
    painter->setFont(font);
    int length = 1;
    if(key < 0){
        length = log10(std::abs(key)) + 1;
    } else if(key > 0){
        length = log10(std::abs(key));
    }
    painter->drawText(point.x() - length * 10, point.y() + 10, QString::fromStdString(std::to_string(key)));
}

QRectF RedBlack_graphics_item::boundingRect() const
{
    return QRectF(QPointF(-80 + x_offset, -40 + y_offset), QSizeF(160, 80));
}

void RedBlack_graphics_item::Draw_splay_tree(Red_Black_node *node, int x, int y)
{
    if(node == nullptr) return;
    int delta_x = std::pow(2, node->height - 1) * 100 / 2;
    if(node->left != nullptr) {
        red_black_scene->addLine(x, y, x - delta_x, y + 100, QPen(QColor(255, 255, 255)));
    }
    if(node->right != nullptr) {
        red_black_scene->addLine(x, y, x + delta_x, y + 100, QPen(QColor(255, 255, 255)));
    }
    RedBlack_graphics_item* rectTest;
    rectTest = new RedBlack_graphics_item(x, y, node->key, node->color, red_black_scene, avl_tree, treap, splay_tree, rb_tree);
    //rectTest->setFlag(QGraphicsItem::ItemIsSelectable, true);
    red_black_scene->addItem(rectTest);

    Draw_splay_tree(node->left, x - delta_x, y + 100);
    Draw_splay_tree(node->right, x + delta_x, y + 100);
}

void RedBlack_graphics_item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    avl_tree->Delete(key);
    rb_tree->Delete(key);
    treap->Delete(key);
    splay_tree->Delete(key);
}
