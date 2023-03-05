#include "atom_field.h"



vect gen_random_vel() {
    vect ret;
    ret.x = rand()-RAND_MAX/2;
    ret.y = rand()-RAND_MAX/2;
    ret.z = rand()-RAND_MAX/2;
    ret *= (4.0/RAND_MAX);
    return ret;    
}

//atom


//field

field::field(int64_t n, double a)
{
    this->n = n;
    this->a = a;
    dt = 0.0001;
    int64_t size_num = ceil(pow(n, 1.0/3));
    c_size = a/size_num;
    double d = (a - (size_num - 1)*c_size)/2;
    pices = new Atom[27*n];
    int64_t i = 0;
    int64_t j = 0;
    int64_t k = 0;
    vect full_momentum;
    for (int64_t p = 0; p < n; ++p)
    {
        //coordinates
        pices[p].pre_pos.x = d + i*c_size;
        pices[p].pre_pos.y = d + j*c_size;
        pices[p].pre_pos.z = d + k*c_size;
        pices[p].vel += gen_random_vel();
        full_momentum += pices[p].vel;
        ++i;
        if (i >= size_num) {
            i = 0;
            ++j;
        }
        if (j >= size_num) {
            j = 0;
            ++k;
        }
        //initializing images
        int16_t i_count = 1;
        for (int16_t x_i = -1; x_i <= 1; ++x_i)
        {
            for (int16_t y_i = -1; y_i <= 1; ++y_i)
            {
                for (int16_t z_i = -1; z_i <= 1; ++z_i)
                {
                    if (x_i || y_i || z_i)
                    {
                        pices[p+i_count*n].pre_pos.x = pices[p].pre_pos.x + x_i*a;
                        pices[p+i_count*n].pre_pos.y = pices[p].pre_pos.y + y_i*a;
                        pices[p+i_count*n].pre_pos.z = pices[p].pre_pos.z + z_i*a;
                        pices[p+i_count*n].vel += pices[p].vel;
                        ++i_count;
                    }
                }
            }
        }
    }
    full_momentum /= n;
    for (int64_t i = 0; i < 27*n; ++i)
    {
        pices[i].vel -= full_momentum;
        pices[i].pos += pices[i].pre_pos;
        pices[i].pos += pices[i].vel * dt;
    }
}

field::~field()
{
    delete [] pices;
}

void field::print_pices_info() {
    for (int64_t i = 0; i < n; i++)
    {
        std::cout << i << ": " << pices[i].pre_pos.x << ", " << pices[i].pre_pos.y << ", " << pices[i].pre_pos.z << "\n";
        std::cout << i << ": " << pices[i].vel.x << ", " << pices[i].vel.y << ", " << pices[i].vel.z << "\n";
        std::cout << i << ": " << pices[i].pos.x << ", " << pices[i].pos.y << ", " << pices[i].pos.z << "\n";
    }
    
}