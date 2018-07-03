//
// Created by 黄琛垚 on 2018/6/28.
//

#include <cstdlib>
#include "Vector.h"
#include "fibonacci/Fib.h"

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
    T *oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; ++i) {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}

template<typename T>
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1) {
        return;
    }
    if (_size << 2 > _capacity) {
        return;
    }
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; ++i) {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
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
    int n = 0;
    for (int i = 1; i < _size; ++i) {
        if (_elem[i - 1] > _elem[i]) {
            ++n;
        }
    }
    return n;
}

template<typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const {
    while ((lo < hi--) && (e != _elem[hi]));
    return hi;
}

template<typename T>
Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const {
    return rand() % 2 ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

template<typename T>
Rank Vector<T>::binSearch(T *A, const T &e, Rank lo, Rank hi) {
    while (lo < hi) {
        Rank mi = (hi + lo) >> 1;
        e < A[mi] ? hi = mi : lo = mi + 1;
    }
    return --lo;
}

template<typename T>
Rank Vector<T>::fibSearch(T *A, const T &e, Rank lo, Rank hi) {
    Fib fib(hi - lo);
    while (lo < hi) {
        while (hi - lo < fib.get()) {
            fib.prev();
        }
        Rank mi = lo + fib.get() - 1;
        if (e < A[mi]) {
            hi = mi - 1;
        } else if (e > A[mi]) {
            lo = mi + 1;
        } else {
            return mi;
        }
    }
    return -1;
}

template<typename T>
T &Vector<T>::operator[](Rank r) const {
    return _elem[r];
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
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    if (lo == hi) {
        return 0;
    }
    while (hi < _size) {
        _elem[lo++] = _elem[hi++];
    }
    shrink();
    return hi - lo;
}

template<typename T>
Rank Vector<T>::insert(Rank r, const T &e) {
    expand();
    for (int i = _size; i > r; --i) {
        _elem[i] = _elem[i - 1];
    }
    _elem[r] = e;
    ++_size;
    return r;
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi) {

}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    T *V = _elem + lo;
    for (Rank i = hi - lo; i > 0; i--) {
        swap(V[i - 1], V[rand() % i]);
    }
}

template<typename T>
int Vector<T>::deduplicate() {
    int oldSize = _size;
    Rank i = 1;
    while (i < _size) {
        (find(_elem[i], 0, i) < 0) ? ++i : remove(i);
    }
    return oldSize - _size;
}

template<typename T>
int Vector<T>::uniquify() {
    Rank i = 0, j = 0;
    while (++j < _size) {
        if (_elem[i] != _elem[j]) {
            _elem[++i] = _elem[j];
        }
    }
    _size = ++i;
    shrink();
    return j - i;
}

template<typename T>
void Vector<T>::traverse(void (*visit)(T &)) {
    for (int i = 0; i < _size; ++i) {
        visit(_elem[i]);
    }
}

template<typename T>
template<typename VST>
void Vector<T>::traverse(VST &visit) {
    for (int i = 0; i < _size; ++i) {
        visit(_elem[i]);
    }
}

template<typename T>
void Vector<T>::swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}