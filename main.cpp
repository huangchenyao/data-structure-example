#include <iostream>
#include "vector/Vector.h"
//#include "fibonacci/Fib.h"

int main() {
    Vector<int> vector(10);
    vector.insert(1);
    std::cout << vector[0] << std::endl;
    return 0;
}