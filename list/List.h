//
// Created by 黄琛垚 on 2018/7/4.
//

#ifndef DATA_STRUCTURE_LIST_H
#define DATA_STRUCTURE_LIST_H

#include <cstdlib>
#include "ListNode.h"

template<typename T>
class List {
private:
    int _size; // 规模
    ListNodePosi<T> header; // 头哨兵
    ListNodePosi<T> trailer; // 尾哨兵

protected:
    void init(); // 列表创建时的初始化
    int clear(); // 清除所有节点
    void copyNodes(ListNodePosi<T>, int); // 复制列表中自位置p起的n项
    void merge(ListNodePosi<T>, int, List<T> &, ListNodePosi<T>, int); // 有序列表区间归并
    void mergeSort(ListNodePosi<T> &, int); // 对从p开始连续的n个节点归并排序
    void selectionSort(ListNodePosi<T>, int); // 对从p开始连续的n个节点选择排序
    void insertionSort(ListNodePosi<T>, int); // 对从p开始连续的n个节点插入排序

public:
    // 构造函数
    List() { init(); } // 默认
    List(List<T> const &L); // 整体复制列表L
    List(List<T> const &L, Rank r, int n); // 复制列表L中自第r项起的n项
    List(ListNodePosi<T> p, int n); // 复制列表中自位置p起的n项

    // 析构函数
    ~List(); // 释放(包含头、尾哨兵在内的)所有节点

    // 只读访问接口
    Rank size() const { return _size; } // 规模
    bool empty() const { return _size <= 0; } // 判空
    T &operator[](Rank r) const; // 重载，支持循秩访问(效率低)
    ListNodePosi<T> first() const { return header->succ; } // 首节点位置
    ListNodePosi<T> last() const { return trailer->pred; } // 末节点位置
    bool valid(ListNodePosi<T> p) // 判断位置p是否对外合法
    { return p && (trailer != p) && (header != p); } // 将头、尾节点等同于NULL
    int disordered() const; // 判断列表是否已排序
    ListNodePosi<T> find(T const &e) const { return find(e, _size, trailer); } // 无序列表查找
    ListNodePosi<T> find(T const &e, int n, ListNodePosi<T> p) const; // 无序区间查找
    ListNodePosi<T> search(T const &e) const { return search(e, _size, trailer); } //有序列表查找
    ListNodePosi<T> search(T const &e, int n, ListNodePosi<T> p) const; //有序区间查找
    ListNodePosi<T> selectMax(ListNodePosi<T> p, int n); // 在p及其前n-1个后继中选出最大者
    ListNodePosi<T> selectMax() { return selectMax(header->succ, _size); } // 整体最大者

    // 可写访问接口
    ListNodePosi<T> insertAsFirst(T const &e); // 将e当作首节点插入
    ListNodePosi<T> insertAsLast(T const &e); // 将e当作末节点插入
    ListNodePosi<T> insertBefore(ListNodePosi<T> p, T const &e); // 将e当作p的前驱插入
    ListNodePosi<T> insertAfter(ListNodePosi<T> p, T const &e); // 将e当作p的后继插入
    T remove(ListNodePosi<T> p); // 删除合法位置p处的节点, 返回被删除节点
    void merge(List<T> &L) { merge(first(), _size, L, L.first(), L._size); } //全列表归并
    void sort(ListNodePosi<T> p, int n); // 列表区间排序
    void sort() { sort(first(), _size); } // 列表整体排序
    int deduplicate(); // 无序去重
    int uniquify(); // 有序去重
    void reverse(); // 前后倒置(习题)

    // 遍历
    void traverse(void (*)(T &)); // 遍历，依次实施visit操作(函数指针，只读局部性修改)
    template<typename VST>
    void traverse(VST &); // 遍历，依次实施visit操作(函数对象，可全局性修改)
};

template<typename T>
void List<T>::init() { // 列表初始化，在创建对象时统一调用
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->pred = nullptr;
    header->succ = trailer;
    trailer->pred = header;
    trailer->succ = nullptr;
    _size = 0;
}

template<typename T>
int List<T>::clear() {
    int oldSize = _size;
    while (0 < _size) {
        remove(header->succ);
    }
    return oldSize;
}

template<typename T>
// 列表内部方法：复制列表中自位置p起的n项
void List<T>::copyNodes(ListNodePosi<T> p, int n) { // p合法，且至少有n-1个真后继节点
    init();
    while (n--) {
        insertAsLast(p->data);
        p = p->succ;
    }
}

template<typename T>
void List<T>::merge(ListNodePosi<T>, int, List<T> &, ListNodePosi<T>, int) {

}

template<typename T>
void List<T>::mergeSort(ListNodePosi<T> &, int n) {

}

template<typename T>
void List<T>::selectionSort(ListNodePosi<T> p, int n) {
    ListNodePosi<T> head = p->pred;
    ListNodePosi<T> tail = p;
    for (int r = 0; r < n; ++r) {
        tail = tail->succ;
    }
    while (1 < n) {
        ListNodePosi<T> max = selectMax(head->succ, n);
        insertBefore(tail, remove(max));
        --n;
    }

}

template<typename T>
void List<T>::insertionSort(ListNodePosi<T> p, int n) {
    for (int r = 0; r < n; ++r) {
        insertAfter(search(p->data, r, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template<typename T>
List<T>::List(const List<T> &L) { // 整体复制列表L
    copyNodes(L.first(), L.size());
}

template<typename T>
List<T>::List(const List<T> &L, Rank r, int n) { // 复制L中自第r项起的n项
    copyNodes(L[r], n);
}

template<typename T>
List<T>::List(ListNodePosi<T> p, int n) { // 复制列表中自位置p起的n项
    copyNodes(p, n);
}

template<typename T>
List<T>::~List() {
    clear();
    delete header;
    delete trailer;
}

template<typename T>
T &List<T>::operator[](Rank r) const { //assert: 0 <= r < size
    ListNodePosi<T> p = first();
    while (0 < r--) {
        p = p->succ;
    }
    return p->data;
}

template<typename T>
int List<T>::disordered() const {
    return 0;
}

template<typename T>
// 在无序列表内节点p(可能是trailer)的n个(真)前驱中，找到等于e的最后者
ListNodePosi<T> List<T>::find(const T &e, int n, ListNodePosi<T> p) const { // 0<=n<=rank(p)<_size
    while (0 < n--) {
        if (e == (p = p->pred)->data) {
            return p;
        }
    }
    return nullptr;
}

template<typename T>
ListNodePosi<T> List<T>::search(const T &e, int n, ListNodePosi<T> p) const {
    while (0 <= n--) {
        if ((p = p->pred)->data <= e) {
            break;
        }
    }
    return p;
}

template<typename T>
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, int n) {
    ListNodePosi<T> max = p;
    for (ListNodePosi<T> cur = p; 1 < n; --n) {
        if ((cur = cur->succ)->data >= max->data) {
            max = cur;
        }
    }
    return max;
}

template<typename T>
ListNodePosi<T> List<T>::insertAsFirst(const T &e) { // e当作头结点插入
    ++_size;
    return header->insertAsPred(e);
}

template<typename T>
ListNodePosi<T> List<T>::insertAsLast(const T &e) { // e当作末节点插入
    ++_size;
    return trailer->insertAsSucc(e);
}

template<typename T>
ListNodePosi<T> List<T>::insertBefore(ListNodePosi<T> p, const T &e) { // e当作p的前驱插入
    _size++;
    return p->insertAsPred(e);
}

template<typename T>
ListNodePosi<T> List<T>::insertAfter(ListNodePosi<T> p, const T &e) { // e当作p的后继插入
    ++_size;
    return p->insertAsSucc(e);
}

template<typename T>
T List<T>::remove(ListNodePosi<T> p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    p->pred = nullptr;
    p->succ = nullptr;
    delete p;
    --_size;
    return e;
}

template<typename T>
void List<T>::sort(ListNodePosi<T> p, int n) {
    switch (rand() % 3) {
        case 0:
            insertionSort(p, n);
            break;
        case 1:
            selectionSort(p, n);
            break;
        default:
            mergeSort(p, n);
            break;
    }
}

template<typename T>
int List<T>::deduplicate() {
    if (_size < 2) {
        return 0;
    }
    int oldSize = _size;
    ListNodePosi<T> p = header;
    Rank r = 0;
    while (trailer != (p = p->succ)) {
        ListNodePosi<T> q = find(p->data, r, p);
        q ? remove(q) : ++r;
    }
    return oldSize - _size;
}

template<typename T>
int List<T>::uniquify() {
    if (_size < 2) {
        return 0;
    }
    int oldSize = _size;
    ListNodePosi<T> p;
    ListNodePosi<T> q;
    for (p = header, q = p->succ; q != trailer; p = q, q = q->succ) {
        if (p->data == q->data) {
            remove(q);
            q = p;
        }
    }
    return oldSize - _size;
}

template<typename T>
void List<T>::reverse() {

}

template<typename T>
void List<T>::traverse(void (*visit)(T &)) {
    for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) {
        visit(p->data);
    }
}

template<typename T>
template<typename VST>
void List<T>::traverse(VST &visit) {
    for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) {
        visit(p->data);
    }
}


#endif //DATA_STRUCTURE_LIST_H
