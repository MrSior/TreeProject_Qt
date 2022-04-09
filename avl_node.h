#ifndef AVL_NODE_H
#define AVL_NODE_H


class AVL_node
{
public:
    int key;
    AVL_node* left;
    AVL_node* right;
    int height;

public:

    AVL_node(){
        key = 0;
        left = nullptr;
        right = nullptr;
        height = 0;
    }

    explicit AVL_node(int key){
        this->key = key;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

#endif // AVL_NODE_H
