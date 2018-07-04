#include <iostream>
#include "vector/Vector.h"
#include "fibonacci/Fib.h"

int main() {
    Vector<int> vec1;
    Fib fib(10);
    vec1.test();
//    std::cout << vec1[0] << std::endl;
    std::cout << fib.get() << std::endl;
    return 0;
}