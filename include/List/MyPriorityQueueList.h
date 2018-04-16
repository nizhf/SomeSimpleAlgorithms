#ifndef MYPRIORITYQUEUELIST_H_INCLUDED
#define MYPRIORITYQUEUELIST_H_INCLUDED

#include "MyList.h"

template<typename T>
class MyPriorityQueueList : public MyList<T>
{
public:
    MyPriorityQueueList();

    T extractMin();
    T minimum();

    bool insert(T data, int key);

private:

};

template<typename T>
inline MyPriorityQueueList<T>::MyPriorityQueueList() {

}

template<typename T>
inline T MyPriorityQueueList<T>::extractMin() {
    return this->popFront();
}

template<typename T>
inline T MyPriorityQueueList<T>::minimum() {
    return this->front();
}

template<typename T>
inline bool MyPriorityQueueList<T>::insert(T data, int key) {
    this->pushBack(data, key);
    this->sortKey();
    return true;
}




#endif // MYPRIORITYQUEUELIST_H_INCLUDED
