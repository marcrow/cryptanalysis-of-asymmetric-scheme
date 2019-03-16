#include<iostream>
#include <cmath>

#include"Point.h"

Point::Point(){
    x = 0;
    y = 1;
    z = 0;
}

Point::Point(unsigned int x, mpz_class y, mpz_class z){
    this->x = x;
    this->y = y;
    this->z = z;
}

bool Point::operator==(Point const& p2){
    return (x == p2.x && y == p2.y && z == p2.z);
}

void Point::operator=(Point const& p2){
    x = p2.x;
    y = p2.y;
    z = p2.z;
}
