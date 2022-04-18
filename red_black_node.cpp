#include "red_black_node.h"

Red_Black_node *Red_Black_node::Get_grandfather() {
    if (parent == nullptr) return nullptr;
    return parent->parent;
}

Red_Black_node *Red_Black_node::Get_uncle() {
    auto* grandfather = Get_grandfather();
    if (grandfather == nullptr) return nullptr;
    if (grandfather->left == parent){
        return grandfather->right;
    }
    return grandfather->left;
}

Red_Black_node *Red_Black_node::Get_sibling() {
    if (parent == nullptr) return nullptr;
    if (parent->left == this){
        return parent->right;
    }
    return parent->left;
}

Red_Black_node *Red_Black_node::Get_sibling_left() {
    if (Get_sibling() == nullptr) return nullptr;
    return Get_sibling()->left;
}

Red_Black_node *Red_Black_node::Get_sibling_right() {
    if (Get_sibling() == nullptr) return nullptr;
    return Get_sibling()->right;
}
