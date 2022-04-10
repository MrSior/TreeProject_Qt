#include "rectangulartest.h"

RectangularTest::RectangularTest(int x, int y, int key, AVL_tree* avl_tree, QGraphicsScene *avl_scene) : QGraphicsItem()
{
    x_offset = x;
    y_offset = y;
    this->key = key;
    point = QPoint(x, y);
    this->avl_tree = avl_tree;
    this->avl_scene = avl_scene;
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
    painter->drawText(point.x() - 10, point.y() + 10, QString::fromStdString(std::to_string(key)));
}

QRectF RectangularTest::boundingRect() const
{
    return QRectF(QPointF(-50 + x_offset, -25 + y_offset), QSizeF(100, 50));
}

QVariant RectangularTest::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
        {
            if (value == true)
            {
                // do stuff if selected

                qDebug() << key;
                // avl_tree->Delete(key);
                // emit Redraw_tree();
                avl_scene->clear();
                avl_tree->Delete(key);
                Draw_avl_tree(avl_tree->Get_root(), 0, 0);
            }
            else
            {
                // do stuff if not selected
            }
        }

    return QGraphicsItem::itemChange(change, value);
}

void RectangularTest::Draw_avl_tree(AVL_node *node, int x, int y)
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
    rectTest = new RectangularTest(x, y, node->key, avl_tree, avl_scene);
    rectTest->setFlag(QGraphicsItem::ItemIsSelectable, true);
    avl_scene->addItem(rectTest);

    //QObject::connect(rectTest, &RectangularTest::Redraw_tree, this, &MainWindow::Draw_trees);

    Draw_avl_tree(node->left, x - delta_x, y + 100);
    Draw_avl_tree(node->right, x + delta_x, y + 100);
}
