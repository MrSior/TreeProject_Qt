#include "treap_graphics_item.h"


Treap_graphics_item::Treap_graphics_item(int x, int y, int key, int priority,
                                         QGraphicsScene *treap_scene, AVL_tree* avl_tree, Treap *treap, Splay_tree* splay_tree)
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
    space_x = 100;
    space_y = 100;
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
    int length = 1;
    if(key < 0){
        length = log10(std::abs(key)) + 1;
    } else if(key > 0){
        length = log10(std::abs(key));
    }
    painter->drawText(point.x() - length * 10, point.y() + 10, QString::fromStdString(std::to_string(key)));
//    painter->setPen(QColor(252, 199, 93));
    painter->setPen(QColor(161, 195, 73));
    font.setPointSize(15);
    painter->setFont(font);
    painter->drawText(point.x() - 50, point.y() - 25, QString::fromStdString(std::to_string(priority)));
}

QRectF Treap_graphics_item::boundingRect() const
{
    return QRectF(QPointF(-60 + x_offset, -45 + y_offset), QSizeF(120, 90));
}

void Treap_graphics_item::Draw_treap(Treap_node *node)
{
//    if(node == nullptr) return;
//    int delta_x = std::pow(2, node->height - 1) * 100 / 2;
//    int l_x = x - delta_x;
//    int r_x = x + delta_x;
//    //int l_x = x - 100 - 100 * (node->Left ? node->Left->count + 1 : 1);
//    //int r_x = x + 100 + 100 * (node->Right ? node->Right->count + 1 : 1);
//    if(node->Left != nullptr) {
//        treap_scene->addLine(x, y, l_x, y + 100, QPen(QColor(255, 255, 255)));
//    }
//    if(node->Right != nullptr) {
//        treap_scene->addLine(x, y, r_x, y + 100, QPen(QColor(255, 255, 255)));
//    }
//    Treap_graphics_item* rectTest;
//    rectTest = new Treap_graphics_item(x, y, node->key, node->priority, treap_scene, avl_tree, treap, splay_tree);
//    //rectTest->setFlag(QGraphicsItem::ItemIsSelectable, true);
//    treap_scene->addItem(rectTest);

//    Draw_treap(node->Left, l_x, y + 100);
//    Draw_treap(node->Right, r_x, y + 100);
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
            treap_scene->addLine(x, y, child_x, child_y, QPen(QColor(255, 255, 255)));
            queue.push(cur_node->left);
        }
        if(cur_node->right != nullptr){
            int child_x = cur_node->right->column * space_x;
            int child_y = cur_node->right->level * space_y;
            treap_scene->addLine(x, y, child_x, child_y, QPen(QColor(255, 255, 255)));
            queue.push(cur_node->right);
        }
        Treap_graphics_item* node_shape;
        node_shape = new Treap_graphics_item(x, y, cur_node->key, cur_node->priority, treap_scene, avl_tree, treap, splay_tree);
        treap_scene->addItem(node_shape);
    }
}

Shadow_tree_node *Treap_graphics_item::build_shadow_tree(Treap_node *node, int level, int &column)
{
    Shadow_tree_node* new_node = nullptr;
    if (node != nullptr){
        new_node = new Shadow_tree_node;
        Shadow_tree_node* new_left = build_shadow_tree(node->Left, level + 1, column);
        new_node->left = new_left;

        new_node->key = node->key;
        new_node->priority = node->priority;
        new_node->level = level;
        new_node->column = column;

        column++;

        Shadow_tree_node* new_right = build_shadow_tree(node->Right, level + 1, column);
        new_node->right = new_right;
    }
    return new_node;
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
    //Draw_treap(treap->Get_root());
}
