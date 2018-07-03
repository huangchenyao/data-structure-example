//
// Created by 黄琛垚 on 2018/7/3.
//

#include "Fib.h"

Fib::Fib(int n) {
    f = 1;
    g = 0;
    while (g < n) {
        next();
    }
}

int Fib::get() {
    return g;
}

int Fib::next() {
    g += f;
    f = g - f;
    return g;
}

int Fib::prev() {
    f = g - f;
    g -= f;
    return g;
}
