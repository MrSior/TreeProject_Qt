#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "splay_node.h"
#include "algorithm"

class Splay_tree
{
private:
    Splay_node* root;

    Splay_node* Left_rotate(Splay_node* node_x);
    Splay_node* Right_rotate(Splay_node* node_y);
    Splay_node* Splay(Splay_node* node, int key);

    Splay_node* Splay_insert(Splay_node* node, int key);
    Splay_node* Splay_delete(Splay_node* node, int key);
    Splay_node* Get_min(Splay_node* node);
public:
    Splay_tree(){
        root = nullptr;
    }

    int Get_height(Splay_node* node);
    Splay_node* Get_root();

    void Add(int key);
    void Delete(int key);

    void Print(Splay_node* node);

    int Check_height(Splay_node* node);
};

#endif // SPLAY_TREE_H
