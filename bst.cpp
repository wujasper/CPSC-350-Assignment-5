/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 5
*/

#include <iostream>
#include "bstbase.cpp"

using namespace std;

// Node for binary search tree
template <class T>
class BSTNode {

public:
    T data;
    BSTNode  *left;
    BSTNode  *right;

    // default constructor
    BSTNode () {
        left = NULL;
        right = NULL;
    };
    // default destructor
    ~BSTNode () {
        delete left;
        delete right;
    };
    // constructor to set data
    BSTNode (T data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }

};

// Implementation of binary search tree
template <class T>
class BST: public virtual BSTBase<T> {
private:
    BSTNode<T> *root;

    BSTNode<T>* insertRecursive(BSTNode<T> *root, T data);
    BSTNode<T>* removeRecursive(BSTNode<T> *root, T data);
    BSTNode<T>* searchRecursive(BSTNode<T> *root, T data);
    BSTNode<T>* getParentRecursive(BSTNode<T> *root, T data);
    void printInorderRecursive(ostream& os, BSTNode<T> *root);
    void copyRecursive(const BSTNode<T> *obj);
    BSTNode<T>* findLeftMostNode(BSTNode<T> *root);
    BSTNode<T>* getParent(T data);
    void deleteTree(BSTNode<T> *root);

public:
    BST();
    ~BST();
    //BST(const BST &obj);
    void insert(T data);
    void remove(T data);
    T* search(T data);
    void printInorder(ostream& os);
    BST<T>& operator=(const BST<T> &obj);
};

// default constructor to set root to null
template <class T>
BST<T>::BST() {
    root = NULL;
}
// default destructor to delete binary search tree nodes
template <class T>
BST<T>::~BST() {
    deleteTree(root);
}
// insert data to the binary search tree
template <class T>
void BST<T>::insert(T data) {

    // if bst is empty, new node becomes root
    if (root == NULL) {
        root = new BSTNode<T>(data);
    }
    // otherwise, traverse and insert
    else {
        root = insertRecursive(root, data);
    }
}
// insert data to the binary search tree recursively
template <class T>
BSTNode<T>* BST<T>::insertRecursive(BSTNode<T> *root, T data) {

    if (root == NULL) {
        return (new BSTNode<T>(data));
    }
    if (data < root->data) {
        root->left = insertRecursive(root->left, data);
    }
    else {
        root->right = insertRecursive(root->right, data);
    }
    return root;
}
// find the leftmost node
template <class T>
BSTNode<T>* BST<T>::findLeftMostNode(BSTNode<T> *root) {
    BSTNode<T> *cur = root;

    while (cur != NULL && cur->left != NULL) {
        cur = cur->left;
    }
    return cur;
}
// remove data from the binary search tree
template <class T>
void BST<T>::remove(T data) {

    // if bst is empty, new node becomes root
    if (root != NULL) {
        root = removeRecursive(root, data);
    }
}
// remove data from the binary search tree recursively
template <class T>
BSTNode<T>* BST<T>::removeRecursive(BSTNode<T> *root, T data) {

    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = removeRecursive(root->left, data);
    }
    else if (data > root->data) {
        root->right = removeRecursive(root->right, data);
    }
    else {
        if (root->left == NULL && root->right == NULL) {
            return NULL;
        }
        else if (root->left == NULL) {
           BSTNode<T> *node = root->right;
           return node;
        }
        else if (root->right == NULL) {
           BSTNode<T> *node = root->left;
           return node;
        }

        BSTNode<T> *min = findLeftMostNode(root->right);
        root->data = min->data;
        root->right = removeRecursive(root->right, min->data);
    }
    return root;
}
// search data from the binary search tree
template <class T>
T* BST<T>::search(T data) {
    if (root == NULL) {
        return NULL;
    }
    else {
        BSTNode<T> *node = searchRecursive(root, data);
        if (node == NULL) {
            return NULL;
        }
        return &(node->data);
    }
}
// search data from the binary search tree recursively
template <class T>
BSTNode<T>* BST<T>::searchRecursive(BSTNode<T> *root, T data) {

    if (root == NULL) {
        return root;
    }
    if (data == root->data) {
        return root;
    }
    else if (data < root->data) {
        return searchRecursive(root->left, data);
    }
    else {
        return searchRecursive(root->right, data);
    }
}
// remove data from the binary search tree
template <class T>
BSTNode<T>* BST<T>::getParent(T data) {

    return getParentRecursive(root, data);
}
// remove data from the binary search tree recursively
template <class T>
BSTNode<T>* BST<T>::getParentRecursive(BSTNode<T> *root, T data) {

    if (root == NULL) {
        return NULL;
    }
    if (root->data == data) {
        return NULL;
    }
    if (root->left != NULL) {
       if (root->left->data == data) {
        return root;
       }
    }
    else if (root->right != NULL) {
        if (root->right->data == data) {
            return root;
        }
    }
    if (data < root->data) {
        return getParentRecursive(root->left, data);
    } else {
        return getParentRecursive(root->right, data);
    }
}
// print inorder from the binary search tree
template <class T>
void BST<T>::printInorder(ostream& os) {

    if (root != NULL) {
        printInorderRecursive(os, root);
    }
}
// print inorder from the binary search tree recursively
template <class T>
void BST<T>::printInorderRecursive(ostream& os, BSTNode<T> *root) {

    if (root != NULL) {
        printInorderRecursive(os, root->left);
        os << root->data;
        printInorderRecursive(os, root->right);
    }
}
// overload operator =
template <class T>
BST<T>& BST<T>::operator=(const BST<T> &obj) {

    if (this == &obj) {
        return *this;
    }

    copyRecursive(obj.root);
    return *this;
}
// copy binary search tree recursively
template <class T>
void BST<T>::copyRecursive(const BSTNode<T> *obj) {

    if (obj != NULL) {
        if (obj->left != NULL) {
            copyRecursive(obj->left);
        }
        insert(obj->data);
        if (obj->right != NULL) {
            copyRecursive(obj->right);
        }
    }
}
// delete binary search tree recursively
template <class T>
void BST<T>::deleteTree(BSTNode<T> *root) {

    if (root != NULL) {
        if (root->left != NULL) {
            deleteTree(root->left);
        }
        if (root->right != NULL) {
            deleteTree(root->right);
        }
        delete root;
    }
}
