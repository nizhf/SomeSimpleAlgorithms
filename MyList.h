#ifndef MYLIST_H_INCLUDED
#define MYLIST_H_INCLUDED

#include "Element.h"

template<typename T>
class MyList
{
public:
    MyList();
    ~MyList();

    void initialize();

    //all index begins with 0!
    T at(int position) const;
    int keyAt(int position) const;
    T back() const; //return the last Element
    T front() const; //return the first Element
    T popBack(); //return the last Element and delete it
    T popFront(); //return the first Element and delete it

    bool pushBack(T data, int key = 0); //insert the Element after the last Element
    bool pushFront(T data, int key = 0); //insert the Element in front of the first Element

    bool insert(int position, T data, int key = 0); //insert the Element after the position
    bool remove(int position); //remove the Element on position
    bool removeKey(int key); //remove all Elements with key
    bool removeData(T data); //remove all Elements with data

    int size() const; //return the length of the List

    void sort(bool sequence = true); //true: increased; false: decreased
    void sortKey(bool sequence = true);
    void sortSelection(bool sequence = true);

    bool swap(int i1, int i2); //swap data and keys with index i1 and i2
    bool swapElement(int i1, int i2); //swap Elements with index i1 and i2
    bool swapIgnoreKey(int i1, int i2); //only swap data, not the key
    T search(int key) const; //return the first data with key
    T* searchAll(int key) const; //return all data with key
    int searchCount(int key) const; //return the count of data with key

    bool changeKeyAt(int index, int key);
    bool changeKeyWithData(T data, int key);
    bool changeKey(int keyPrevious, int key);

    template<typename U> friend std::ostream& operator<<(std::ostream &os, const MyList<U> &l);


private:
    struct ElementSort {
        int key;
        T data;
    };
    Element<T> *first; //first Element with index 0
    Element<T> *last; //last Element with index length - 1, the newest inserted Element
    int length;

    void quickSort(struct ElementSort arr[], int a, int b, bool dataOrKey, bool order); //data - true, key - false;

};

template<typename T>
inline MyList<T>::MyList() {
    first = NULL;
    last = NULL;
    length = 0;
}

template<typename T>
inline MyList<T>::~MyList() {
    Element<T> *temp = first;
    while (first != NULL) {
        first = first->next;
        delete temp;
        temp = first;
    }
}

template<typename T>
inline void MyList<T>::initialize() {
    Element<T> *temp = first;
    while (first != NULL) {
        first = first->next;
        delete temp;
        temp = first;
    }
    first = NULL;
    last = NULL;
    length = 0;
}

template<typename T>
inline T MyList<T>::at(int position) const {
    if (length == 0 || position >= length)
        throw "invalid index!";
    if (position == 0)
        return front();
    if (position == length - 1)
        return back();

    Element<T> *temp = first;
    for (int i = 0; i < position; i++)
        temp = temp->next;
    return temp->data;
}

template<typename T>
inline int MyList<T>::keyAt(int position) const {
    if (length == 0 || position >= length)
        throw "invalid index!";
    if (position == 0)
        return first->key;
    if (position == length - 1)
        return last->key;

    Element<T> *temp = first;
    for (int i = 0; i < position; i++)
        temp = temp->next;
    return temp->key;
}

template<typename T>
inline T MyList<T>::back() const {
    if (length == 0)
        throw "List is empty!";
    else
        return last->data;
}

template<typename T>
inline T MyList<T>::front() const {
    if (length == 0)
        throw "List is empty!";
    else
        return first->data;
}

template<typename T>
inline T MyList<T>::popBack() {
    if (length == 0)
        throw "List is empty!";
    else {
        T data = last->data;
        Element<T> *temp = last;
        last = last->previous;
        length--;
        if (length == 0)
            first = NULL;
        else
            last->next = NULL;
        delete temp;
        return data;
    }
}

template<typename T>
inline T MyList<T>::popFront() {
    if (length == 0)
        throw "List is empty!";
    else {
        T data = first->data;
        Element<T> *temp = first;
        first = first->next;
        length--;
        if (length == 0)
            last = NULL;
        else
            first->previous = NULL;
        delete temp;
        return data;
    }
}

template<typename T>
inline bool MyList<T>::pushBack(T data, int key) {
    if (length == 0) {
        Element<T> *newElement = new Element<T>(data, key);
        newElement->next = NULL;
        newElement->previous = NULL;
        first = newElement;
        last = newElement;
    }
    else {
        Element<T> *newElement = new Element<T>(data, key);
        newElement->next = NULL;
        newElement->previous = last;
        last->next = newElement;
        last = newElement;
    }
    length++;
    return true;
}

template<typename T>
inline bool MyList<T>::pushFront(T data, int key) {
    if (length == 0) {
        Element<T> *newElement = new Element<T>(data, key);
        newElement->next = NULL;
        newElement->previous = NULL;
        first = newElement;
        last = newElement;
    }
    else {
        Element<T> *newElement = new Element<T>(data, key);
        newElement->previous = NULL;
        newElement->next = first;
        first->previous = newElement;
        first = newElement;
    }
    length++;
    return true;
}

template<typename T>
inline bool MyList<T>::insert(int position, T data, int key) {
    if (position <= 0)
        return pushFront(data, key);
    if (position >= length - 1)
        return pushBack(data, key);

    Element<T> *temp = first;
    Element<T> *newElement  = new Element<T>(data, key);
    for (int i = 0; i < position; i++)
        temp = temp->next;
    newElement->previous = temp;
    newElement->next = temp->next;
    newElement->previous->next = newElement;
    newElement->next->previous = newElement;
    length++;
    return true;
}

template<typename T>
inline bool MyList<T>::remove(int position) {
    if (position >= length || position < 0)
        return false;
    if (position == 0) {
        popFront();
        return true;
    }
    if (position == length - 1) {
        popBack();
        return true;
    }

    Element<T> *temp = first;
    for (int i = 0; i < position; i++)
        temp = temp->next;
    temp->previous->next = temp->next;
    temp->next->previous = temp->previous;
    length--;
    delete temp;
    return true;
}

template<typename T>
inline bool MyList<T>::removeKey(int key) {
    Element<T> *temp = first;
    int tempLength = length;
    bool found = false;
    for (int i = 0; i < tempLength; i++) {
        if (temp->key == key) {
            temp = temp->next;
            remove(i);
            found = true;
        }
        else
            temp = temp->next;
    }
    if (found)
        return true;
    return false;
}

template<typename T>
inline bool MyList<T>::removeData(T data) {
    Element<T> *temp = first;
    int tempLength = length;
    bool found = false;
    for (int i = 0; i < tempLength; i++) {
        if (temp->data == data) {
            temp = temp->next;
            remove(i);
            found = true;
        }
        else
            temp = temp->next;
    }
    if (found)
        return true;
    return false;
}

template<typename T>
inline int MyList<T>::size() const {
    return length;
}

template<typename T>
inline void MyList<T>::sort(bool sequence) {
    struct ElementSort arr[length];
    Element<T> *temp = first;
    for (int i = 0; i < length; i++) {
        arr[i] = {temp->key, temp->data};
        temp = temp->next;
    }
    quickSort(arr, 0, length - 1, true, sequence);
    temp = first;
    for (int i = 0; i < length; i++) {
        temp->key = arr[i].key;
        temp->data = arr[i].data;
        temp = temp->next;
    }

}

template<typename T>
inline void MyList<T>::sortKey(bool sequence) {
    struct ElementSort arr[length];
    Element<T> *temp = first;
    for (int i = 0; i < length; i++) {
        arr[i] = {temp->key, temp->data};
        temp = temp->next;
    }
    quickSort(arr, 0, length - 1, false, sequence);
    temp = first;
    for (int i = 0; i < length; i++) {
        temp->key = arr[i].key;
        temp->data = arr[i].data;
        temp = temp->next;
    }
}

template<typename T>
inline void MyList<T>::quickSort(struct ElementSort arr[], int a, int b, bool dataOrKey, bool order) {
    if (a >= b) return;

    int i = a, j = b;

    if (dataOrKey) {
        T key = arr[(a + b) / 2].data;

        if (order) {
            while (i < j) {
                while (arr[i].data < key)
                    i++;
                while (arr[j].data > key)
                    j--;
                if (i <= j) {
                    struct ElementSort temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                    i++;
                    j--;
                }
            }
        }
        else {
            while (i < j) {
                while (arr[i].data > key)
                    i++;
                while (arr[j].data < key)
                    j--;
                if (i <= j) {
                    struct ElementSort temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                    i++;
                    j--;
                }
            }
        }
    }
    else {
        int key = arr[(a + b) / 2].key;
        if (order) {
            while (i < j) {
                while (arr[i].key < key)
                    i++;
                while (arr[j].key > key)
                    j--;
                if (i <= j) {
                    struct ElementSort temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                    i++;
                    j--;
                }
            }
        }
        else {
            while (i < j) {
                while (arr[i].key > key)
                    i++;
                while (arr[j].key < key)
                    j--;
                if (i <= j) {
                    struct ElementSort temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                    i++;
                    j--;
                }
            }
        }
    }
    quickSort(arr, a, j, dataOrKey, order);
    quickSort(arr, i, b, dataOrKey, order);

}

template<typename T>
inline bool MyList<T>::swap(int i1, int i2) {
    if (i1 == i2 || i1 < 0 || i1 >= length || i2 < 0 || i2 >= length)
        return false;

    int i3 = i1;
    if (i1 > i2) {
        i1 = i2;
        i2 = i3;
    }

    Element<T> *temp1 = first;
    Element<T> *temp2 = first;
    for (int i = 0; i < i2; i++) {
        temp2 = temp2->next;
        if (i == i1 - 1)
            temp1 = temp2;
    }

    int tempKey = temp1->key;
    T tempData = temp1->data;
    temp1->key = temp2->key;
    temp1->data = temp2->data;
    temp2->key = tempKey;
    temp2->data = tempData;

    return true;
}

template<typename T>
inline bool MyList<T>::swapElement(int i1, int i2) {
    if (i1 == i2 || i1 < 0 || i1 >= length || i2 < 0 || i2 >= length)
        return false;

    int i3 = i1;
    if (i1 > i2) {
        i1 = i2;
        i2 = i3;
    }

    Element<T> *temp1 = first;
    Element<T> *temp2 = first;
    for (int i = 0; i < i2; i++) {
        temp2 = temp2->next;
        if (i == i1 - 1)
            temp1 = temp2;
    }

    Element<T> *temp1Pre = temp1->previous;
    Element<T> *temp1Next = temp1->next;
    Element<T> *temp2Pre = temp2->previous;
    Element<T> *temp2Next = temp2->next;

    temp1->next = temp2Next;
    temp2->previous = temp1Pre;
    if (i2 - i1 != 1) {
        temp1->previous = temp2Pre;
        temp2->next = temp1Next;
    }
    else {
        temp1->previous = temp2;
        temp2->next = temp1;
    }

    if (NULL == temp1Pre)
        first = temp2;
    else
        temp1Pre->next = temp2;
    if (i2 - i1 != 1)
        temp1Next->previous = temp2;

    if (NULL == temp2Next)
        last = temp1;
    else
        temp2Next->previous = temp1;
    if (i2 - i1 != 1)
        temp2Pre->next = temp1;

    return true;
}

template<typename T>
inline bool MyList<T>::swapIgnoreKey(int i1, int i2) {
    if (i1 == i2 || i1 < 0 || i1 >= length || i2 < 0 || i2 >= length)
        return false;

    int i3 = i1;
    if (i1 > i2) {
        i1 = i2;
        i2 = i3;
    }

    Element<T> *temp1 = first;
    Element<T> *temp2 = first;
    for (int i = 0; i < i2; i++) {
        temp2 = temp2->next;
        if (i == i1 - 1)
            temp1 = temp2;
    }

    T tempData = temp1->data;
    temp1->data = temp2->data;
    temp2->data = tempData;

    return true;
}

template<typename T>
inline T MyList<T>::search(int key) const {
    Element<T> *temp = first;
    while(temp != NULL) {
        if (temp->key == key)
            return temp->data;
        temp = temp->next;
    }
    throw "not found";
}

template<typename T>
inline T* MyList<T>::searchAll(int key) const {
    T tempResult[length];
    int index = 0;
    Element<T> *temp = first;
    while(temp != NULL) {
        if (temp->key == key) {
            tempResult[index] = temp->data;
            index++;
        }
        temp = temp->next;
    }

    T *result = new T[index];
    for (int i = 0; i < index; i++) {
        result[i] = tempResult[i];
    }
    return result;
}

template<typename T>
inline int MyList<T>::searchCount(int key) const {
    int count = 0;
    Element<T> *temp = first;
    while(temp != NULL) {
        if (temp->key == key)
            count++;
        temp = temp->next;
    }
    return count;
}

template<typename T>
inline bool MyList<T>::changeKeyAt(int index, int key) {
    if (index < 0 || index >= length)
        return false;
    Element<T> *temp = first;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    temp->key = key;
    return true;
}

template<typename T>
inline bool MyList<T>::changeKeyWithData(T data, int key) {
    bool found = false;
    Element<T> *temp = first;
    while (temp != NULL) {
        if (temp->data == data) {
            temp->key = key;
            found = true;
        }
        temp = temp->next;
    }
    return found;
}

template<typename T>
inline bool MyList<T>::changeKey(int keyPrevious, int key) {
    bool found = false;
    Element<T> *temp = first;
    while (temp != NULL) {
        if (temp->key == keyPrevious) {
            temp->key = key;
            found = true;
        }
        temp = temp->next;
    }
    return found;
}

template<typename U>
std::ostream& operator<<(std::ostream &os, const MyList<U> &l) {
    os << std::endl << l.size() << " Elements: ";
    for (int i = 0; i < l.size(); i++) {
        os << l.keyAt(i) << "-" << l.at(i) << " ";
    }
    os << std::endl;
    return os;
}





#endif // MYLIST_H_INCLUDED
