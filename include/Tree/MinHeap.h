#ifndef MINHEAP_H_INCLUDED
#define MINHEAP_H_INCLUDED

#include "BinaryTree.h"

template<typename T, typename K>
class MinHeap : public BinaryTree<T, K> {
public:
    MinHeap();
    ~MinHeap();

    bool insert(T data, K key) override;
    bool insert(T data, K key, bool lr) override;

    T extractMin();

    void minHeapify(struct BinaryTree<T, K>::Node *node);

    static MinHeap<T, K>* buildMinHeap(BinaryTree<T, K> &bt);

    static T* heapSort(T *arr, int length);

private:


};

template<typename T, typename K>
inline MinHeap<T, K>::MinHeap() : BinaryTree<T, K>() {

}

template<typename T, typename K>
inline MinHeap<T, K>::~MinHeap() {

}

template<typename T, typename K>
inline bool MinHeap<T, K>::insert(T data, K key) {
    bool success = BinaryTree<T, K>::insert(data, key);
    if (success)
        this->traversePost(this->_root, [&](struct BinaryTree<T, K>::Node *node){minHeapify(node);});
    return success;
}

template<typename T, typename K>
inline bool MinHeap<T, K>::insert(T data, K key, bool lr) {
    return insert(data, key);
}

template<typename T, typename K>
inline T MinHeap<T, K>::extractMin() {
    auto currentRoot = this->_root;
    if (NULL == currentRoot)
        return T();
    T data = currentRoot->data;
    if (NULL == currentRoot->left && NULL == currentRoot->right) {
        this->_root = NULL;
        delete currentRoot;
        return data;
    }
    if (NULL == currentRoot->left) {
        currentRoot->right->parent = NULL;
        this->_root = currentRoot->right;
        delete currentRoot;
        return data;
    }
    if (NULL == currentRoot->right) {
        currentRoot->left->parent = NULL;
        this->_root = currentRoot->left;
        delete currentRoot;
        return data;
    }

    struct BinaryTree<T, K>::Node *lastNode = NULL;
    this->traverseLevel(currentRoot, [&](struct BinaryTree<T, K>::Node *node){lastNode = node;});
    if (lastNode == currentRoot->right) {
        lastNode->left = currentRoot->left;
        currentRoot->left->parent = lastNode;
    }
    else {
        if (lastNode == lastNode->parent->left)
            lastNode->parent->left = NULL;
        else
            lastNode->parent->right = NULL;
        lastNode->left = currentRoot->left;
        currentRoot->left->parent = lastNode;
        lastNode->right = currentRoot->right;
        currentRoot->right->parent = lastNode;
    }
    lastNode->parent = NULL;
    this->_root = lastNode;
    delete currentRoot;
    minHeapify(this->_root);
    return data;
}

template<typename T, typename K>
inline void MinHeap<T, K>::minHeapify(struct BinaryTree<T, K>::Node *node) {
    if (NULL == node->left && NULL == node->right)
        return;
    struct BinaryTree<T, K>::Node *temp;
    if (NULL == node->left)
        temp = node->right;
    else if (NULL == node->right)
        temp = node->left;
    else
        temp = node->left->key < node->right->key ? node->left : node->right;
    if (temp->key < node->key) {
        int tempKey = node->key;
        node->key = temp->key;
        temp->key = tempKey;
        T tempData = node->data;
        node->data = temp->data;
        temp->data = tempData;
        minHeapify(temp);
    }
}

template<typename T, typename K>
inline MinHeap<T, K>* MinHeap<T, K>::buildMinHeap(BinaryTree<T, K> &bt) {
    MinHeap<T, K> *mh = new MinHeap<T, K>;
    bt.traversePre(bt.root(), [&](struct BinaryTree<T, K>::Node *node){mh->insert(node->data, node->key);});
    return mh;
}

template<typename T, typename K>
inline T* MinHeap<T, K>::heapSort(T *arr, int length) {
    MinHeap<T, T> mh;
    for (int i = 0; i < length; i++) {
        mh.insert(arr[i], arr[i]);
    }
    for (int i = 0; i < length; i++) {
        arr[i] = mh.extractMin();
    }
    return arr;
}


#endif // MINHEAP_H_INCLUDED
