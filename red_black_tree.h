#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "red_black_node.h"
#include "algorithm"

class Red_Black_tree
{
    Red_Black_node* root;

    void Left_rotate(Red_Black_node*& root_node, Red_Black_node*& node);
    void Right_rotate(Red_Black_node*& root_node, Red_Black_node*& node);
    Red_Black_node* Red_Black_insert(Red_Black_node* node,Red_Black_node* new_node);
    void Fix_insert(Red_Black_node*& root_node, Red_Black_node*& node);

    void Red_Black_delete(Red_Black_node*& node, int key);
    void Fix_delete(Red_Black_node* node);

    bool is_Red(Red_Black_node* node);
    bool is_Black(Red_Black_node* node);

    int Get_height(Red_Black_node* node);
    Red_Black_node* Get_min(Red_Black_node* node);

    void Inorder_print(Red_Black_node* node);
    void Del_min(Red_Black_node*& node);


public:
    Red_Black_tree(){
        root = nullptr;
    }
    Red_Black_node* Get_root();

    void Add(int key);
    void Delete(int key);

    void Print();
};

#endif // RED_BLACK_TREE_H
