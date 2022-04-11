#ifndef TREAP_H
#define TREAP_H

#include "treap_node.h"
#include "random"
#include "ctime"

class Treap
{
    Treap_node* root;

    std::pair<Treap_node *, Treap_node *> Split(Treap_node *tree, int split_key);
    Treap_node *Merge(Treap_node *first_tree, Treap_node *second_tree);

    void Update(Treap_node* node);
    int Get_height(Treap_node* node);

public:
    Treap(){
        root = nullptr;
        gen = std::mt19937(time(nullptr));
        dis = std::uniform_int_distribution<> (0, 10000);
    }

    int Get_min(Treap_node *tree);
    void Add(int data);
    void Delete(int data);
    Treap_node* Get_root();

    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
};

#endif // TREAP_H
