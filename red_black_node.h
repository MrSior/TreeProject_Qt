#ifndef RED_BLACK_NODE_H
#define RED_BLACK_NODE_H


class Red_Black_node
{
public:
    int key;
    char color; // 1 - red   0 - black
    int height;
    Red_Black_node* left;
    Red_Black_node* right;
    Red_Black_node* parent;

    Red_Black_node(){
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        height = 1;
        color = 'R';
        key = 0;
    }

    explicit Red_Black_node(int key, char color = 'R'){
        this->key = key;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        this->color = color;
        height = 1;
    }

    Red_Black_node* Get_grandfather();
    Red_Black_node* Get_uncle();
    Red_Black_node* Get_sibling();
    Red_Black_node* Get_sibling_left();
    Red_Black_node* Get_sibling_right();

    bool is_left_child(){
        return this == parent->left;
    }

    bool is_right_child(){
        return this == parent->right;
    }
};

#endif // RED_BLACK_NODE_H
