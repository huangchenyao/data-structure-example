#include <iostream>
#include "stack/Stack.h"
#include "stack/StackUse.h"
#include "queen/Queen.h"

int main() {
//    Vector<char> vector;
//    vector.insert('(');
//    vector.remove(0);
    clock_t startTime, endTime;
    for (int i = 0; i < 16; ++i) {
        std::cout << "Queen(" << i << "), ";
        startTime = clock();
        std::cout << "solu: " << placeQueens(i) << ", ";
        endTime = clock();
        std::cout << "Total Time: " << (double) (endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;

    }
    return 0;
}