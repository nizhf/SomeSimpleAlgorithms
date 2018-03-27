#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#include "BinarySearchTree.h"

template<typename T, typename K>
class AVLTree : public BinarySearchTree<T, K> {
public:
    AVLTree();
    ~AVLTree();

    bool insert(T data, K key) override;
    bool insert(T data, K key, bool lr) override;

    bool removeKey(K key) override;
    bool removeData(T data) override;

};

template<typename T, typename K>
inline AVLTree<T, K>::AVLTree() : BinarySearchTree<T, K>() {

}

template<typename T, typename K>
inline AVLTree<T, K>::~AVLTree() {

}

template<typename T, typename K>
inline bool AVLTree<T, K>::insert(T data, K key) {
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

    auto temp = newNode;
    while (temp != NULL) {
        int depthDiff = this->depth(temp->left) - this->depth(temp->right);
        if (depthDiff > 1) {
            if (this->depth(temp->left->left) - this->depth(temp->left->right) < 0) {
                this->rotate_left(temp->left->right);
                this->rotate_right(temp->left);
            }
            else
                this->rotate_right(temp->left);
        }
        else if (depthDiff < -1) {
            if (this->depth(temp->right->left) - this->depth(temp->right->right) > 0) {
                this->rotate_right(temp->right->left);
                this->rotate_left(temp->right);
            }
            else
                this->rotate_left(temp->right);
        }
        temp = temp->parent;
    }
    return true;
}

template<typename T, typename K>
inline bool AVLTree<T, K>::insert(T data, K key, bool lr) {
    return insert(data, key);
}

template<typename T, typename K>
inline bool AVLTree<T, K>::removeKey(K key) {
    auto current = this->_root;
    typename BinaryTree<T, K>::Node *node = NULL;
    if (NULL == current)
        return false;
    while (current != NULL) {
        if (current->key == key) {
            node = current;
            auto parent = node->parent;
            if (NULL == parent) {                                   //root node
                if (NULL == node->left && NULL == node->right)
                    this->_root = NULL;
                else if (NULL == node->left) {
                    node->right->parent = NULL;
                    this->_root = node->right;
                }
                else if (NULL == node->right) {
                    node->left->parent = NULL;
                    this->_root = node->left;
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
                }
            }
            else {
                if (NULL == node->left && NULL == node->right) {
                    if (parent->left == node)
                        parent->left = NULL;
                    else
                        parent->right = NULL;
                }
                else if (NULL == node->left) {
                    if (parent->left == node)
                        parent->left = node->right;
                    else
                        parent->right = node->right;
                    node->right->parent = parent;
                }
                else if (NULL == node->right) {
                    if (parent->left == node)
                        parent->left = node->left;
                    else
                        parent->right = node->left;
                    node->left->parent = parent;
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
                }
            }

            auto temp = node;
            while (temp != NULL) {
                int depthDiff = this->depth(temp->left) - this->depth(temp->right);
                if (depthDiff > 1) {
                    if (this->depth(temp->left->left) - this->depth(temp->left->right) < 0) {
                        this->rotate_left(temp->left->right);
                        this->rotate_right(temp->left);
                    }
                    else
                        this->rotate_right(temp->left);
                }
                else if (depthDiff < -1) {
                    if (this->depth(temp->right->left) - this->depth(temp->right->right) > 0) {
                        this->rotate_right(temp->right->left);
                        this->rotate_left(temp->right);
                    }
                    else
                        this->rotate_left(temp->right);
                }
                temp = temp->parent;
            }
            delete node;
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
inline bool AVLTree<T, K>::removeData(T data) {
    this->traversePre(this->_root, [&](struct BinaryTree<T, K>::Node *node) {
                    if (node->data == data) {
                        auto parent = node->parent;
                        if (NULL == parent) {                                   //root node
                            if (NULL == node->left && NULL == node->right)
                                this->_root = NULL;
                            else if (NULL == node->left) {
                                node->right->parent = NULL;
                                this->_root = node->right;
                            }
                            else if (NULL == node->right) {
                                node->left->parent = NULL;
                                this->_root = node->left;
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
                            }
                        }
                        else {
                            if (NULL == node->left && NULL == node->right) {
                                if (parent->left == node)
                                    parent->left = NULL;
                                else
                                    parent->right = NULL;
                            }
                            else if (NULL == node->left) {
                                if (parent->left == node)
                                    parent->left = node->right;
                                else
                                    parent->right = node->right;
                                node->right->parent = parent;
                            }
                            else if (NULL == node->right) {
                                if (parent->left == node)
                                    parent->left = node->left;
                                else
                                    parent->right = node->left;
                                node->left->parent = parent;
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
                            }
                        }

                        auto temp = node;
                        while (temp != NULL) {
                            int depthDiff = this->depth(temp->left) - this->depth(temp->right);
                            if (depthDiff > 1) {
                                if (this->depth(temp->left->left) - this->depth(temp->left->right) < 0) {
                                    this->rotate_left(temp->left->right);
                                    this->rotate_right(temp->left);
                                }
                                else
                                    this->rotate_right(temp->left);
                            }
                            else if (depthDiff < -1) {
                                if (this->depth(temp->right->left) - this->depth(temp->right->right) > 0) {
                                    this->rotate_right(temp->right->left);
                                    this->rotate_left(temp->right);
                                }
                                else
                                    this->rotate_left(temp->right);
                            }
                            temp = temp->parent;
                        }
                        delete node;
                    }
                });
    return true;
}

#endif // AVLTREE_H_INCLUDED
