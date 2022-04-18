#include "splay_tree.h"

Splay_node *Splay_tree::Left_rotate(Splay_node *node_x) {
    Splay_node *node_y = node_x->right;
    Splay_node *T2 = node_y->left;

    node_x->right = T2;
    node_y->left = node_x;

    node_x->height = std::max(Get_height(node_x->left), Get_height(node_x->right)) + 1;
    node_y->height = std::max(Get_height(node_y->left), Get_height(node_y->right)) + 1;

    return node_y;
}

Splay_node *Splay_tree::Right_rotate(Splay_node *node_y) {
    Splay_node *node_x = node_y->left;
    Splay_node *T2 = node_x->right;

    node_x->right = node_y;
    node_y->left = T2;

    node_y->height = std::max(Get_height(node_y->left), Get_height(node_y->right)) + 1;
    node_x->height = std::max(Get_height(node_x->left), Get_height(node_x->right)) + 1;

    return node_x;
}

Splay_node *Splay_tree::Splay(Splay_node *node, int key) {
    if (node == nullptr || node->key == key) {
        return node;
    }

    if (node->key > key) {
        if (node->left == nullptr) return node;

        if (node->left->key > key) { // Zig-Zig
            /*
            *         node
            *         / \
            *        y   T4
            *       / \
            *      x  T3
            *     / \
            *    T1 T2
            */

            node->left->left = Splay(node->left->left, key);
            node = Right_rotate(node);
        } else if (node->left->key < key) { //Zag-Zig
            /*
            *        node
            *        / \
            *       y   T4
            *      / \
            *     T1  x
            *        / \
            *       T2 T3
            */

            node->left->right = Splay(node->left->right, key);
            if (node->left->right != nullptr){
                node->left = Left_rotate(node->left);
            }
        }

        if (node->left == nullptr) {
            return node;
        }
        return Right_rotate(node);
    } else {
        if (node->right == nullptr) return node;

        if (node->right->key < key){ // Zag-Zag
            /*
            *        node
            *        / \
            *       T1  y
            *          / \
            *         T2  x
            *            / \
            *           T3 T4
            */

            node->right->right = Splay(node->right->right, key);
            node = Left_rotate(node);
        } else if (node->right->key > key){ //Zig-Zag
            /*
            *         node
            *         / \
            *        T1  y
            *           / \
            *          x  T4
            *         / \
            *        T2 T3
            */

            node->right->left = Splay(node->right->left, key);
            if (node->right->left != nullptr) {
                node->right = Right_rotate(node->right);
            }
        }

        if (node->right == nullptr){
            return node;
        }
        return Left_rotate(node);
    }
}

int Splay_tree::Get_height(Splay_node *node) {
    if (node == nullptr) return 0;
    return node->height;
}

Splay_node* Splay_tree::Splay_insert(Splay_node* node, int key) {
    if (node == nullptr){
        return new Splay_node(key);
    }
    node = Splay(node, key);
    if (node->key == key) return node;
    auto* new_node = new Splay_node(key);

    if (node->key > key){
        new_node->right = node;
        new_node->left = node->left;
        node->left = nullptr;
    } else {
        new_node->left = node;
        new_node->right = node->right;
        node->right = nullptr;
    }
    new_node->height = std::max(Get_height(new_node->left), Get_height(new_node->right)) + 1;
    return new_node;
}

void Splay_tree::Add(int key) {
    root = Splay_insert(root, key);
}

//Splay_node *Splay_tree::Splay_delete(Splay_node* node, int key) {
//    if (node == nullptr) return nullptr;

//    node = Splay(node, key);
//    if (node->key != key){
//        return nullptr;
//    } else {
//        if(node->right == nullptr){
//            Splay_node* new_root = node->left;
//            delete node;
//            return new_root;
//        } else {
//            Splay_node* tmp = Get_min(node->right);
//            node->key = tmp->key;
//            node->right = Splay_delete(node->right, node->key);
//        }
//    }
//    node->height = std::max(Get_height(node->left), Get_height(node->right)) + 1;
//    return node;
//}

Splay_node *Splay_tree::Get_min(Splay_node *node) {
    while (node->left != nullptr){
        node = node->left;
    }
    return node;
}

void Splay_tree::Delete(int key) {
    root = Splay_delete(root, key);
}

void Splay_tree::Print(Splay_node* node) {
    if (node == nullptr) return;
    Print(node->left);
    //std::cout << node->key << " ";
    Print(node->right);
}

Splay_node *Splay_tree::Get_root() {
    return root;
}

int Splay_tree::Check_height(Splay_node *node)
{
    if(node == nullptr) return 0;
    node->height = std::max(Check_height(node->left), Check_height(node->right)) + 1;
    return node->height;
}


Splay_node *Splay_tree::Splay_delete(Splay_node* node, int key) {
    if (node == nullptr) return nullptr;

    node = Splay(node, key);
    if (node->key != key){
        return nullptr;
    } else {
        Splay_node* root1 = node->left;
        Splay_node* root2 = node->right;
        if(node->right == nullptr) return root1;
        Splay_node* tmp = Get_min(root2);
        root2 = Splay(root2, tmp->key);
        root2->left = root1;
        return root2;

//        if(node->right == nullptr){
//            Splay_node* new_root = node->left;
//            delete node;
//            return new_root;
//        } else {
//            Splay_node* tmp = Get_min(node->right);
//            node->key = tmp->key;
//            node->right = Splay_delete(node->right, node->key);
//        }
    }
    //node->height = std::max(Get_height(node->left), Get_height(node->right)) + 1;
    return node;
}
