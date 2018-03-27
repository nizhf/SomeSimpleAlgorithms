#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

#include "BinaryTree.h"

template<typename T, typename K>
class BinarySearchTree : public BinaryTree<T, K> {
public:
    BinarySearchTree();
    ~BinarySearchTree();

    virtual bool insert(T data, K key) override;
    virtual bool insert(T data, K key, bool lr) override;

    virtual bool removeKey(K key) override;

    void rotate_left(struct BinaryTree<T, K>::Node *node);
    void rotate_right(struct BinaryTree<T, K>::Node *node);

    T search(K key);
    T minimum();
    T maximum();


};

template<typename T, typename K>
inline BinarySearchTree<T, K>::BinarySearchTree() : BinaryTree<T, K>() {

}

template<typename T, typename K>
inline BinarySearchTree<T, K>::~BinarySearchTree() {

}

template<typename T, typename K>
inline bool BinarySearchTree<T, K>::insert(T data, K key) {
    if (NULL == this->_root) {
        typename BinaryTree<T, K>::Node *newNode = new typename BinaryTree<T, K>::Node{key, data, NULL, NULL, NULL};
        this->_root = newNode;
        return true;
    }
    auto current = this->_root;
    typename BinaryTree<T, K>::Node *currentParent = NULL;
    while (current != NULL) {
        if (key < current->key) {
            currentParent = current;
            current = current->left;
        }
        else {
            currentParent = current;
            current = current->right;
        }
    }
    typename BinaryTree<T, K>::Node *newNode = new typename BinaryTree<T, K>::Node{key, data, currentParent, NULL, NULL};
    if (key < currentParent->key)
        currentParent->left = newNode;
    else
        currentParent->right = newNode;
    return true;
}

template<typename T, typename K>
inline bool BinarySearchTree<T, K>::insert(T data, K key, bool lr) {
    return this->insert(data, key);
}

template<typename T, typename K>
inline bool BinarySearchTree<T, K>::removeKey(K key) {
    auto current = this->_root;
    typename BinaryTree<T, K>::Node *node = NULL;
    if (NULL == current)
        return false;
    while (current != NULL) {
        if (current->key == key) {
            node = current;
            auto parent = node->parent;
            if (NULL == parent) {                                   //root node
                if (NULL == node->left && NULL == node->right) {
                    delete node;
                    this->_root = NULL;
                }
                else if (NULL == node->left) {
                    node->right->parent = NULL;
                    this->_root = node->right;
                    delete node;
                }
                else if (NULL == node->right) {
                    node->left->parent = NULL;
                    this->_root = node->left;
                    delete node;
                }
                else {
                    auto succ = this->successor(node);
                    if (succ != node->right) {
                        succ->parent->left = succ->right;
                        if (succ->right != NULL)
                            succ->right->parent = succ->parent;
                        succ->right = node->right;
                        node->right->parent = succ;
                    }
                    succ->parent = NULL;
                    succ->left = node->left;
                    node->left->parent = succ;
                    this->_root = succ;
                    delete node;
                }
            }
            else {
                if (NULL == node->left && NULL == node->right) {
                    if (parent->left == node)
                        parent->left = NULL;
                    else
                        parent->right = NULL;
                    delete node;
                }
                else if (NULL == node->left) {
                    if (parent->left == node)
                        parent->left = node->right;
                    else
                        parent->right = node->right;
                    node->right->parent = parent;
                    delete node;
                }
                else if (NULL == node->right) {
                    if (parent->left == node)
                        parent->left = node->left;
                    else
                        parent->right = node->left;
                    node->left->parent = parent;
                    delete node;
                }
                else {
                    auto succ = this->successor(node);
                    if (succ != node->right) {
                        succ->parent->left = succ->right;
                        if (succ->right != NULL)
                            succ->right->parent = succ->parent;
                        succ->right = node->right;
                        node->right->parent = succ;
                    }
                    succ->parent = parent;
                    if (parent->left == node)
                        parent->left = succ;
                    else
                        parent->right = succ;
                    succ->left = node->left;
                    node->left->parent = succ;
                    delete node;
                }
            }
            return true;
        }
        if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return false;
}

template<typename T, typename K>
inline T BinarySearchTree<T, K>::search(K key) {
    auto current = this->_root;
    if (NULL == current)
        return T();
    while (current != NULL) {
        if (current->key == key)
            return current->data;
        if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    throw("Not found!");
}

template<typename T, typename K>
inline T BinarySearchTree<T, K>::minimum() {
    auto temp = this->_root;
    if (NULL == temp)
        return T();
    while (temp->left != NULL) {
        temp = temp->left;
    }
    return temp->data;
}

template<typename T, typename K>
inline T BinarySearchTree<T, K>::maximum() {
    auto temp = this->_root;
    if (NULL == temp)
        return T();
    while (temp->right != NULL) {
        temp = temp->right;
    }
    return temp->data;
}

template<typename T, typename K>
inline void BinarySearchTree<T, K>::rotate_left(struct BinaryTree<T, K>::Node *node) {
    if (NULL == node)
        return;
    if (NULL == node->parent)
        return;

    auto parent = node->parent;
    auto grandparent = parent->parent;
    parent->right = node->left;
    if (node->left != NULL)
        node->left->parent = parent;
    node->parent = grandparent;
    node->left = parent;
    parent->parent = node;
    if (NULL == grandparent) {
        this->_root = node;
    }
    else {
        if (parent == grandparent->left)
            grandparent->left = node;
        else
            grandparent->right = node;
    }
}

template<typename T, typename K>
inline void BinarySearchTree<T, K>::rotate_right(struct BinaryTree<T, K>::Node *node) {
    if (NULL == node)
        return;
    if (NULL == node->parent)
        return;

    auto parent = node->parent;
    auto grandparent = parent->parent;
    parent->left = node->right;
    if (node->right != NULL)
        node->right->parent = parent;
    node->parent = grandparent;
    node->right = parent;
    parent->parent = node;
    if (NULL == grandparent) {
        this->_root = node;
    }
    else {
        if (parent == grandparent->left)
            grandparent->left = node;
        else
            grandparent->right = node;
    }
}




#endif // BINARYSEARCHTREE_H_INCLUDED
