#pragma once
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    inline static long long rotations = 0;
};

Node* insert(Node* root, int key);
Node* remove(Node* root, int key);
Node* find(Node* root, int key);
//глубина и количество поворотов
void printStats();

