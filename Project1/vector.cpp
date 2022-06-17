#include <iostream>
#include "vector.h"
const size_t DEF_CAP = 4;

template <typename T>
void Vector<T>::copy(const Vector& other) {
    size = other.size;
    capacity = other.capacity;
    array = new T [capacity];
    for (int i = 0; i < size; i++) {
        array[i] = other.array[i];
    }
}

template <typename T>
void Vector<T>::clear() {
    delete[] array;
    array = nullptr;
    size = 0;
    capacity = 0;
}

template <typename T>
Vector<T>::Vector() {
    size = 0;
    capacity = DEF_CAP;
    array = new T [capacity];
}

template <typename T>
Vector<T>& Vector<T>::operator= (const Vector& other) {
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

template <typename T>
Vector<T>::Vector(int cap) {
    capacity = cap;
    array = new T [capacity];
    size = 0;
}

template <typename T>
Vector<T>::Vector(int _size, T* _array) {
    size = _size;
    capacity = size;
    array = new T [capacity];
    for (int i = 0; i < size; i++) {
        array[i] = _array[i];
    }
}

template <typename T>
void Vector<T>::readVector (std::istream& is = std::cin) {
    char c;
    do {
        if (T == int) {
            is.get(c);
            if ( c >= '0' && c <= '9') {
            push_back((int)(c - '0'));
            }
        }
    }
    while ( c != '\0' && c != '\n' && c!= '|' );
}

template <typename T>
void Vector<T>::setVector (int _size, T* _array) {
    size = _size;
    if (capacity < size) {
        reserve(2*capacity);
    }
    for (int i = 0; i < size; i++) {
        array[i] = _array[i];
    }
}

template <typename T>
bool Vector<T>::reserve(int _capacity) {
    if (_capacity > capacity) {
        int* newVector = new T [_capacity];
        if (newVector == nullptr) {
            return false;
        }
        for (int i = 0; i < size; i++) {
            newVector[i] = array[i];
        }
        delete[] array;
        array = newVector;
    }
    return true;
}

template <typename T>
void Vector<T>::push_back (T element) {
    if (size + 1 <= capacity) {
        if (!reserve(2*capacity)) {
            std::cerr << "Failed to Allocate new memory!";
        }
    }
    array[size++] = element;
}

template <typename T>
void Vector<T>::erase (int index) {
    for (int i = index; i < size - 1; i++) {
        array[i] = array[i + 1];
    }
    --size;
}

template <typename T>
void Vector<T>::deleteElem (T elem) {
    for (int i = 0; i < size; i++) {
        if (array[i] == elem) {
            erase(i);
        }
    }
}

template <typename T>
T& Vector<T>::find (T elem) const {
    for (int i = 0; i < size; i++) {
        if (array[i] == elem) {
            return i;
        }
    }
    return -1;
}

template <typename T>
void Vector<T>::print () const {
    for (int i = 0; i < size; i++) {
        std::cout << array[i];
    }
}

template <typename T>
T& Vector<T>::operator [] (int idx) const {
    return array[idx];
}

template <typename T>
bool Vector<T>::operator == (const Vector<T>& other) const {
    if (size != other.size) {
        return false;
    }
    for (int i = 0;i < size; i++) {
        if (array[i] != other[i] ) {
            return false;
        }
    }
    return true;
}

template <typename T>
std::ostream& operator << (std::ostream& os, Vector<T>& dynArray) {
    int size = dynArray.getSize();
    for (int i = 0; i < size; i++) {
        os << dynArray[i];
    }
    return os;
}

template <typename T>
std::ostream& operator << (std::ostream& os, const Vector<T>& dynArray) {
    int size = dynArray.getSize();
    for (int i = 0; i < size; i++) {
        os << dynArray[i];
    }
    return os;
}

template <typename T>
std::istream& operator >> (std::istream& is, Vector<T>& dynArray) {
    char c;
    do {
        if (T == int) {
            is.get(c);
            if ( c >= '0' && c <= '9') {
            dynArray.push_back((int)(c - '0'));
            }
        }
    }
    while ( c != '\0' && c != '\n' && c!= '|' && c!= ' ');
    return is;
}

