#ifndef atoms_struct
#define atoms_struct
#include <cstdint>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <fstream>

class vect
{
public:
    double x;
    double y;
    double z;
    //constructs
    vect();
    vect(double x_p, double y_p, double z_p);
    vect operator + (vect a);
    void operator+=(vect a);
    vect operator * (double l);
    void operator *= (double l);
    double sqr_len();
};




#endif