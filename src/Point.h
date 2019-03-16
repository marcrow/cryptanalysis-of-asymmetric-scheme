#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <stdint.h>
#include <gmpxx.h> //permet de gérer les grands nombres

class Point{
    public:
        Point(unsigned int x, mpz_class y, mpz_class z);
        Point();
        bool operator==(Point const& p2);
        void operator=(Point const& p2);
        unsigned int x;
        mpz_class y;
        mpz_class z;
};

bool operator==(Point const& p1, Point const& p2);

#endif // POINT_H_INCLUDED
