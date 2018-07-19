//
// Created by 黄琛垚 on 2018/7/11.
//

#include <cctype>
#include <cstring>
#include <cstdio>
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

float StackUse::evaluate(char *S, char *&RPN) { // 对(已剔除白空格的)表达式S求值，并转换为逆波兰式RPN
    Stack<float> opnd; // 运算数栈
    Stack<char> optr; // 运算符栈
    optr.push('\0'); // 尾哨兵'\0'也作为头哨兵首先入栈
    while (!optr.empty()) { // 在运算符栈非空之前，逐个处理表达式中各字符
        if (isdigit(*S)) { // 若当前字符为操作数，则
            readNumber(S, opnd); // 读入操作数
            append(RPN, opnd.top()); // 并将其接至RPN末尾
        } else //若当前字符为运算符，则
            switch (orderBetween(optr.top(), *S)) { // 视其与栈顶运算符之间优先级高低分别处理
                case '<': // 栈顶运算符优先级更低时
                    optr.push(*S);
                    S++; // 计算推迟，当前运算符进栈
                    break;
                case '=': // 优先级相等(当前运算符为右括号或者尾部哨兵'\0')时
                    optr.pop();
                    S++; // 脱括号并接收下一个字符
                    break;
                case '>': {//栈顶运算符优先级更高时，可实施相应的计算，并将结果重新入栈
                    char op = optr.pop();
                    append(RPN, op); // 栈顶运算符出栈并续接至RPN末尾
                    if ('!' == op) { // 若属亍一元运算符
                        float pOpnd = opnd.pop(); //只需取出一个操作数，并
//                        opnd.push(calcu(op, pOpnd)); // 实施一元计算，结果入栈
                    } else { // 对于其它(二元)运算符
                        float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop(); // 取出后、前操作数
//                        opnd.push(calcu(pOpnd1, op, pOpnd2)); // 实施二元计算，结果入栈
                    }
                    break;
                }
                default:
                    exit(-1); // 逢语法错误，不做处理直接退出
            }
    }
    return opnd.pop();
}

Operator StackUse::optr2rank(char op) {
    switch (op) {
        case '+' :
            return ADD; // 加
        case '-' :
            return SUB; // 减
        case '*' :
            return MUL; // 乘
        case '/' :
            return DIV; // 除
        case '^' :
            return POW; // 乘方
        case '!' :
            return FAC; // 阶乘
        case '(' :
            return L_P; // 左括号
        case ')' :
            return R_P; // 右括号
        case '\0':
            return EOE; // 起始符和终止符
        default :
            exit(-1); // 未知运算符
    }
}

char StackUse::orderBetween(char op1, char op2) {
    return pri[optr2rank(op1)][optr2rank(op2)];
}

void StackUse::readNumber(char *&p, Stack<float> &stk) { // 将起始于p的子串解析为数值，并存入操作数栈
    stk.push((float) (*p - '0'));
    while (isdigit(*(++p))) {
        stk.push(stk.pop() * 10 + (*p - '0'));
    }
    if (*p == '.') {
        float fraction = 1.0;
        while (isdigit(*(++p))) {
            stk.push(stk.pop() + (*p - '0') * (fraction /= 10.0));
        }
    }
}

void StackUse::append(char *&RPN, float opnd) { // 将操作数接至RPN末尾
    int n = strlen(RPN); // RPN当前长度(以'\0'结尾，长度n + 1)
    char buf[64];
    if (opnd != (float) (int) opnd) { // 浮点格式，或
        sprintf(buf, "%.2f \0", opnd);
    } else { // 整数格式
        sprintf(buf, "%d \0", (int) opnd);
    }
    RPN = (char *) realloc(RPN, sizeof(char) * (n + (int)strlen(buf) + 1)); // 扩展空间
    strcat(RPN, buf); // RPN加长
}

void StackUse::append(char *&RPN, char optr) { // 将运算符接至RPN末尾
    int n = strlen(RPN); // RPN当前长度(以'\0'结尾，长度n + 1)
    RPN = (char *) realloc(RPN, sizeof(char) * (n + 3)); // 扩展空间
    sprintf(RPN + n, "%c ", optr);
    RPN[n + 2] = '\0'; // 接入指定的运算符
}