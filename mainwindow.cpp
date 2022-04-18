#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    avl_scene = new QGraphicsScene(this);
    ui->avl_graphicsView->setScene(avl_scene);

    treap_scene = new QGraphicsScene(this);
    ui->Treap_graphicsView->setScene(treap_scene);

    splay_scene = new QGraphicsScene(this);
    ui->Splay_graphicsView->setScene(splay_scene);

    red_black_scene = new QGraphicsScene(this);
    ui->RedBlack_graphicsView->setScene(red_black_scene);

    //avl_tree = new AVL_tree;
//    avl_tree.Insert(9);
//    avl_tree.Insert(5);
//    avl_tree.Insert(10);
//    avl_tree.Insert(0);
//    avl_tree.Insert(6);
//    avl_tree.Insert(11);
//    avl_tree.Insert(-1);
//    avl_tree.Insert(1);
//    avl_tree.Insert(2);

    //avl_tree->Delete(2);
//    for (int i = 0; i < 507; ++i) {
//        avl_tree->Insert(i + 1);
//    }

    //Draw_avl_tree(avl_tree.Get_root(), 0, 0);

//    QBrush redBrush(Qt::red);
//    QPen blackPen(Qt::black);

//    RectangularTest* rectTest;
//    rectTest = new RectangularTest(500, 0);
//    //rectTest->setFlag(QGraphicsItem::ItemIsMovable, true);
//    avl_scene->addItem(rectTest);

//    RectangularTest* rectTest1;
//    rectTest1 = new RectangularTest(0, 0);
//    //rectTest1->setFlag(QGraphicsItem::ItemIsMovable, true);
//    avl_scene->addItem(rectTest1);



   //ui->avl_graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
   ui->avl_graphicsView->setRenderHint(QPainter::Antialiasing);
   ui->avl_graphicsView->scale(1, 1);

   ui->Treap_graphicsView->setRenderHint(QPainter::Antialiasing);
   ui->Treap_graphicsView->scale(1, 1);

   ui->Splay_graphicsView->setRenderHint(QPainter::Antialiasing);
   ui->Splay_graphicsView->scale(1, 1);

   ui->RedBlack_graphicsView->setRenderHint(QPainter::Antialiasing);
   ui->RedBlack_graphicsView->scale(1, 1);

   gen = std::mt19937(10 * time(0));
   dis = std::uniform_int_distribution<> (0, 10000);

   space_x = 100;
   space_y = 100;

   timer = new QTimer(this);
   QObject::connect(timer, SIGNAL(timeout()), this, SLOT(Draw_trees()));
   timer->start(10);


//    ui->avl_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->avl_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W){
        ui->avl_graphicsView->scale(0.9 , 0.9);
        ui->Treap_graphicsView->scale(0.9 , 0.9);
        ui->Splay_graphicsView->scale(0.9 , 0.9);
        ui->RedBlack_graphicsView->scale(0.9, 0.9);
    }
    if(event->key() == Qt::Key_S){
        ui->avl_graphicsView->scale(1.1,  1.1);
        ui->Treap_graphicsView->scale(1.1 , 1.1);
        ui->Splay_graphicsView->scale(1.1 , 1.1);
        ui->RedBlack_graphicsView->scale(1.1, 1.1);
    }
}

void MainWindow::Draw_avl_tree(AVL_node* node)
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
//    rectTest = new RectangularTest(x, y, node->key, avl_scene, &avl_tree, &treap, &splay_tree, ui->avl_graphicsView);
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
        node_shape = new RectangularTest(x, y, cur_node->key, avl_scene, &avl_tree, &treap, &splay_tree, ui->avl_graphicsView);
        avl_scene->addItem(node_shape);
    }
}

void MainWindow::Draw_treap(Treap_node *node)
{
//    if(node == nullptr) return;
//    int delta_x = std::pow(2, node->height - 1) * 100 / 2;
//    //int l_x = x - 100 - 100 * (node->Left ? node->Left->count + 1 : 1);
//    //int r_x = x + 100 + 100 * (node->Right ? node->Right->count + 1: 1);
//    int l_x = x - delta_x;
//    int r_x = x + delta_x;
//    if(node->Left != nullptr) {
//        treap_scene->addLine(x, y, l_x, y + 100, QPen(QColor(255, 255, 255)));
//    }
//    if(node->Right != nullptr) {
//        treap_scene->addLine(x, y, r_x, y + 100, QPen(QColor(255, 255, 255)));
//    }
//    Treap_graphics_item* rectTest;
//    rectTest = new Treap_graphics_item(x, y, node->key, node->priority, treap_scene, &avl_tree, &treap, &splay_tree, ui->Treap_graphicsView);
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
        node_shape = new Treap_graphics_item(x, y, cur_node->key, cur_node->priority, treap_scene, &avl_tree, &treap, &splay_tree);
        treap_scene->addItem(node_shape);
    }
}

void MainWindow::Draw_splay_tree(Splay_node *node)
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
//    rectTest = new Splay_graphics_item(x, y, node->key, splay_scene, &avl_tree, &treap, &splay_tree, ui->Splay_graphicsView);
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
        rectTest = new Splay_graphics_item(x, y, cur_node->key, splay_scene, &avl_tree, &treap, &splay_tree);
        splay_scene->addItem(rectTest);
    }
}

void MainWindow::Draw_rb_tree(Red_Black_node *node)
{
//    if(node == nullptr) return;
//    int delta_x = std::pow(2, node->height - 1) * 100 / 2;
//    if(node->left != nullptr) {
//        red_black_scene->addLine(x, y, x - delta_x, y + 100, QPen(QColor(90, 90, 90)));
//    }
//    if(node->right != nullptr) {
//        red_black_scene->addLine(x, y, x + delta_x, y + 100, QPen(QColor(90, 90, 90)));
//    }
//    RedBlack_graphics_item* rectTest;
//    rectTest = new RedBlack_graphics_item(x, y, node->key, node->color, red_black_scene, &avl_tree, &treap, &splay_tree, &rb_tree);
//    //rectTest->setFlag(QGraphicsItem::ItemIsSelectable, true);
//    red_black_scene->addItem(rectTest);

//    Draw_rb_tree(node->left, x - delta_x, y + 100);
//    Draw_rb_tree(node->right, x + delta_x, y + 100);
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
            red_black_scene->addLine(x, y, child_x, child_y, QPen(QColor(255, 255, 255)));
            queue.push(cur_node->left);
        }
        if(cur_node->right != nullptr){
            int child_x = cur_node->right->column * space_x;
            int child_y = cur_node->right->level * space_y;
            red_black_scene->addLine(x, y, child_x, child_y, QPen(QColor(255, 255, 255)));
            queue.push(cur_node->right);
        }
        RedBlack_graphics_item* node_shape;
        node_shape = new RedBlack_graphics_item(x, y, cur_node->key, cur_node->color,
                                                red_black_scene, &avl_tree, &treap, &splay_tree, &rb_tree);
        red_black_scene->addItem(node_shape);
    }
}

Shadow_tree_node *MainWindow::build_shadow_tree(AVL_node *node, int level, int &column)
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

Shadow_tree_node *MainWindow::build_shadow_tree(Splay_node *node, int level, int &column)
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

Shadow_tree_node *MainWindow::build_shadow_tree(Treap_node *node, int level, int &column)
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


Shadow_tree_node *MainWindow::build_shadow_tree(Red_Black_node *node, int level, int &column)
{
    Shadow_tree_node* new_node = nullptr;
    if (node != nullptr){
        new_node = new Shadow_tree_node;
        Shadow_tree_node* new_left = build_shadow_tree(node->left, level + 1, column);
        new_node->left = new_left;

        new_node->key = node->key;
        new_node->color = node->color;
        new_node->level = level;
        new_node->column = column;

        column++;

        Shadow_tree_node* new_right = build_shadow_tree(node->right, level + 1, column);
        new_node->right = new_right;
    }
    return new_node;
}

void MainWindow::on_AddElement_clicked()
{
    try {
        std::string str = ui->lineEdit->text().toStdString();
        if(str.empty()){
            for(int i = 0; i < 20; ++i){
                int num = dis(gen);
                avl_tree.Insert(num);
                treap.Add(num);
                splay_tree.Add(num);
                rb_tree.Add(num);
            }
        } else {
            str += ' ';
            std::string num;
            for(int i = 0; i < int(str.size()); ++i){
                if(str[i] != ' '){
                   num += str[i];
                } else {
                    avl_tree.Insert(std::stoi(num));
                    treap.Add(std::stoi(num));
                    splay_tree.Add(std::stoi(num));
                    rb_tree.Add(std::stoi(num));
                    num.clear();
                }
            }
        }
        avl_scene->clear();
        treap_scene->clear();
        splay_scene->clear();
        red_black_scene->clear();
//        delete splay_scene;
//        splay_scene = new QGraphicsScene(this);
//        ui->Splay_graphicsView->setScene(splay_scene);
//        delete treap_scene;
//        treap_scene = new QGraphicsScene(this);
//        ui->Treap_graphicsView->setScene(treap_scene);
//        delete avl_scene;
//        avl_scene = new QGraphicsScene(this);
//        ui->avl_graphicsView->setScene(avl_scene);
        Draw_avl_tree(avl_tree.Get_root());
        Draw_treap(treap.Get_root());
        Draw_splay_tree(splay_tree.Get_root());
        Draw_rb_tree(rb_tree.Get_root());
        ui->lineEdit->setText("");
    }  catch (...) {

    }
}


void MainWindow::on_DeleteElement_clicked()
{
    try {
        std::string str = ui->lineEdit_2->text().toStdString();
        str += ' ';
        std::string num;
        for(int i = 0; i < int(str.size()); ++i){
            if(str[i] != ' '){
                num += str[i];
            } else {
                if(num.empty()) continue;
                avl_tree.Delete(std::stoi(num));
                treap.Delete(std::stoi(num));
                splay_tree.Delete(std::stoi(num));
                num.clear();
            }
        }
        avl_scene->clear();
        treap_scene->clear();
        splay_scene->clear();
//        delete splay_scene;
//        splay_scene = new QGraphicsScene(this);
//        ui->Splay_graphicsView->setScene(splay_scene);
//        delete treap_scene;
//        treap_scene = new QGraphicsScene(this);
//        ui->Treap_graphicsView->setScene(treap_scene);
//        delete avl_scene;
//        avl_scene = new QGraphicsScene(this);
//        ui->avl_graphicsView->setScene(avl_scene);

        Draw_avl_tree(avl_tree.Get_root());
        Draw_treap(treap.Get_root());
        Draw_splay_tree(splay_tree.Get_root());
        ui->lineEdit_2->setText("");
    }  catch (...) {

    }
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 0) {
        avl_scene->clear();
        delete avl_scene;
        avl_scene = new QGraphicsScene(this);
        ui->avl_graphicsView->setScene(avl_scene);
       Draw_avl_tree(avl_tree.Get_root());
    }
    if(index == 1){
        red_black_scene->clear();
        delete red_black_scene;
        red_black_scene = new QGraphicsScene(this);
        ui->RedBlack_graphicsView->setScene(red_black_scene);
        Draw_rb_tree(rb_tree.Get_root());
    }
    if(index == 2){
       treap_scene->clear();
       delete treap_scene;
       treap_scene = new QGraphicsScene(this);
       ui->Treap_graphicsView->setScene(treap_scene);
       Draw_treap(treap.Get_root());
    }
    if(index == 3){
        splay_scene->clear();
        delete splay_scene;
        splay_scene = new QGraphicsScene(this);
        ui->Splay_graphicsView->setScene(splay_scene);
        Draw_splay_tree(splay_tree.Get_root());
    }
}

void MainWindow::Draw_trees()
{
    avl_scene->clear();
    treap_scene->clear();
    splay_scene->clear();
    red_black_scene->clear();

    Draw_avl_tree(avl_tree.Get_root());
    Draw_treap(treap.Get_root());
    Draw_splay_tree(splay_tree.Get_root());
    Draw_rb_tree(rb_tree.Get_root());
}

