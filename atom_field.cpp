#include "atom_field.h"



vect gen_random_vel() {
    vect ret;
    ret.x = rand()-RAND_MAX/2;
    ret.y = rand()-RAND_MAX/2;
    ret.z = rand()-RAND_MAX/2;
    ret *= (4.0/RAND_MAX);
    ret *= 0.1;
    return ret;    
}

//atom


//field

field::field(int64_t n, double a)
{
    this->n = n;
    this->a = a;
    dt = pow(10,-3);
    int64_t size_num = ceil(pow(n, 1.0/3));
    c_size = a/size_num;
    pices = new Atom[n];
    int64_t i = 0;
    int64_t j = 0;
    int64_t k = 0;
    vect full_momentum;
    for (int64_t p = 0; p < n; ++p)
    {
        //coordinates
        pices[p].pre_pos.x = i*c_size;
        pices[p].pre_pos.y = j*c_size;
        pices[p].pre_pos.z = k*c_size;
        pices[p].vel += gen_random_vel();
        pices[p].cnt = 0;
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
    }
    full_momentum /= n;
    for (int64_t i = 0; i < n; ++i)
    {
        pices[i].vel -= full_momentum;
        pices[i].pos += pices[i].pre_pos;
        pices[i].pos += pices[i].vel * dt;
        int64_t off_x = floor(pices[i].pos.x/a);
        int64_t off_y = floor(pices[i].pos.y/a);
        int64_t off_z = floor(pices[i].pos.z/a);
        vect off_dr(-1*a*off_x,-1*a*off_y,-1*a*off_z);
        pices[i].pre_pos += off_dr;
        pices[i].pos += off_dr;
    }
}

field::~field()
{
    delete [] pices;
}

void field::print_pices_info() {
    for (int64_t i = 0; i < n; i++)
    {
        //std::cout << i << ": " << pices[i].pre_pos.x << ", " << pices[i].pre_pos.y << ", " << pices[i].pre_pos.z << "\n";
        std::cout << i << ": " << pices[i].vel.x << ", " << pices[i].vel.y << ", " << pices[i].vel.z << "\n";
        std::cout << i << ": " << pices[i].pos.x << ", " << pices[i].pos.y << ", " << pices[i].pos.z << "\n";
    }
    
}

void field::period_r(vect & r) {
    while (abs(r.x) > a/2)
    {
        if (r.x > a/2)
        {
            r.x -= a;
        } else {
            r.x += a;
        }
    }
    while (abs(r.y) > a/2)
    {
        if (r.y > a/2)
        {
            r.y -= a;
        } else {
            r.y += a;
        }
    }
    while (abs(r.z) > a/2)
    {
        if (r.z > a/2)
        {
            r.z -= a;
        } else {
            r.z += a;
        }
    }
}

vect field::count_force(Atom * p, Atom * e) {
    //force on atom p from atom e
    vect r;
    vect force;
    r = e->pos - p->pos;
    period_r(r);
    double len = r.sqr_len();
    force = r * (24*(pow(len,-4) - 2*pow(len,-7)));
    return force;
}

double field::count_potential_energy(Atom * p, Atom * e) {
    vect r;
    r = e->pos - p->pos;
    period_r(r);
    double len = r.sqr_len();
    return 4*(pow(len,-6) - pow(len, -3));
}


double field::count_kinetic_energy(Atom * p) {
    return p->vel.sqr_len()/2;
}

void field::make_ticks(int64_t num) {
    std::ofstream e_out;
    e_out.open("logs/energy.txt");
    for (int64_t i = 0; i < num; ++i)
    {
        tick();
        e_out << "Tick: " << i << ", energy: " << energy << ", penergy: " << p_energy << ", kenergy: " << k_energy << "\n";
        if ((i >= 2000) && !(i%100))
        {
            upd_vels();
        }
        
        //std::cout << "Tick " << i <<":\n"; 
        //print_pices_info();
        update();
        //std::cout << "------------\n";
    }
    e_out.close();
    std::ofstream vels_out;
    vels_out.open("logs/velocity.txt");
    vels_out << "n=" << n << "\n";
    for (int64_t i = 0; i < n; ++i)
    {
        pices[i].avg_vel /= pices[i].cnt;
        vels_out << i << " " << sqrt(pices[i].vel.sqr_len()) << " " << pices[i].avg_vel.x << " " << pices[i].avg_vel.y << " " << pices[i].avg_vel.z << "\n";
    }
    vels_out.close();
}

void field::tick() {
    k_energy = 0;
    p_energy = 0;
    energy = 0;
    //std::cout << "a";
    for (int64_t i = 0; i < n; ++i)
    {
        Atom * p = &pices[i];
        k_energy += count_kinetic_energy(p);
        p->acel *= 0;
        //std::cout << "b";
        for (int64_t j = 0; j < n; ++j)
        {
            if (j == i) continue;
            Atom * e = &pices[j];
            p->acel += count_force(p, e);
            if (j > i)
            {
                p_energy += count_potential_energy(p,e);
            }
            
        }
        //std::cout << "e";
        
    }
    energy = p_energy + k_energy;
    
    //std::cout << "f";
}


void field::update() {
    for (int64_t i = 0; i < n; ++i)
    {
        vect dr(0,0,0);
        vect dv(0,0,0);
        dv += (pices[i].acel * dt);
        dr += pices[i].pos;
        dr -= pices[i].pre_pos;
        dr += (pices[i].acel * pow(dt, 2));
        pices[i].pre_pos *= 0;
        pices[i].pre_pos += pices[i].pos;
        pices[i].pos += dr;
        pices[i].vel += dv;
        int64_t off_x = floor(pices[i].pos.x/a);
        int64_t off_y = floor(pices[i].pos.y/a);
        int64_t off_z = floor(pices[i].pos.z/a);
        vect off_dr(-1*a*off_x,-1*a*off_y,-1*a*off_z);
        pices[i].pre_pos += off_dr;
        pices[i].pos += off_dr;
    }
}

void field::upd_vels() {
    for (int64_t i = 0; i < n; ++i)
    {
        pices[i].avg_vel += pices[i].vel;
        pices[i].cnt += 1;
    }
}