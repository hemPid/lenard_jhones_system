#ifndef atom_field_h
#define atom_field_h
#include "vect.h"
#include "stdlib.h"


class Atom
{
public:
    vect pos;
    vect pre_pos;
    vect vel;
    vect acel;
};


class field
{
private:
    int64_t n;
    double a;
    double dt;
    double c_size;
    Atom * pices;
public:
    field(int64_t n, double a);
    void print_pices_info();
    ~field();
};

vect gen_random_vel();

#endif