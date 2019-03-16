#ifndef ELLIPTIQUE_H_INCLUDED
#define ELLIPTIQUE_H_INCLUDED

#include"Point.h"
unsigned gcd(unsigned u, unsigned v);
class Elliptique{
    public:
        Elliptique(mpz_class a, mpz_class x, mpz_class y, mpz_class n);
        Point addition(Point p1, Point p2);
        mpz_class get_res();
    private:
        mpz_class a, b, x, y, n, res;
        Point O;



};

#endif // ELLIPTIQUE_H_INCLUDED
