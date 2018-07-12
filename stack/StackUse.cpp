//
// Created by 黄琛垚 on 2018/7/11.
//

#include "StackUse.h"

void StackUse::convert(Stack<char> &S, __int64_t n, int base) {
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    while (n > 0) {
        int remainder = (int) (n % base);
        S.push(digit[remainder]);
        n /= base;
    }
}
