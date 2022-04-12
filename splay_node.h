#ifndef SPLAY_NODE_H
#define SPLAY_NODE_H


class Splay_node
{
public:
    int key;
    Splay_node *left, *right;
    int height;

    Splay_node(){
        left = nullptr;
        right = nullptr;
        key = 0;
        height = 1;
    }

    explicit Splay_node(int key){
        this->key = key;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

#endif // SPLAY_NODE_H
