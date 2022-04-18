#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "avl_node.h"
#include "algorithm"
#include "QDebug"

class AVL_tree
{
private:
    AVL_node* root;

    int Get_balance_factor(AVL_node* node);
    int Get_height(AVL_node* node);

    AVL_node* AVL_insert(AVL_node* node, int key);
    AVL_node* AVL_delete(AVL_node* node, int key);
    AVL_node* Left_rotate(AVL_node* node_x);
    AVL_node* Right_rotate(AVL_node* node_y);

    AVL_node* Get_min(AVL_node* node);
    void Print_inorder(AVL_node* node);
    int Recount(AVL_node* node);
public:
    AVL_tree(){
        root = nullptr;
    }

    AVL_node* Get_root();

    void Insert(int key);
    void Delete(int key);

    void Print();
};

#endif // AVL_TREE_H
