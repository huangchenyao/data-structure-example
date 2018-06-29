//
// Created by 黄琛垚 on 2018/6/28.
//

#include "Vector.h"

template<typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi) {
        _elem[_size++] = A[lo++];
    }
}

template<typename T>
void Vector<T>::expand() {
    if (_size < _capacity) {
        return;
    }
    if (_capacity < DEFAULT_CAPACITY) {
        _capacity = DEFAULT_CAPACITY;
    }
    T * oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; ++i) {
        _elem[i] = oldElem[i];
    }
    delete [] oldElem;
}

template<typename T>
void Vector<T>::shrink() {

}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
    return false;
}

template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {

}

template<typename T>
Rank Vector<T>::max(Rank lo, Rank hi) {
    return 0;
}

template<typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi) {

}

template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {

}

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {

}

template<typename T>
Rank Vector<T>::partition(Rank lo, Rank hi) {
    return 0;
}

template<typename T>
void Vector<T>::quickSort(Rank lo, Rank hi) {

}

template<typename T>
void Vector<T>::heapSort(Rank lo, Rank hi) {

}

template<typename T>
int Vector<T>::disordered() const {
    return 0;
}

template<typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const {
    return 0;
}

template<typename T>
Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const {
    return 0;
}

template<typename T>
T &Vector<T>::operator[](Rank r) const {
    return <#initializer#>;
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &V) {
    if (_elem) {
        delete[] _elem;
    }
    copyFrom(V._elem, 0, V.size());
    return *this;
}

template<typename T>
T Vector<T>::remove(Rank r) {
    return nullptr;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    return 0;
}

template<typename T>
Rank Vector<T>::insert(Rank r, const T &e) {
    return 0;
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi) {

}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {

}

template<typename T>
int Vector<T>::deduplicate() {
    return 0;
}

template<typename T>
int Vector<T>::uniquify() {
    return 0;
}

template<typename T>
void Vector<T>::traverse(void (*)(T &)) {

}

template<typename T>
template<typename VST>
void Vector<T>::traverse(VST &) {

}
