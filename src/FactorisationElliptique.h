#include <iostream>
#include <tgmath.h>
#include <stdint.h>
#include <thread>
#include <vector>

#include "Elliptique.h"

void factorisationElliptique(mpz_class n);
mpz_class courbe(mpz_class n, mpz_class h, mpz_class k, bool *conti);
