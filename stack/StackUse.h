//
// Created by 黄琛垚 on 2018/7/11.
//

#ifndef DATA_STRUCTURE_STACKUSE_H
#define DATA_STRUCTURE_STACKUSE_H


#include <_regex.h>
#include "./Stack.h"

class StackUse {
public:
    void convert(Stack<char> &S, __int64_t n, int base);

    bool paren(const char exp[], int lo, int hi);

    bool paren(const char exp[]);

private:
    void trim(const char exp[], int &lo, int &hi);

    int divide(const char exp[], int lo, int hi);
};


#endif //DATA_STRUCTURE_STACKUSE_H
