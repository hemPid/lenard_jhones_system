#include <iostream>
#include "atoms_construct.h"

int main() {
    int64_t n = 0; //number of elements
    double a = 0; // size of system
    std::cin >> n >> a;
    Field test(n, a);
    test.show_info();
    return 0;
}