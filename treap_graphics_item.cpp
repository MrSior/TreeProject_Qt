#include "treap_graphics_item.h"


Treap_graphics_item::Treap_graphics_item(int x, int y, int key, int priority, Treap *treap, QGraphicsScene *treap_scene, AVL_tree* avl_tree)
{
    x_offset = x;
    y_offset = y;
    this->key = key;
    this->priority = priority;
    point = QPoint(x, y);
    this->treap = treap;
    this->treap_scene = treap_scene;
    this->avl_tree = avl_tree;
}

void Treap_graphics_item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

QRectF Treap_graphics_item::boundingRect() const
{
    return QRectF(QPointF(-50 + x_offset, -25 + y_offset), QSizeF(100, 50));
}

void Treap_graphics_item::Draw_treap(Treap_node *node, int x, int y)
{
    if(node == nullptr) return;
    int delta_x = std::pow(2, node->height - 1) * 100 / 2;
    if(node->Left != nullptr) {
        treap_scene->addLine(x, y, x - delta_x, y + 100, QPen(QColor(255, 255, 255)));
    }
    if(node->Right != nullptr) {
        treap_scene->addLine(x, y, x + delta_x, y + 100, QPen(QColor(255, 255, 255)));
    }
    Treap_graphics_item* rectTest;
    rectTest = new Treap_graphics_item(x, y, node->key, node->priority, treap, treap_scene, avl_tree);
    //rectTest->setFlag(QGraphicsItem::ItemIsSelectable, true);
    treap_scene->addItem(rectTest);

    Draw_treap(node->Left, x - delta_x, y + 100);
    Draw_treap(node->Right, x + delta_x, y + 100);
}

void Treap_graphics_item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    treap_scene->clear();
    treap->Delete(key);
    avl_tree->Delete(key);
    Draw_treap(treap->Get_root(), 0, 0);
}
