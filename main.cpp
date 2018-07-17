#include <iostream>
#include "stack/Stack.h"
#include "stack/StackUse.h"

int main() {
    StackUse stackUse;
    Stack<char> stack;
//    Vector<char> vector;
//    vector.insert('(');
    const char *string = "2*(3+4)-6/7";
    std::cout << stackUse.paren(string) << std::endl;
//    vector.remove(0);
//    std::cout << vector.size() << std::endl;
    return 0;
}