#include <iostream>
#include "stack/Stack.h"
#include "stack/StackUse.h"

int main() {
    StackUse stackUse;
    Stack<char> stack;
//    Vector<char> vector;
//    vector.insert('(');
    char *string = "12.34*(3.4+4.5)-5.6/7.8";
    char * rpn;
    std::cout << stackUse.evaluate(string, rpn) << std::endl;
    std::cout << rpn << std::endl;
//    vector.remove(0);
//    std::cout << vector.size() << std::endl;
    return 0;
}