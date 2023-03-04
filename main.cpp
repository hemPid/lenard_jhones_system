#include <iostream>
#include "atoms_construct.h"

int main() {/*
    int64_t n = 0; //number of elements
    double a = 0; // size of system
    int64_t ticks = 0;
    std::cin >> n >> a >> ticks;*/
    vect a(1,2,3);
    vect b(4,5,6);
    vect c = a *2;
    std::cout << c.x << " " << c.y << " " << c.z;
    b*=2;
    std::cout << " " << b.x << " " << b.y << " " << b.z;
    return 0;
}