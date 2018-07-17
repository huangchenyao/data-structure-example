//
// Created by 黄琛垚 on 2018/7/11.
//

#ifndef DATA_STRUCTURE_STACKUSE_H
#define DATA_STRUCTURE_STACKUSE_H


#include <_regex.h>
#include "./Stack.h"

#define N_OPTR 9 // 运算符总数
typedef enum {
    ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE
} Operator; //运算符集合
// 加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符

class StackUse {
public:
    void convert(Stack<char> &S, __int64_t n, int base);

    bool paren(const char exp[], int lo, int hi);

    bool paren(const char exp[]);

    float evaluate(char *S, char *&RPN);

private:
    const char pri[N_OPTR][N_OPTR] = { // 运算符优先等级 [栈顶] [当前]
            /*           |-------------- 当前运算符 --------------| */
            /*           +    -    *    /    ^    !    (    )   \0 */
            /* --  + */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
            /* |   - */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
            /* 栈  * */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
            /* 顶  / */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
            /* 运  ^ */ '>', '>', '>', '>', '>', '<', '<', '>', '>',
            /* 算  ! */ '>', '>', '>', '>', '>', '>', ' ', '>', '>',
            /* 符  ( */ '<', '<', '<', '<', '<', '<', '<', '=', ' ',
            /* |   ) */ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            /* -- \0 */ '<', '<', '<', '<', '<', '<', '<', ' ', '='
    };

    void trim(const char exp[], int &lo, int &hi);

    int divide(const char exp[], int lo, int hi);

    void readNumber(char *&p, Stack<float> &stk);

    void append(char *&RPN, float opnd);

    void append(char *&RPN, char optr);

    Operator optr2rank(char op);

    char orderBetween(char op1, char op2);
};

#endif //DATA_STRUCTURE_STACKUSE_H




