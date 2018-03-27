#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include <functional>
#include "../List/MyQueue.h"

template<typename T, typename K>
class BinaryTree {
public:
    struct Node {
        K key;
        T data;
        struct Node *parent, *left, *right;
    };

    explicit BinaryTree(BinaryTree<T, K> *bt = 0);
    explicit BinaryTree(struct Node *node);
    virtual ~BinaryTree();

    void initialize();

    bool isEmpty();

    struct Node* root();
    struct Node* successor(struct Node *node);

    virtual bool insert(T data, K key); //insert data at the first not full node
    virtual bool insert(T data, K key, bool lr); //true - left, false - right
//    void insert(BinaryTree<T, K> &bt, bool lr);
    virtual bool removeKey(K key);
    virtual bool removeData(T data);

    int depth();
    int depth(struct Node *node);
    int size();

    void traversePre(struct Node *node, std::function<void(struct Node *)> visit);
    void traverseIn(struct Node *node, std::function<void(struct Node *)> visit);
    void traversePost(struct Node *node, std::function<void(struct Node *)> visit);
    void traverseLevel(struct Node *node, std::function<void(struct Node *)> visit);

protected:
    struct Node *_root;

private:
    int DFSDepth(struct Node *node);

};

template<typename T, typename K>
inline BinaryTree<T, K>::BinaryTree(BinaryTree<T, K> *bt) {
    if (bt)
        _root = bt->root();
    else
        _root = NULL;
}

template<typename T, typename K>
inline BinaryTree<T, K>::BinaryTree(struct Node *node) {
    _root = node;
}

template<typename T, typename K>
inline BinaryTree<T, K>::~BinaryTree() {
    traversePost(_root, [&](struct Node *node){delete node;});
}

template<typename T, typename K>
inline void BinaryTree<T, K>::initialize() {
    traversePost(_root, [&](struct Node *node){delete node;});
    _root = NULL;
}

template<typename T, typename K>
inline bool BinaryTree<T, K>::isEmpty() {
    return NULL == _root;
}

template<typename T, typename K>
inline struct BinaryTree<T, K>::Node* BinaryTree<T, K>::root() {
    return _root;
}

template<typename T, typename K>
inline struct BinaryTree<T, K>::Node* BinaryTree<T, K>::successor(struct Node *node) {
    if (NULL == node)
        return NULL;
    if (NULL == node->parent && NULL == node->right)
        return NULL;
    if (NULL == node->right)
        return node->parent;
    struct Node *temp = node->right;
    while (temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}

template<typename T, typename K>
inline bool BinaryTree<T, K>::insert(T data, K key) {
    if (NULL == _root) {
        struct Node *newNode = new Node{key, data, NULL, NULL, NULL};
        _root = newNode;
        return true;
    }

    MyQueue<struct Node *> q;
    q.enqueue(_root);
    while (!q.isEmpty()) {
        struct Node *temp = q.dequeue();
        if (NULL == temp->left) {
            struct Node *newNode = new Node{key, data, temp, NULL, NULL};
            temp->left = newNode;
            break;
        }
        if (NULL == temp->right) {
            struct Node *newNode = new Node{key, data, temp, NULL, NULL};
            temp->right = newNode;
            break;
        }
        q.enqueue(temp->left);
        q.enqueue(temp->right);
    }
    return true;
}

template<typename T, typename K>
inline bool BinaryTree<T, K>::insert(T data, K key, bool lr) {
    if (NULL == _root) {
        struct Node *newNode = new Node{key, data, NULL, NULL, NULL};
        _root = newNode;
        return true;
    }
    struct Node *temp = _root;
    if (lr) {
        while (temp->left != NULL)
        temp = temp->left;
        struct Node *newNode = new Node{key, data, temp, NULL, NULL};
        temp->left = newNode;
    }
    else {
        while (temp->right != NULL)
        temp = temp->right;
        struct Node *newNode = new Node{key, data, temp, NULL, NULL};
        temp->right = newNode;
    }
    return true;
}

template<typename T, typename K>
inline bool BinaryTree<T, K>::removeKey(K key) {
    traversePre(_root, [&](struct Node *node) {
                    if (node->key == key) {
                        auto parent = node->parent;
                        if (NULL == parent) {                                   //root node
                            if (NULL == node->left && NULL == node->right) {
                                delete node;
                                _root = NULL;
                            }
                            else if (NULL == node->left) {
                                node->right->parent = NULL;
                                _root = node->right;
                                delete node;
                            }
                            else if (NULL == node->right) {
                                node->left->parent = NULL;
                                _root = node->left;
                                delete node;
                            }
                            else {
                                auto succ = successor(node);
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
                                _root = succ;
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
                                auto succ = successor(node);
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
                    }
                });
    return true;
}

template<typename T, typename K>
inline bool BinaryTree<T, K>::removeData(T data) {
    traversePre(_root, [&](struct Node *node) {
                    if (node->data == data) {
                        auto parent = node->parent;
                        if (NULL == parent) {                                   //root node
                            if (NULL == node->left && NULL == node->right) {
                                delete node;
                                _root = NULL;
                            }
                            else if (NULL == node->left) {
                                node->right->parent = NULL;
                                _root = node->right;
                                delete node;
                            }
                            else if (NULL == node->right) {
                                node->left->parent = NULL;
                                _root = node->left;
                                delete node;
                            }
                            else {
                                auto succ = successor(node);
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
                                _root = succ;
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
                                auto succ = successor(node);
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
                    }
                });
    return true;
}

template<typename T, typename K>
inline int BinaryTree<T, K>::size() {
    int _size = 0;
    traversePre(_root, [&_size](struct Node *node){_size++;});
    return _size;
}

template<typename T, typename K>
inline int BinaryTree<T, K>::depth() {
    return DFSDepth(_root);
}

template<typename T, typename K>
inline int BinaryTree<T, K>::depth(struct Node *node) {
    return DFSDepth(node);
}

template<typename T, typename K>
inline int BinaryTree<T, K>::DFSDepth(struct Node *node) {
    int i = 0, j = 0;
    if (NULL == node)
        return 0;
    if (NULL != node->left)
        i = DFSDepth(node->left);
    if (NULL != node->right)
        j = DFSDepth(node->right);
    return i > j ? i + 1: j + 1;
}

template<typename T, typename K>
inline void BinaryTree<T, K>::traversePre(struct Node *node, std::function<void(struct Node *)> visit) {
    if (NULL == node)
        return;
    visit(node);
    traversePre(node->left, visit);
    traversePre(node->right, visit);
}

template<typename T, typename K>
inline void BinaryTree<T, K>::traverseIn(struct Node *node, std::function<void(struct Node *)> visit) {
    if (NULL == node)
        return;
    traverseIn(node->left, visit);
    visit(node);
    traverseIn(node->right, visit);
}

template<typename T, typename K>
inline void BinaryTree<T, K>::traversePost(struct Node *node, std::function<void(struct Node *)> visit) {
    if (NULL == node)
        return;
    traversePost(node->left, visit);
    traversePost(node->right, visit);
    visit(node);
}

template<typename T, typename K>
inline void BinaryTree<T, K>::traverseLevel(struct Node *node, std::function<void(struct Node *)> visit) {
    MyQueue<struct Node *> q;
    if (NULL == node)
        return;
    q.enqueue(node);
    while (!q.isEmpty()) {
        struct Node *temp = q.dequeue();
        visit(temp);
        if (temp->left != NULL)
            q.enqueue(temp->left);
        if (temp->right != NULL)
            q.enqueue(temp->right);
    }
}


#endif // BINARYTREE_H_INCLUDED
