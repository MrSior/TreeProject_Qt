#include "avl_tree.h"

int AVL_tree::Get_balance_factor(AVL_node *node) {
    if (node == nullptr) return 0;
    return Get_height(node->left) - Get_height(node->right);
}

int AVL_tree::Get_height(AVL_node *node) {
    if (node == nullptr){
        return 0;
    }
    return node->height;
}

void AVL_tree::Insert(int key) {
    root = AVL_insert(root, key);
}


/*  LEFT ROTATE
 *      x                        y
 *     / \                      / \
 *    T1  y      ------->      x   T3
 *       / \                  / \
 *      T2  T3               T1  T2
 */

AVL_node *AVL_tree::Left_rotate(AVL_node *node_x) {
    AVL_node* node_y = node_x->right;
    AVL_node* T2 = node_y->left;

    node_x->right = T2;
    node_y->left = node_x;

    node_x->height = std::max(Get_height(node_x->left), Get_height(node_x->right)) + 1;
    node_y->height = std::max(Get_height(node_y->left), Get_height(node_y->right)) + 1;

    return node_y;
}

/*  RIGHT ROTATE
 *      y                   x
 *     / \                 / \
 *    x   T3   ------->   T1  y
 *   / \                     / \
 *  T1  T2                  T2  T3
 */

AVL_node *AVL_tree::Right_rotate(AVL_node *node_y) {
    AVL_node* node_x = node_y->left;
    AVL_node* T2 = node_x->right;

    node_x->right = node_y;
    node_y->left = T2;

    node_y->height = std::max(Get_height(node_y->left), Get_height(node_y->right)) + 1;
    node_x->height = std::max(Get_height(node_x->left), Get_height(node_x->right)) + 1;

    return node_x;
}

AVL_node* AVL_tree::AVL_insert(AVL_node* node, int key) {

    if (node == nullptr){
        return new AVL_node(key);
    }

    if (key < node->key){
        node->left = AVL_insert(node->left, key);
    } else if (key > node->key){
        node->right = AVL_insert(node->right, key);
    } else {
        return node;
    }

    node->height = std::max(Get_height(node->left), Get_height(node->right)) + 1;

    int balance_factor = Get_balance_factor(node);

    if (balance_factor > 1 && key < node->left->key){
        /* x and y on path from inserted value to z
         *       node
         *       / \
         *      y   T4
         *     / \
         *    x  T3
         *   / \
         *  T1 T2
         */
        return Right_rotate(node);
    } else if (balance_factor > 1 && key > node->left->key){
        /* x and y on path from inserted value to z
         *        node
         *        / \
         *       y   T4
         *      / \
         *     T1  x
         *        / \
         *       T2 T3
         */
        node->left = Left_rotate(node->left);
        return Right_rotate(node);
    }

    if (balance_factor < -1 && key < node->right->key){
        /* x and y on path from inserted value to z
         *         node
         *         / \
         *        T1  y
         *           / \
         *          x  T4
         *         / \
         *        T2 T3
         */
        node->right = Right_rotate(node->right);
        return Left_rotate(node);
    } else if (balance_factor < -1 && key > node->right->key){
        /* x and y on path from inserted value to z
         *        node
         *        / \
         *       T1  y
         *          / \
         *         T2  x
         *            / \
         *           T3 T4
         */
        return Left_rotate(node);
    }

    return node;
}

void AVL_tree::Print_inorder(AVL_node* node) {
    if (node == nullptr) return;
    Print_inorder(node->left);
    qDebug() << node->key << " ";
    Print_inorder(node->right);
}

AVL_node *AVL_tree::Get_root()
{
    return root;
}

void AVL_tree::Print() {
    Print_inorder(root);
}

void AVL_tree::Delete(int key) {
    AVL_delete(root, key);
}

AVL_node *AVL_tree::AVL_delete(AVL_node *node, int key) {
    if (node == nullptr){
        return node;
    }

    if (node->key > key){
        node->left = AVL_delete(node->left, key);
    } else if (node->key < key){
        node->right = AVL_delete(node->right, key);
    } else {
        if (node->left == nullptr || node->right == nullptr){
            AVL_node* tmp = node->left ? node->left : node->right;

            if (tmp == nullptr){
                tmp = node;
                node = nullptr;
                free(tmp);
            } else {
                *node = *tmp;
                free(tmp);
            }
        } else {
            AVL_node* tmp = Get_min(node->right);
            node->key = tmp->key;
            node->right = AVL_delete(node->right, node->key);
        }
    }

    if (node == nullptr) return node;

    node->height = std::max(Get_height(node->left), Get_height(node->right)) + 1;

    int balance_factor = Get_balance_factor(node);

    if (balance_factor > 1 && Get_balance_factor(node->left) >= 0) {
        return Right_rotate(node);
    } else if (balance_factor > 1 && Get_balance_factor(node->left) < 0){
        node->left = Left_rotate(node->left);
        return Right_rotate(node);
    }

    if (balance_factor < -1 && Get_balance_factor(node->right) <= 0){
        return Left_rotate(node);
    } else if (balance_factor < -1 && Get_balance_factor(node->right) > 0) {
        node->right = Right_rotate(node->right);
        return Left_rotate(node);
    }

    return node;
}

AVL_node *AVL_tree::Get_min(AVL_node *node) {
    while (node->left != nullptr){
        node = node->left;
    }
    return node;
}
