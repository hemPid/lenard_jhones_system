#ifndef atom_field_h
#define atom_field_h
#include "vect.h"
#include "stdlib.h"
#include <fstream>


class Atom
{
public:
    vect pos;
    vect pre_pos;
    vect vel;
    vect avg_vel;
    int cnt;
    vect acel;
};


class field
{
private:
    int64_t n;
    double a;
    double dt;
    double c_size;
    double k_energy;
    double p_energy;
    double energy;
    Atom * pices;
    void tick();
    void update();
    vect count_force(Atom * p, Atom * e);
    double count_potential_energy(Atom * p, Atom * e);
    double count_kinetic_energy(Atom * p);
    void period_r(vect & r);
    void upd_vels();
public:
    field(int64_t n, double a);
    void print_pices_info();
    void make_ticks(int64_t num);
    ~field();
};

vect gen_random_vel();

#endif