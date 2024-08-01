/*
 *  AVL_tree.cpp
 *  ENSF 694 Lab 5 - Exercise B
 *  Created by Mahmood Moussavi
 *  Created by Jeff Wheeler
 *  Submission date: August 2, 2024
 */

#include "AVL_tree.h"

AVLTree::AVLTree() : root(nullptr), cursor(nullptr){}

int AVLTree::height(const Node* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

int AVLTree::getBalance(Node* N) {
    return (height(N->right) - height(N->left));
}

Node* AVLTree::rightRotate(Node* node) {
    Node* pivot = node->left;
    
    node->left = pivot->right;
    if (pivot->right != nullptr)
        pivot->right->parent = node;    
    
    if (node->parent == nullptr)
        root = pivot;
    else if (node->parent->right == node)
        node->parent->right = pivot;
    else if (node->parent->left == node)
        node->parent->left = pivot;
    
    pivot->parent = node->parent;
    pivot->right = node;
    node->parent = pivot;
    node->height = 1;
    pivot->height = 2;
    return pivot;
}

Node* AVLTree::leftRotate(Node* node) {
    Node* pivot = node->right;

    node->right = pivot->left;
    if (pivot->left != nullptr)
        pivot->left->parent = node;

    if (node->parent == nullptr)
        root = pivot;
    else if (node->parent->right == node)
        node->parent->right = pivot;
    else if (node->parent->left == node)
        node->parent->left = pivot;

    pivot->parent = node->parent;
    pivot->left = node;
    node->parent = pivot;   
    node->height = 1;
    pivot->height = 2;
    return pivot;
}

void AVLTree::insert(int key, Type value) {
    root = insert(root, key, value, nullptr);
}

// Recursive function
Node* AVLTree::insert(Node* node, int key, Type value, Node* parent) {
    if (node == nullptr){ // setup initial root node
        return new Node(key, value, parent);
    }
    else if (key < node->data.key){ // insert lower key value to left
        node->left = insert(node->left, key, value, node);
    }
    else if (key > node->data.key){ // insert higher key value to right
        node->right = insert(node->right, key, value, node);
    }

    // adjust height of node
    if (height(node->left) > height(node->right)){
        node->height = height(node->left) + 1;
    }
    else if (height(node->left) < height(node->right)){
        node->height = height(node->right) + 1;
    }
    // else height stays the same

    // 4 cases
    if (getBalance(node) == -2){ 
        // LL
        if (key < node->left->data.key) {
            return rightRotate(node);
        }
         // LR
         node->left = leftRotate(node->left);
         return rightRotate(node);
    } 
    else if (getBalance(node) == 2){
        // RR
        if (key > node->data.key){
            return leftRotate(node);
        }
        // RL
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Recursive function
void AVLTree::inorder(const Node* root) {
    if (root == nullptr){
        return;
    }
    inorder(root->left);
    std::cout << "(" << root->data.key << " " << root->data.value << ")" << std::endl;
    inorder(root->right);
}

// Recursive function
void AVLTree::preorder(const Node* root) {
    if (root == nullptr){
        return;
    }
    std::cout << "(" << root->data.key << " " << root->data.value << ")" << std::endl;
    preorder(root->left);
    preorder(root->right);
}

// Recursive function
void AVLTree::postorder(const Node* root) {
    if (root == nullptr){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    std::cout << "(" << root->data.key << " " << root->data.value << ")" << std::endl;
}

const Node* AVLTree::getRoot(){
    return root;
}

void AVLTree::find(int key) {
    go_to_root();
    if(root != nullptr)
        find(root, key);
    else
        std::cout << "It seems that tree is empty, and key not found." << std::endl;
}

// Recursive funtion
void AVLTree::find(Node* node, int key){
    if (node == nullptr){
        return;
    }

    if (key == node->data.key){
        cursor = node;
        return;
    }
    
    if (key < node->data.key)
        find(node->left, key);
    else if (key > node->data.key)
        find(node->right, key);
}

AVLTree::AVLTree(const AVLTree& other) : root(nullptr), cursor(nullptr) {
    root = copy(other.root, nullptr);
    cursor = root;
}

AVLTree::~AVLTree() {
    destroy(root);
}

AVLTree& AVLTree::operator=(const AVLTree& other) {
    if (this == &other) return *this;
    destroy(root);
    root = copy(other.root, nullptr);
    cursor = root;
    return *this;
}

// Recursive funtion
Node* AVLTree::copy(Node* node, Node* parent) {
    if (node == nullptr)
        return nullptr;
    
    Node* new_node = new Node(node->data.key, node->data.value, parent);
    new_node->height = node->height;

    new_node->left = copy(node->left, new_node);
    new_node->right = copy(node->right, new_node);
    return new_node;
}

// Recusive function
void AVLTree::destroy(Node* node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
    root = nullptr;
}

const int& AVLTree::cursor_key() const{
    if (cursor != nullptr)
        return cursor->data.key;
    else {
        std::cout << "looks like tree is empty, as cursor == Zero.\n";
        exit(1);
    }
}

const Type& AVLTree::cursor_datum() const{
    if (cursor != nullptr)
        return cursor->data.value;
    else {
        std::cout << "looks like tree is empty, as cursor == Zero.\n";
        exit(1);
    }
}

int AVLTree::cursor_ok() const{
    if(cursor == nullptr)
        return 0;
    return 1;
}

void AVLTree::go_to_root(){
    //if(!root) 
    cursor = root;
    // cursor = nullptr;
}

