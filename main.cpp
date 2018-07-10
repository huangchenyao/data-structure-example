#include <iostream>
#include "list/List.h"

int main() {
    List<int> list;
    list.insertAsLast(1);
    list.insertAsLast(2);
    list.insertAsLast(3);
    ListNodePosi(int)p = list.find(2);
    list.insertBefore(p, 4);
    list.insertAfter(p, 5);
    list.sort();
    std::cout << list[0] << std::endl;
    return 0;
}