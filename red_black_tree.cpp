#include "red_black_tree.h"


void Red_Black_tree::Left_rotate(Red_Black_node*& root_node, Red_Black_node*& node) {
    Red_Black_node *node_right = node->right;

    node->right = node_right->left;

    if (node->right != nullptr)
        node->right->parent = node;

    node_right->parent = node->parent;

    if (node->parent == nullptr)
        root_node = node_right;

    else if (node == node->parent->left)
        node->parent->left = node_right;

    else
        node->parent->right = node_right;

    node_right->left = node;
    node->parent = node_right;
}

void Red_Black_tree::Right_rotate(Red_Black_node*& root_node, Red_Black_node*& node) {
    Red_Black_node* node_left = node->left;

    node->left = node_left->right;

    if (node->left != NULL)
        node->left->parent = node;

    node_left->parent = node->parent;

    if (node->parent == NULL)
        root_node = node_left;

    else if (node == node->parent->left)
        node->parent->left = node_left;

    else
        node->parent->right = node_left;

    node_left->right = node;
    node->parent = node_left;
}

int Red_Black_tree::Get_height(Red_Black_node *node) {
    if (node == nullptr) return 0;
    return node->height;
}

Red_Black_node *Red_Black_tree::Red_Black_insert(Red_Black_node* node,Red_Black_node* new_node) {
    if (node == nullptr){
        return new_node;
    }

    if (node->key < new_node->key){
        node->right = Red_Black_insert(node->right, new_node);
        node->right->parent = node;
    } else if (node->key > new_node->key){
        node->left = Red_Black_insert(node->left, new_node);
        node->left->parent = node;
    }

    node->height = std::max(Get_height(node->left), Get_height(node->right)) + 1;
    return node;
}

bool Red_Black_tree::is_Red(Red_Black_node *node) {
    if (node == nullptr) return false;
    return node->color == 'R';
}

bool Red_Black_tree::is_Black(Red_Black_node *node) {
    if (node == nullptr) return true;
    return node->color == 'B';
}

void Red_Black_tree::Add(int key) {
    auto * new_node = new Red_Black_node(key);
    root = Red_Black_insert(root, new_node);
    Fix_insert(root, new_node);
}

Red_Black_node *Red_Black_tree::Get_root() {
    return root;
}

void Red_Black_tree::Inorder_print(Red_Black_node *node) {
    if (node == nullptr) return;
    Inorder_print(node->left);
    // std::cout << node->key << " ";
    Inorder_print(node->right);
}

void Red_Black_tree::Del_min(Red_Black_node *&node)
{
    if (node->left != nullptr){
        Del_min(node->left);
        return;
    }
    if(node->right != nullptr) node->right->parent = node->parent;
    //delete node;
    node = nullptr;
}

void Red_Black_tree::Print() {
    Inorder_print(root);
}

Red_Black_node *Red_Black_tree::Get_min(Red_Black_node *node) {
    while (node->left != nullptr){
        node = node->left;
    }
    return node;
}

void Red_Black_tree::Red_Black_delete(Red_Black_node*& node, int key) {
    if(node == nullptr) return;
        if (node->key < key){
            Red_Black_delete(node->right, key);
            return;
        } else if (node->key > key) {
            Red_Black_delete(node->left, key);
            return;
        } else {
            if(is_Red(node) && node->left == nullptr && node->right == nullptr){
                delete node;
                node = nullptr;
                return;
            }
            if(node->left != nullptr && node->right != nullptr){
                auto min = Get_min(node->right);
                std::swap(node->key, min->key);
                //node->key = min->key;
                Red_Black_delete(node->right, min->key);
            } else if (is_Black(node) && (node->left != nullptr || node->right != nullptr)){
                if (node->left != nullptr){
                    std::swap(node->key, node->left->key);
                    Red_Black_delete(node->left, node->left->key);
                } else {
                    std::swap(node->key, node->right->key);
                    Red_Black_delete(node->right, node->right->key);
                }
            } else {
                Fix_delete(node);
                delete node;
                node = nullptr;
            }
            //return node;
        }
}

void Red_Black_tree::Delete(int key) {
    Red_Black_delete(root, key);
}

void Red_Black_tree::Fix_insert(Red_Black_node *&root_node, Red_Black_node *&node) {
    Red_Black_node* parent = nullptr;
    Red_Black_node* grandfather = nullptr;

    while ((node != root_node) && (node->color != 'B') && is_Red(node->parent)){
        parent = node->parent;
        grandfather = node->parent->parent;
        if (parent == grandfather->left){
            Red_Black_node* uncle = grandfather->right;
            if (uncle != nullptr && uncle->color == 'R'){
                grandfather->color = 'R';
                parent->color = 'B';
                uncle->color = 'B';
                node = grandfather;
            } else {
                if (node == parent->right){
                    Left_rotate(root, parent);
                    node = parent;
                    parent = node->parent;
                }

                Right_rotate(root, grandfather);
                std::swap(grandfather->color, parent->color);
                node = parent;
            }
        } else {
            Red_Black_node* uncle = grandfather->left;
            if ((uncle != nullptr) && (uncle->color == 'R')){
                grandfather->color = 'R';
                parent->color = 'B';
                uncle->color = 'B';
                node = grandfather;
            } else {
                if (node == parent->left){
                    Right_rotate(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                Left_rotate(root, grandfather);
                std::swap(grandfather->color, parent->color);
                node = parent;
            }
        }
    }
    root_node->color = 'B';
}

void Red_Black_tree::Fix_delete(Red_Black_node *node) {
    while (node != root && is_Black(node)){
        if (node->is_left_child()) {
            if (is_Black(node->Get_sibling()) && is_Red(node->Get_sibling_right())) {
                std::swap(node->Get_sibling()->color, node->parent->color);
                node->parent->color = 'B';
                node->Get_sibling()->color = 'B';
                Left_rotate(root, node->parent);
                return;
            } else if (is_Black(node->Get_sibling()) &&
                       is_Red(node->Get_sibling_left()) && is_Black(node->Get_sibling_right())) {
                std::swap(node->Get_sibling_left()->color, node->Get_sibling()->color);
                Right_rotate(root, node->parent->right);
            } else if (is_Black(node->Get_sibling()) &&
                       is_Black(node->Get_sibling_left()) && is_Black(node->Get_sibling_right())) {
                if (is_Red(node->parent)) {
                    node->Get_sibling()->color = 'R';
                    node->parent->color = 'B';
                    return;
                } else {
                    node = node->parent;
                }
            } else if (is_Red(node->Get_sibling())) {
                node->parent->color = 'R';
                node->Get_sibling()->color = 'B';
                Left_rotate(root, node->parent);
            }
        } else {
            if (is_Black(node->Get_sibling()) && is_Red(node->Get_sibling_left())){
                std::swap(node->Get_sibling()->color, node->parent->color);
                node->Get_sibling_left()->color = 'B';
                Right_rotate(root, node->parent);
                return;
            } else if (is_Black(node->Get_sibling()) && is_Red(node->Get_sibling_right()) &&
                       is_Black(node->Get_sibling_left())){
                std::swap(node->Get_sibling()->color, node->Get_sibling_right()->color);
                Left_rotate(root, node->parent->left);
            } else if (is_Black(node->Get_sibling()) &&
                       is_Black(node->Get_sibling_left()) && is_Black(node->Get_sibling_right())){
                if (is_Red(node->parent)){
                    node->Get_sibling()->color = 'R';
                    node->parent->color = 'B';
                    return;
                } else {
                    node->Get_sibling()->color = 'R';
                    node->parent->color = 'B';
                    node = node->parent;
                }
            } else if (is_Red(node->Get_sibling())){
                node->Get_sibling()->color = 'B';
                node->parent->color = 'R';
            }
        }
    }
}
