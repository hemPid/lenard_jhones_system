#include <iostream>
#include "vect.h"
#include "atom_field.h"

int main() {
    int64_t n = 0; //number of elements
    double a = 0; // size of system
    int64_t ticks = 0;
    std::cin >> n >> a >> ticks;
    field test(n,a);
    test.print_pices_info();
    return 0;
}