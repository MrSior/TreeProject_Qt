#include "treap.h"

std::pair<Treap_node *, Treap_node *> Treap::Split(Treap_node* tree, int split_key)
{
    if (tree == nullptr) {
        return {nullptr, nullptr};
    }
    if (split_key > tree->key) {
        auto res = Split(tree->Right, split_key);
        tree->Right = res.first;
        Update(tree);
        return {tree, res.second};
    } else {
        auto res = Split(tree->Left, split_key);
        tree->Left = res.second;
        Update(tree);
        return {res.first, tree};
    }
}


Treap_node *Treap::Merge(Treap_node *first_tree, Treap_node *second_tree) {
    if (first_tree == nullptr) return second_tree;
    if (second_tree == nullptr) return first_tree;
    if (first_tree->priority < second_tree->priority) {
        first_tree->Right = Merge(first_tree->Right, second_tree);
        Update(first_tree);
        return first_tree;
    } else {
        second_tree->Left = Merge(first_tree, second_tree->Left);
        Update(second_tree);
        return second_tree;
    }
}

void Treap::Update(Treap_node* node)
{
    if(node == nullptr) return;
    node->height = Get_height(node->Left) + Get_height(node->Right) + 1;
}

int Treap::Get_height(Treap_node* node)
{
    if(node == nullptr) return 0;
    return node->height;
}

int Treap::Get_min(Treap_node *tree) {
    if (tree == nullptr) {
        return -1;
    }
    if (tree->Left == nullptr) {
        return tree->key;
    }
    return Get_min(tree->Left);
}

void Treap::Add(int data) {
    if (root == nullptr) {
        root = new Treap_node(data);
        return;
    }
    Update(root);
    auto res = Split(root, data);
    Treap_node *left = res.first;
    Treap_node *right = res.second;
    if (Get_min(left) != data) {
        auto *new_node = new Treap_node(data);
        root = Merge(Merge(left, new_node), right);
    } else {
        root = Merge(left, right);
    }
    Update(root);
}

void Treap::Delete(int data)
{

}

Treap_node* Treap::Get_root()
{
    return root;
}
