#include <iostream>
#include "vector/Vector.h"
//#include "fibonacci/Fib.h"

int main() {
    Vector<int> vector;
    for (int i = 0; i < 2000; ++i) {
        vector.insert(rand() % 2000);
    }
    vector.sort();
    for (int i = 0; i < 2000; ++i) {
        std::cout << vector[i] << std::endl;
    }
//    std::cout << vector[0] << std::endl;
    return 0;
}