#ifndef TREAP_NODE_H
#define TREAP_NODE_H

#include "random"

class Treap_node
{
public:
    int key;
    int priority;

    int height;
    int count;

    Treap_node *Left;
    Treap_node *Right;

    Treap_node();

    explicit Treap_node(int key, int priority = -1, Treap_node *Left = nullptr, Treap_node *Right = nullptr);
};

#endif // TREAP_NODE_H
