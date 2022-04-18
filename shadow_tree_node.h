#ifndef SHADOW_TREE_NODE_H
#define SHADOW_TREE_NODE_H

#include "string"

class Shadow_tree_node
{
public:
    int key;
    int priority;
    char color;

    int level, column;
    Shadow_tree_node*left, *right;
};

#endif // SHADOW_TREE_NODE_H
