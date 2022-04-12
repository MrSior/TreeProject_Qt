#include "treap_graphics_item.h"


Treap_graphics_item::Treap_graphics_item(int x, int y, int key, int priority,
                                         QGraphicsScene *treap_scene, AVL_tree* avl_tree, Treap *treap, Splay_tree* splay_tree,
                                         QGraphicsView* treap_view)
{
    x_offset = x;
    y_offset = y;
    this->key = key;
    this->priority = priority;
    point = QPoint(x, y);
    this->treap = treap;
    this->treap_scene = treap_scene;
    this->avl_tree = avl_tree;
    this->splay_tree = splay_tree;
    this->treap_view = treap_view;
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
    painter->setPen(QColor(0, 255, 0));
    font.setPointSize(15);
    painter->setFont(font);
    painter->drawText(point.x() - 50, point.y() - 25, QString::fromStdString(std::to_string(priority)));
}

QRectF Treap_graphics_item::boundingRect() const
{
    return QRectF(QPointF(-60 + x_offset, -45 + y_offset), QSizeF(120, 90));
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
    rectTest = new Treap_graphics_item(x, y, node->key, node->priority, treap_scene, avl_tree, treap, splay_tree, treap_view);
    //rectTest->setFlag(QGraphicsItem::ItemIsSelectable, true);
    treap_scene->addItem(rectTest);

    Draw_treap(node->Left, x - delta_x, y + 100);
    Draw_treap(node->Right, x + delta_x, y + 100);
}

void Treap_graphics_item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   treap_scene->clear();
//    delete treap_scene;
//    treap_scene = new QGraphicsScene();
//    treap_view->setScene(treap_scene);
    treap->Delete(key);
    avl_tree->Delete(key);
    splay_tree->Delete(key);
    Draw_treap(treap->Get_root(), 0, 0);
}
