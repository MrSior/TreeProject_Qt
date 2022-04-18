#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "QMouseEvent"
#include "rectangulartest.h"
#include "avl_tree.h"
#include "QGraphicsSceneMouseEvent"
#include "treap.h"
#include "treap_graphics_item.h"
#include "splay_tree.h"
#include "splay_graphics_item.h"
#include "red_black_tree.h"
#include "redblack_graphics_item.h"
#include "random"
#include "shadow_tree_node.h"
#include "QTimer"

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

private slots:
    void on_AddElement_clicked();

    void on_DeleteElement_clicked();

    void on_tabWidget_currentChanged(int index);

    void Draw_trees();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *avl_scene;
    QGraphicsScene *treap_scene;
    QGraphicsScene *splay_scene;
    QGraphicsScene *red_black_scene;
    AVL_tree avl_tree;
    Treap treap;
    Splay_tree splay_tree;
    Red_Black_tree rb_tree;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
    void Draw_avl_tree(AVL_node* node);
    void Draw_treap(Treap_node* node);
    void Draw_splay_tree(Splay_node* node);
    void Draw_rb_tree(Red_Black_node* node);

    Shadow_tree_node* build_shadow_tree(AVL_node* node, int level, int& column);
    Shadow_tree_node *build_shadow_tree(Splay_node* node, int level, int& column);
    Shadow_tree_node* build_shadow_tree(Treap_node* node, int level, int& column);
    Shadow_tree_node* build_shadow_tree(Red_Black_node* node, int level, int& column);

    int space_x;
    int space_y;

    QTimer* timer;
};
#endif // MAINWINDOW_H
