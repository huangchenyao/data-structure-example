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

bool StackUse::paren(const char exp[], int lo, int hi) {
    trim(exp, lo, hi);
    if (lo > hi) { return true; }
    if (exp[lo] != '(') { return false; }
    if (exp[hi] != ')') { return false; }
    int mi = divide(exp, lo, hi);
    if (mi > hi) { return false; }
    return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi);
}

bool StackUse::paren(const char *exp) {
    Stack<char> S;
    for (int i = 0; exp[i]; ++i) {
        switch (exp[i]) {
            case '(':
            case '[':
            case '{':
                S.push(exp[i]);
                break;
            case ')':
                if (S.empty() || S.pop() != '(') { return false; }
                break;
            case ']':
                if (S.empty() || S.pop() != '[') { return false; }
                break;
            case '}':
                if (S.empty() || S.pop() != '{') { return false; }
                break;
            default:
                break;
        }
    }
    return S.empty();
}

void StackUse::trim(const char exp[], int &lo, int &hi) { // 删除表达式exp[lo, hi]不含小括号的最长前缀、后缀
    while ((lo <= hi) && (exp[lo] != '(') && (exp[lo] != ')')) { lo++; } // 查找第一个和
    while ((lo <= hi) && (exp[hi] != '(') && (exp[hi] != ')')) { hi--; } // 最后一个括号
}

int StackUse::divide(const char exp[], int lo, int hi) { // 切分表达式exp[lo, hi]，使exp匹配仅当它们匹配
    int mi = lo;
    int crc = 1; // crc为[lo, mi]范围内左、右括号数目之差
    while ((0 < crc) && (++mi < hi)) {
        if (exp[mi] == ')') { --crc; }
        if (exp[mi] == '(') { ++crc; }
    }
    return mi;
}
