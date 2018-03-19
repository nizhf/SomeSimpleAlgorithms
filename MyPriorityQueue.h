#ifndef MYPRIORITYQUEUE_H_INCLUDED
#define MYPRIORITYQUEUE_H_INCLUDED

#include "MyList.h"

template<typename T>
class MyPriorityQueue : public MyList<T>
{
public:
    MyPriorityQueue();
    ~MyPriorityQueue();

    T extractMin();
    T minimum();

    bool insert(T data, int key);

private:

};

template<typename T>
inline MyPriorityQueue<T>::MyPriorityQueue() {

}

template<typename T>
inline MyPriorityQueue<T>::~MyPriorityQueue() {

}

template<typename T>
inline T MyPriorityQueue<T>::extractMin() {
    return this->popFront();
}

template<typename T>
inline T MyPriorityQueue<T>::minimum() {
    return this->front();
}

template<typename T>
inline bool MyPriorityQueue<T>::insert(T data, int key) {
    this->pushBack(data, key);
    this->sortKey();
    return true;
}




#endif // MYPRIORITYQUEUE_H_INCLUDED
