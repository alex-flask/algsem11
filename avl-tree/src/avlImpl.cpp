#include "avl.h"
#include <cassert>
#include <algorithm>

//вспомогательные функции для реализации avl-дерева
namespace {
//высота узла
int getHeight(Node* node) {
    return node == nullptr ? 0 : node->height;
}

//обновить высоту узла
void updateHeight(Node* node) {
    node->height = 1 + std::max(
        getHeight(node->left),
        getHeight(node->right)
    );
}

//получить фактор балансировки
int getBalance(Node* node) {
    return getHeight(node->left)
         - getHeight(node->right);
}

//поворот вправо
Node *rotateRight(Node *y) {
    Node* x = y->left;
    Node* b = x->right;

    x->right = y;
    y->left = b;

    updateHeight(y);
    updateHeight(x);

    Node::rotations++;
    return x;
}

//поворот влево
Node *rotateLeft(Node *y) {
    Node *x = y->right;
    Node *b = x->left;

    x->left = y;
    y->right = b;
    
    updateHeight(y);
    updateHeight(x);

    Node::rotations++;
    return x;
}

//балансировка узла
Node *balance(Node *y) {
    assert(y != nullptr);
    updateHeight(y);
    int bf = getBalance(y);

    if (bf > 1) {
        if (getBalance(y->left) < 0)
            y->left = rotateLeft(y->left);
        return rotateRight(y);
    } else if (bf < -1) {
        if (getBalance(y->right) > 0)
            y->right = rotateRight(y->right);
        return rotateLeft(y);
    }
    return y;
}
}
Node *insert(Node* root, int key)
{
    if (root == nullptr) {
        Node *res = new Node{key, nullptr, nullptr, 1};
        return res;
    }
    if (key < root->key) 
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;
    
    root = balance(root);
    return root;
}
Node* remove(Node* root, int key);
Node* find(Node* root, int key);
void printStats();
