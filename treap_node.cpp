#include "treap_node.h"

Treap_node::Treap_node()
{
    this->Left = nullptr;
    this->Right = nullptr;
    height = 0;
}

Treap_node::Treap_node(int key, int priority, Treap_node *Left, Treap_node *Right)
{
    std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution<> dis(0, 10000);

    this->key = key;
    if (priority == -1) {
        this->priority = dis(gen);
    } else {
        this->priority = priority;
    }
    this->Left = Left;
    this->Right = Right;
    height = 0;
}
