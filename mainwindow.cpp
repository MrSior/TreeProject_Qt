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

    //avl_tree = new AVL_tree;
    avl_tree.Insert(9);
    avl_tree.Insert(5);
    avl_tree.Insert(10);
    avl_tree.Insert(0);
    avl_tree.Insert(6);
    avl_tree.Insert(11);
    avl_tree.Insert(-1);
    avl_tree.Insert(1);
    avl_tree.Insert(2);

    //avl_tree->Delete(2);
//    for (int i = 0; i < 507; ++i) {
//        avl_tree->Insert(i + 1);
//    }

    Draw_avl_tree(avl_tree.Get_root(), 0, 0);

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

    }
    if(event->key() == Qt::Key_S){
        ui->avl_graphicsView->scale(1.1,  1.1);
    }
}

//void MainWindow::mousePressEvent(QMouseEvent *event)
//{
//    if(event->button() == Qt::MouseButton::LeftButton){
//        qDebug() << 1;
//        if(!avl_scene->selectedItems().empty()){
//            qDebug() << 1;
//            Draw_trees();
//        }
//    }
//}

void MainWindow::Draw_avl_tree(AVL_node* node, int x, int y)
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
    rectTest = new RectangularTest(x, y, node->key, &avl_tree, avl_scene);
    rectTest->setFlag(QGraphicsItem::ItemIsSelectable, true);
    avl_scene->addItem(rectTest);

    //QObject::connect(rectTest, &RectangularTest::Redraw_tree, this, &MainWindow::Draw_trees);

    Draw_avl_tree(node->left, x - delta_x, y + 100);
    Draw_avl_tree(node->right, x + delta_x, y + 100);
}

