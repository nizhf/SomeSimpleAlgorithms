#ifndef MYQUEUE_H_INCLUDED
#define MYQUEUE_H_INCLUDED

template<typename T>
class MyQueue {
public:
    MyQueue(); //First In First Out
    ~MyQueue();
    void clear();

    bool enqueue(T data);
    T dequeue();
    T back();
    T front();

    bool isEmpty();
    int size();


private:
    int start;
    int end;
    int maxLength;
    T *queue;
};

template<typename T>
inline MyQueue<T>::MyQueue() {
    start = 0;
    end = 0;
    maxLength = 16;
    queue = new T[maxLength];
}

template<typename T>
inline MyQueue<T>::~MyQueue() {
    delete queue;
}

template<typename T>
inline void MyQueue<T>::clear() {
    start = 0;
    end = 0;
    maxLength = 16;
    delete[] queue;
    queue = new T[maxLength];
}

template<typename T>
inline bool MyQueue<T>::enqueue(T data) {
    if (end == maxLength) {
        if (start == 0) {
            maxLength = maxLength * 2;
            T *newQueue;
            try {
                newQueue = new T[maxLength];
            }
            catch (std::exception &e) {
                std::cout << e.what();
                return false;
            }
            for (int i = 0; i < maxLength / 2; i++)
                newQueue[i] = queue[i];
            delete[] queue;
            queue = newQueue;
        }
        else {
            int currentLength = end - start;
            for (int i = 0; i < currentLength; i++)
                queue[i] = queue[start + i];
            start = 0;
            end = currentLength;
        }

    }
    queue[end] = data;
    end++;
    return true;
}

template<typename T>
inline T MyQueue<T>::dequeue() {
    if (isEmpty())
        throw "Queue is empty!";
    else {
        start++;
        return queue[start - 1];
    }
}

template<typename T>
inline T MyQueue<T>::back() {
    if (isEmpty())
        throw "Queue is empty!";
    else
        return queue[end - 1];
}

template<typename T>
inline T MyQueue<T>::front() {
    if (isEmpty())
        throw "Queue is empty!";
    else
        return queue[start];
}

template<typename T>
inline bool MyQueue<T>::isEmpty() {
    return end == start;
}

template<typename T>
inline int MyQueue<T>::size() {
    return end - start;
}


#endif // MYQUEUE_H_INCLUDED
