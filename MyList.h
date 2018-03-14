#ifndef MYLIST_H_INCLUDED
#define MYLIST_H_INCLUDED

#include <stdlib.h>

template<typename T>
class Element {
public:
    Element(T data, int key = 0);
    int key;
    T data;
    Element *previous, *next;
};

template<typename T>
inline Element<T>::Element(T data, int key) : key(key), data(data) {
    previous = NULL;
    next = NULL;
}

template<typename T>
class MyList
{
public:
    MyList();
    ~MyList();

    void initialize();

    //all index begins with 0!
    T at(int position);
    T back(); //return the last Element
    T front(); //return the first Element
    T popBack(); //return the last Element and delete it
    T popFront(); //return the first Element and delete it

    T pushBack(T data, int key = 0); //insert the Element after the last Element
    T pushFront(T data, int key = 0); //insert the Element in front of the first Element

    T insert(int position, T data, int key = 0); //insert the Element after the position
    T remove(int position); //remove the Element on position

    int size(); //return the length of the List

    void sort(bool sequence = true);
    void sortSelection(bool sequence = true);

    void swap(int i1, int i2); //swap data and keys with index i1 and i2
    void swapElement(int i1, int i2); //swap Elements with index i1 and i2
    void swapIgnoreKey(int i1, int i2); //only swap data, not the key
    T search(int key); //return the first data with key
    T* searchAll(int key); //return all data with key
    int searchCount(int key); //return the count of data with key


private:
    Element<T> *first; //first Element with index 0
    Element<T> *last; //last Element with index length - 1, the newest inserted Element
    int length;

    void quickSort(T arr[], int a, int b, bool order);

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
inline T MyList<T>::at(int position) {
    if (length == 0 || position >= length)
        return T(0);
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
inline T MyList<T>::back() {
    if (length == 0)
        return T(0);
    else
        return last->data;
}

template<typename T>
inline T MyList<T>::front() {
    if (length == 0)
        return T(0);
    else
        return first->data;
}

template<typename T>
inline T MyList<T>::popBack() {
    if (length == 0)
        return T(0);
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
        return T(0);
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
inline T MyList<T>::pushBack(T data, int key) {
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
    return data;
}

template<typename T>
inline T MyList<T>::pushFront(T data, int key) {
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
    return data;
}

template<typename T>
inline T MyList<T>::insert(int position, T data, int key) {
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
    return data;
}

template<typename T>
inline T MyList<T>::remove(int position) {
    if (position >= length || position < 0)
        return T(0);
    if (position == 0)
        return popFront();
    if (position == length - 1)
        return popBack();

    Element<T> *temp = first;
    for (int i = 0; i < position; i++)
        temp = temp->next;
    temp->previous->next = temp->next;
    temp->next->previous = temp->previous;
    T data = temp->data;
    length--;
    delete temp;
    return data;
}

template<typename T>
inline int MyList<T>::size() {
    return length;
}

template<typename T>
inline void MyList<T>::sort(bool sequence) {
    T *arr = new T[length];
    Element<T> *temp = first;
    for (int i = 0; i < length; i++) {
        arr[i] = temp->data;
        temp = temp->next;
    }
    quickSort(arr, 0, length - 1, sequence);
    temp = first;
    for (int i = 0; i < length; i++) {
        temp->data = arr[i];
        temp = temp->next;
    }
    delete[] arr;
}

template<typename T>
inline void MyList<T>::quickSort(T arr[], int a, int b, bool order) {
    if (a >= b) return;

	T key = arr[(a + b) / 2];
	int i = a, j = b;
	if (order) {
		while (i < j) {
			while (arr[i] < key)
				i++;
			while (arr[j] > key)
				j--;
			if (i <= j) {
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
				i++;
				j--;
			}
		}
	}
	else {
		while (i < j) {
			while (arr[i] > key)
				i++;
			while (arr[j] < key)
				j--;
			if (i <= j) {
				T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
				i++;
				j--;
			}
		}
	}

	quickSort(arr, a, j, order);
	quickSort(arr, i, b, order);
}

template<typename T>
inline void MyList<T>::swap(int i1, int i2) {
    if (i1 == i2 || i1 < 0 || i1 >= length || i2 < 0 || i2 >= length)
        return;

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
}

template<typename T>
inline void MyList<T>::swapElement(int i1, int i2) {
    if (i1 == i2 || i1 < 0 || i1 >= length || i2 < 0 || i2 >= length)
        return;

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
}

template<typename T>
inline void MyList<T>::swapIgnoreKey(int i1, int i2) {
    if (i1 == i2 || i1 < 0 || i1 >= length || i2 < 0 || i2 >= length)
        return;

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
}

template<typename T>
inline T MyList<T>::search(int key) {
    Element<T> *temp = first;
    while(temp != NULL) {
        if (temp->key == key)
            return temp->data;
        temp = temp->next;
    }
    return T(0);
}

template<typename T>
inline T* MyList<T>::searchAll(int key) {
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
inline int MyList<T>::searchCount(int key) {
    int count = 0;
    Element<T> *temp = first;
    while(temp != NULL) {
        if (temp->key == key)
            count++;
        temp = temp->next;
    }
    return count;
}





#endif // MYLIST_H_INCLUDED
