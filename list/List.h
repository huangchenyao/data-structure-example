//
// Created by 黄琛垚 on 2018/7/4.
//

#ifndef DATA_STRUCTURE_LIST_H
#define DATA_STRUCTURE_LIST_H

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
    void merge(ListNodePosi<T> &, int, List<T> &, ListNodePosi<T>, int); // 有序列表区间归并
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
};


#endif //DATA_STRUCTURE_LIST_H
