#include<iostream>
#include <cmath>
#include "Elliptique.h"

using namespace std;

Elliptique::Elliptique(mpz_class a, mpz_class x, mpz_class y, mpz_class n){
    mpz_class pow1, pow2;
    this->a = a;
    this->x = x;
    this->y = y;
    this->n = n;
    mpz_pow_ui(pow1.get_mpz_t(), y.get_mpz_t(), 2);
    mpz_pow_ui(pow1.get_mpz_t(), x.get_mpz_t(), 3);
    this->b = (pow1+pow2-a*x);
    res = -1;
}

Point Elliptique::addition(Point p1, Point p2){
    mpz_class pow1, gcd1, gcd2, p_gcd1, p_gcd2;
    Point p3;
    if(p1 == O)
        p3 = p2;
    else if(p2 == O)
        p3 = p1;
    else{
        p_gcd1 = p1.x-p2.x;
        mpz_gcd(gcd1.get_mpz_t(), p_gcd1.get_mpz_t(), n.get_mpz_t());
        if(gcd1 == 1){
            mpz_class lambda = (p1.y-p2.y)/(p1.x-p2.x);
            mpz_pow_ui(pow1.get_mpz_t(), lambda.get_mpz_t(), 2);
            p3.x = pow1.get_ui()-p1.x-p2.x;
            p3.y = lambda*(p1.x-p3.x)-p1.y;
            p3.z = 1;
        }else if(gcd1 == n){
            p_gcd2 = p1.y+p2.y;
            mpz_gcd(gcd2.get_mpz_t(), p_gcd2.get_mpz_t(), n.get_mpz_t());
            if(gcd2 == 1){
                mpz_ui_pow_ui(pow1.get_mpz_t(), p1.x, 2);
                mpz_class lambda = (3*pow1+a)/(p1.y+p2.y);
                mpz_pow_ui(pow1.get_mpz_t(), lambda.get_mpz_t(), 2);
                p3.x = pow1.get_ui()-p1.x-p2.x;
                p3.y = lambda*(p1.x-p3.x)-p1.y;
                p3.z = 1;
            }else if(gcd2 != n){
                res = gcd2;
            }
        } else{
           res = gcd1;
        }
    }
    return p3;
}

mpz_class Elliptique::get_res(){
  return res;
}
