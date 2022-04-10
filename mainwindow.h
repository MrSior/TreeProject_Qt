#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "QMouseEvent"
#include "rectangulartest.h"
#include "avl_tree.h"
#include "QGraphicsSceneMouseEvent"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void keyPressEvent( QKeyEvent *event );
    // virtual void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *avl_scene;
    AVL_tree avl_tree;
    void Draw_avl_tree(AVL_node* node, int x, int y);
};
#endif // MAINWINDOW_H
