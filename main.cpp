#include <iostream>
#include "stack/Stack.h"
#include "stack/StackUse.h"
#include "queen/Queen.h"

int main() {
//    Vector<char> vector;
//    vector.insert('(');
//    vector.remove(0);
    placeQueens(8);
    std::cout << nSolu << std::endl;
    return 0;
}