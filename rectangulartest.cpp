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
    space_x = 100;
    space_y = 100;
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
    int length = 1;
    if(key < 0){
        length = log10(std::abs(key)) + 1;
    } else if(key > 0){
        length = log10(std::abs(key));
    }
    painter->drawText(point.x() - length * 10, point.y() + 10, QString::fromStdString(std::to_string(key)));
}

QRectF RectangularTest::boundingRect() const
{
    return QRectF(QPointF(-100 + x_offset, -50 + y_offset), QSizeF(200, 100));
}

void RectangularTest::Draw_avl_tree(AVL_node *node, int x, int y)
{
//    if(node == nullptr) return;
//    int delta_x = std::pow(2, node->height - 1) * 100 / 2;
//    //int l_x = x - 100 * (node->left ? node->left->count : 0);
//    //int r_x = x + 100 * (node->right ? node->right->count : 0);
//    int l_x = x - delta_x;
//    int r_x = x + delta_x;
//    if(node->left != nullptr) {
//        avl_scene->addLine(x, y, l_x, y + 100, QPen(QColor(255, 255, 255)));
//    }
//    if(node->right != nullptr) {
//        avl_scene->addLine(x, y, r_x, y + 100, QPen(QColor(255, 255, 255)));
//    }
//    RectangularTest* rectTest;
//    rectTest = new RectangularTest(x, y, node->key, avl_scene, avl_tree, treap, splay_tree, avl_view);
//    //rectTest->setFlag(QGraphicsItem::ItemIsSelectable, true);
//    avl_scene->addItem(rectTest);

//    Draw_avl_tree(node->left, l_x, y + 100);
//    Draw_avl_tree(node->right, r_x, y + 100);
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
            avl_scene->addLine(x, y, child_x, child_y, QPen(QColor(255, 255, 255)));
            queue.push(cur_node->left);
        }
        if(cur_node->right != nullptr){
            int child_x = cur_node->right->column * space_x;
            int child_y = cur_node->right->level * space_y;
            avl_scene->addLine(x, y, child_x, child_y, QPen(QColor(255, 255, 255)));
            queue.push(cur_node->right);
        }
        RectangularTest* node_shape;
        node_shape = new RectangularTest(x, y, cur_node->key, avl_scene, avl_tree, treap, splay_tree, avl_view);
        avl_scene->addItem(node_shape);
    }
}

Shadow_tree_node *RectangularTest::build_shadow_tree(AVL_node *node, int level, int &column)
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

void RectangularTest::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    avl_scene->clear();
//    delete avl_scene;
//    avl_scene = new QGraphicsScene();
//    avl_view->setScene(avl_scene);
    avl_tree->Delete(key);
    treap->Delete(key);
    splay_tree->Delete(key);
    //Draw_avl_tree(avl_tree->Get_root(), 0, 0);
}
