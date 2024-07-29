//
//  AVL tree.cpp
//  AVL tree
//
//  Created by Mahmood Moussavi on 2024-05-22.
//

#include "AVL_tree.h"

AVLTree::AVLTree() : root(nullptr), cursor(nullptr){}

int AVLTree::height(const Node* N) {
    // Student must complete and if necessary change the return value of 
    // this function this function
    return 0;
}

int AVLTree::getBalance(Node* N) {
    // Student must complete and if necessary change the return value of 
    // this function this function
    return 0;
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
     // Student must complete and if necessary change the return value of 
     // this function this function
     return nullptr;
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
void AVLTree::find(Node* root, int key){
    // Student must complete this function
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
    else{
        std::cout << "looks like tree is empty, as cursor == Zero.\n";
        exit(1);
    }
}

const Type& AVLTree::cursor_datum() const{
    if (cursor != nullptr)
        return cursor->data.value;
    else{
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
    if(!root) cursor = root;
    cursor = nullptr;
}

