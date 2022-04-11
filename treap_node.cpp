#include "treap_node.h"

Treap_node::Treap_node()
{
    this->Left = nullptr;
    this->Right = nullptr;
    height = 0;
}

Treap_node::Treap_node(int key, int priority, Treap_node *Left, Treap_node *Right)
{

    this->key = key;
    this->priority = priority;
//    if (priority == -1) {
//        this->priority = dis(gen);
//    } else {
//        this->priority = priority;
//    }
    this->Left = Left;
    this->Right = Right;
    height = 0;
}
