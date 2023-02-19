#ifndef atoms_struct
#define atoms_struct
#include <cstdint>
#include <cmath>
#include <iostream>

class Atom
{
public:
    Atom();
    Atom(bool is_im, double x, double y, double z);
    bool is_image;
    double x, y, z;
    double prev_x, prev_y, prev_z;
    double a;
};
struct positions
{
    Atom ** pos_x;
    Atom ** pos_y;
    Atom ** pos_z;
};

class Field
{
private:
    double size;
    int64_t n;
    Atom * pieces;
    positions p;
public:
    Field(int64_t n, double a);
    void show_info();
    ~Field();
};


#endif