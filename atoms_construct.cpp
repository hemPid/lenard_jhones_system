#include "atoms_construct.h"

Atom::Atom() {
    is_image = false;
    x = 0;
    y = 0;
    z = 0;
    prev_x = 0;
    prev_y = 0;
    prev_z = 0;
    a = 0;
}

Atom::Atom(bool is_im, double x, double y, double z) {
    this->is_image = is_im;
    this->x = x;
    this->y = y;
    this->z = z;
}

Field::Field(int64_t n, double a) {
    this->n = n;
    this->size = a;
    pieces = new Atom[27*n];
    p.pos_x = new Atom * [27*n];
    p.pos_y = new Atom * [27*n];
    p.pos_z = new Atom * [27*n];
    int64_t crystal_size = ceil(pow(n, 1.0/3.0));
    double step = a/(crystal_size + 1);
    int64_t s_x = 1;
    int64_t s_y = 1;
    int64_t s_z = 1;
    for (int c = 0; c < n; ++c)
    {
        //intialization of true atom
        pieces[c].x = s_x*step;
        pieces[c].y = s_y*step;
        pieces[c].z = s_z*step;
        pieces[c].prev_x = s_x*step;
        pieces[c].prev_y = s_y*step;
        pieces[c].prev_z = s_z*step;
        p.pos_x[c] = &pieces[c];
        p.pos_y[c] = &pieces[c];
        p.pos_z[c] = &pieces[c];
        //initializtion of images
        int16_t mult = 1;
        for (int16_t k = -1; k <= 1; ++k)
        {
            for (int16_t j = -1; j <= 1; ++j)
            {
                for (int16_t i = -1; i <= 1; ++i)
                {
                    if (!k && !j && !i) continue;
                    pieces[c+mult*n].is_image = true;
                    pieces[c+mult*n].x = pieces[c].x + i*a;
                    pieces[c+mult*n].y = pieces[c].y + j*a;
                    pieces[c+mult*n].z = pieces[c].z + k*a;
                    p.pos_x[c+mult*n] = &pieces[c+mult*n];
                    p.pos_y[c+mult*n] = &pieces[c+mult*n];
                    p.pos_x[c+mult*n] = &pieces[c+mult*n];
                    ++mult; 
                }
                
            }
        }
        
    }
}

Field::~Field() {
    delete [] pieces;
    delete [] p.pos_x;
    delete [] p.pos_y;
    delete [] p.pos_z;
}

void Field::show_info() {
    for (int64_t i = 0; i < 27*n; ++i)
    {
        std::cout << i << ":\n";
        std::cout << "is_image: " << pieces[i].is_image << ", ";
        std::cout << "x: " << pieces[i].x << ", ";
        std::cout << "y: " << pieces[i].y << ", ";
        std::cout << "z: " << pieces[i].z << "\n";
    }
    
}