#include "vect.h"

//vector methods

vect::vect(/* args */)
{
    x = 0;
    y = 0;
    z = 0;
}

vect::vect(double x_p, double y_p, double z_p) {
    x = x_p;
    y = y_p;
    z = z_p;
}

vect vect::operator+(vect a) {
        vect ret_vec(x+a.x, y+a.y, z+a.z);
        return ret_vec;
}
void vect::operator+=(vect a) {
    x += a.x;
    y += a.y;
    z += a.z;
}


vect vect::operator * (double l) {
    vect ret_vec(l*x,y*l,z*l);
    return ret_vec;
}

void vect::operator *= (double l) {
    x*=l;
    y*=l;
    z*=l;
}

double vect::sqr_len() {
    return pow(x,2) + pow(y, 2) + pow(z, 2);
}


