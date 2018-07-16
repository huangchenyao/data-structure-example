#include <iostream>
#include "stack/Stack.h"
#include "stack/StackUse.h"

int main() {
    StackUse stackUse;
    Stack<char> stack;
//    Vector<char> vector;
    stackUse.convert(stack, 16, 16);
    const char *string = "1+2+(3+4*5)-6/7";
    int lo = 0;
    int hi = 10;
    std::cout << stackUse.paren(string, lo, hi) << std::endl;
    return 0;
}