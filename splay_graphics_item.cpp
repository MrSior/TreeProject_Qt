#include "splay_graphics_item.h"

Splay_graphics_item::Splay_graphics_item(int x, int y, int key,
                                         QGraphicsScene *splay_scene, AVL_tree *avl_tree, Treap *treap, Splay_tree *splay_tree)
{
    x_offset = x;
    y_offset = y;
    point = QPoint(x, y);
    this->key = key;
    this->splay_scene = splay_scene;
    this->avl_tree = avl_tree;
    this->treap = treap;
    this->splay_tree = splay_tree;
    space_x = 100;
    space_y = 100;
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
    int length = 1;
    if(key < 0){
        length = log10(std::abs(key)) + 1;
    } else if(key > 0){
        length = log10(std::abs(key));
    }
    painter->drawText(point.x() - length * 10, point.y() + 10, QString::fromStdString(std::to_string(key)));
}

QRectF Splay_graphics_item::boundingRect() const
{
    return QRectF(QPointF(-80 + x_offset, -40 + y_offset), QSizeF(160, 80));
}

void Splay_graphics_item::Draw_splay_tree(Splay_node *node, int x, int y)
{
//    if(node == nullptr) return;
//    int delta_x = std::pow(2, node->height - 1) * 100 / 2;
//    if(node->left != nullptr) {
//        splay_scene->addLine(x, y, x - delta_x, y + 100, QPen(QColor(255, 255, 255)));
//    }
//    if(node->right != nullptr) {
//        splay_scene->addLine(x, y, x + delta_x, y + 100, QPen(QColor(255, 255, 255)));
//    }
//    Splay_graphics_item* rectTest;
//    rectTest = new Splay_graphics_item(x, y, node->key, splay_scene, avl_tree, treap, splay_tree, splay_view);
//    //rectTest->setFlag(QGraphicsItem::ItemIsSelectable, true);
//    splay_scene->addItem(rectTest);

//    Draw_splay_tree(node->left, x - delta_x, y + 100);
//    Draw_splay_tree(node->right, x + delta_x, y + 100);
    if(node == nullptr) return;
    int level = 0;
    int column = 0;
    Shadow_tree_node* root = build_shadow_tree(node, level, column);
    std::queue<Shadow_tree_node*> queue;
    queue.push(root);
    while(!queue.empty()){
        auto cur_node = queue.front();
        queue.pop();
        int x = cur_node->column * space_x;
        int y = cur_node->level * space_y;
        if(cur_node->left != nullptr){
            int child_x = cur_node->left->column * space_x;
            int child_y = cur_node->left->level * space_y;
            splay_scene->addLine(x, y, child_x, child_y, QPen(QColor(255, 255, 255)));
            queue.push(cur_node->left);
        }
        if(cur_node->right != nullptr){
            int child_x = cur_node->right->column * space_x;
            int child_y = cur_node->right->level * space_y;
            splay_scene->addLine(x, y, child_x, child_y, QPen(QColor(255, 255, 255)));
            queue.push(cur_node->right);
        }
        Splay_graphics_item* rectTest;
        rectTest = new Splay_graphics_item(x, y, cur_node->key, splay_scene, avl_tree, treap, splay_tree);
        splay_scene->addItem(rectTest);
    }
}

Shadow_tree_node *Splay_graphics_item::build_shadow_tree(Splay_node *node, int level, int &column)
{
    Shadow_tree_node* new_node = nullptr;
    if (node != nullptr){
        new_node = new Shadow_tree_node;
        Shadow_tree_node* new_left = build_shadow_tree(node->left, level + 1, column);
        new_node->left = new_left;

        new_node->key = node->key;
        new_node->level = level;
        new_node->column = column;

        column++;

        Shadow_tree_node* new_right = build_shadow_tree(node->right, level + 1, column);
        new_node->right = new_right;
    }
    return new_node;
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
    //Draw_splay_tree(splay_tree->Get_root(), 0, 0);
}
