//
// Created by 黄琛垚 on 2018/7/3.
//

#ifndef DATA_STRUCTURE_FIB_H
#define DATA_STRUCTURE_FIB_H


class Fib {
private:
    int f, g;

public:
    Fib(int n);

    int get();

    int next();

    int prev();
};


#endif //DATA_STRUCTURE_FIB_H
