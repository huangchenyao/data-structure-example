#include <iostream>
#include "stack/Stack.h"
#include "stack/StackUse.h"

int main() {
    StackUse stackUse;
    Stack<char> stack;
//    Vector<char> vector;
    stackUse.convert(stack, 16, 16);
    std::cout << stack[1] << std::endl;
    return 0;
}