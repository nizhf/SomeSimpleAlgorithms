#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

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

#endif // ELEMENT_H_INCLUDED
