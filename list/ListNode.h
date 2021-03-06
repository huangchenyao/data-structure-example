//
// Created by 黄琛垚 on 2018/7/4.
//

#ifndef DATA_STRUCTURE_LISTNODE_H
#define DATA_STRUCTURE_LISTNODE_H

typedef int Rank; // 秩
#define ListNodePosi(T) ListNode<T>* // 列表节点位置

template<typename T>
struct ListNode { // 列表节点模板类(以双向链表形式实现)
    // 成员
    T data; // 数值
    ListNodePosi(T) pred; // 前驱
    ListNodePosi(T) succ; // 后继

    // 构造函数
    ListNode() {} // 针对header和trailer的构造
    ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) : data(e), pred(p), succ(s) {} // 默认构造器

    // 操作接口
    ListNodePosi(T) insertAsPred(T const &e); //紧靠当前节点之前插入新节点
    ListNodePosi(T) insertAsSucc(T const &e); //紧随当前节点之后插入新节点
};

#endif //DATA_STRUCTURE_LISTNODE_H

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(const T &e) {
    ListNodePosi(T) x = new ListNode(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(const T &e) {
    ListNodePosi(T) x = new ListNode(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}
