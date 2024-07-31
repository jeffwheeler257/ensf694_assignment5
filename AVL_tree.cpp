/*
 *  AVL_tree.cpp
 *  ENSF 694 Lab 4 - Exercise D
 *  Created by Mahmood Moussavi
 *  Created by Jeff Wheeler
 *  Submission date: August 2, 2024
 */

#include "AVL_tree.h"

AVLTree::AVLTree() : root(nullptr), cursor(nullptr){}

int AVLTree::height(const Node* N) {
    return N->height;
}

int AVLTree::getBalance(Node* N) {
    return (N->right->height - N->left->height);
}

Node* AVLTree::rightRotate(Node* y) {
    // Student must complete and if necessary change the return value of 
    // this function this function
    return nullptr;
 }

 Node* AVLTree::leftRotate(Node* x) {
     // Student must complete and if necessary change the return value of 
     // this function this function
     return nullptr;
 }

void AVLTree::insert(int key, Type value) {
    root = insert(root, key, value, nullptr);
}

// Recursive function
 Node* AVLTree::insert(Node* node, int key, Type value, Node* parent) {
    if (node == nullptr){ // setup initial root node
        return new Node(key, value, node);
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

    // check 4 cases
    if (getBalance(node) == -2){ 
        if (key < node->left->data.key) { //LL
            //rotate node right
            //return node
        }
         // LR
         // rotate node->left left
         // rotate node right
         // return node
    } 
    else if (getBalance(node) == 2){
        if (key > node->data.key){ // RR
            // rotate node left
            // return node
        }
        // RL
        // rotate node->right right 
        // rotate node left
        // return node
    }
 }

// Recursive function
void AVLTree::inorder(const Node* root) {
    // Student must complete this function
}

// Recursive function
void AVLTree::preorder(const Node* root) {
    // Student must complete this function
}

// Recursive function
void AVLTree::postorder(const Node* root) {
    // Student must complete this function
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
        std::cout << "Key not found" << std::endl;
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
    // Student must complete and if necessary change the return value of this function this function
    return nullptr;
}

// Recusive function
void AVLTree::destroy(Node* node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
    // Student must complete this function
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

