#include "avl.h"
#include <iostream>
#include <cassert>
#include <algorithm>

//вспомогательные функции для реализации avl-дерева
namespace {
int treeDepth = 0;

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
        root = new Node{key, nullptr, nullptr, 1};
    } else if (key < root->key) {
        root->left = insert(root->left, key);
        root = balance(root);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
        root = balance(root);
    }

    treeDepth = getHeight(root);
    return root;
}

Node* remove(Node* root, int key)
{
    if(root == nullptr) return nullptr;

    if(key < root->key) root->left = remove(root->left, key);
    else if(key > root->key) root->right = remove(root->right, key);
    else{
        if(root->left == nullptr || root->right == nullptr){
             Node* child = root->left ? root->left : root->right;
             
             if(child == nullptr){
                delete root;
                return nullptr;
             }else{
                Node* old = root;
                root = child;
                delete old;
             }
        }else{
            Node* kid = root->right;
            while(kid->left != nullptr){kid = kid->left;}
            root->key = kid->key;
            root->right = remove(root->right, kid->key);
            }
        }
    root = balance(root);
    return root;
}  
Node* find(Node* root, int key) {
    treeDepth = getHeight(root);
    while (root != nullptr && root->key != key) {
        root = key < root->key ? root->left : root->right;
    }
    return root;
}

void printStats() {
    std::cout << "Depth: " << treeDepth << '\n'
              << "Rotations: " << Node::rotations << '\n';
}

