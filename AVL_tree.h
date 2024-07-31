#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>

typedef std::string Type;

struct Pair {
    int key;
    Type value;
};

struct Node {
    Pair data;
    Node* left;
    Node* right;
    Node* parent;
    int height;

    Node(int k, Type v, Node* p = nullptr) : data{ k, v }, left(nullptr), right(nullptr), parent(p), height(1) {}
};

class AVLTree {
private:
    Node* root;
    Node* cursor;
    
    // PROMISES: if N is not a nullptr, returns the difference bet its left and right sub-trees. Otherwise, returns 0
    int getBalance(Node* N);

    // PROMISES: x points to a unbalanced node.Therefor, makes a right rotation and adjusts the new heights
    Node* rightRotate(Node* y);

    // PROMISES: x points to a unbalanced node.Therefor, makes a left rotation and adjusts the new heights
    Node* leftRotate(Node* x);
    
    // PROMISES: adds a new node with a given key and value to the tree, maintaining the tree's properties and
    // rebalancing the tree if necessary.
    Node* insert(Node* node, int key, Type value, Node* parent);
    
    void find(Node* root, int key);

    // Deallocate all nodes in th tree, and set root to zero.
    void destroy();

    // Establishes *this as a copy of source.  Cursor of *this will
    // point to the twin of whatever the source's cursor points t
    void copy(const AVLTree& source);
    
    Node* copy(Node* node, Node* parent);
    void destroy(Node* node);
    
public:
    AVLTree();
    ~AVLTree();
    AVLTree& operator= (const AVLTree& rsh);
    AVLTree(const AVLTree& src);

    // PROMISES: Returns number of keys in the table.
    int size() const;
    
    // PROMISES:
    //   Returns 1 if the cursor is attached to a key/datum pair,
    //   and 0 if the cursor is in the off-list state.
    int cursor_ok() const;
    
    // REQUIRES: cursor_ok()
    // PROMISES: Returns key of key/datum pair to which cursor is attached.
    const int& cursor_key() const;
    
    // REQUIRES: cursor_ok()
    // PROMISES: Returns datum of key/datum pair to which cursor is attached.
    const Type& cursor_datum() const;
    
    // PROMISE: serves as the interface for users to add new nodes to the AVL tree, and ensures that the tree's
    // properties are maintained by calling the private helper insert function, which handles the actual insertion
    // and rebalancing logic.
    void insert(int key, Type value);
    
    // PROMISES: if N is not a nullptr, returns the height sub-tree. Otherwise, returns 0
    int height(const Node* N);
    
    // PROMISES: nodes are visited in ascending order of their keys. This traversal method visits the left subtree,
    // the root node, and then the right subtree.
    void inorder(const Node* root);
    
    // PROMISES: nodes are visited in the following order: the root node, the left subtree, and then the right subtree.
    // Often used to create a copy of the tree or to serialize the tree for storage or transmission.
    void preorder(const Node* root);
    
    // PROMISES: nodes are visited in the following order: left subtree, right subtree, and then the root node.
    // Often used to delete or free nodes and to evaluate expression trees.
    void postorder(const Node* root);
    
    // PROMISES: if tree is not empty, cursor is moved to the root. Otherwise is set to nullptr.
    void go_to_root();
    
    void find(int key);

    // PROMISES: return pointer to the root node
    const Node* getRoot();
};

#endif // AVLTREE_H
