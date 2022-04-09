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

    avl_tree = new AVL_tree;

    for (int i = 0; i < 507; ++i) {
        avl_tree->Insert(i + 1);
    }

    Draw_avl_tree(avl_tree->Get_root(), 0, 0);

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



   ui->avl_graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
   ui->avl_graphicsView->setRenderHint(QPainter::Antialiasing);
   ui->avl_graphicsView->scale(0.2, 0.2);

//    ui->avl_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->avl_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
    rectTest = new RectangularTest(x, y, node->key);
    avl_scene->addItem(rectTest);
    Draw_avl_tree(node->left, x - delta_x, y + 100);
    Draw_avl_tree(node->right, x + delta_x, y + 100);
}

