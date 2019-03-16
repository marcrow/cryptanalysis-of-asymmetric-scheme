#include <set>
#include <utility>
#include <vector>
#include <stdlib.h>
#include<iostream>
#include <math.h>
#include <random>
#include <chrono>
#include "matriceNullSpace.h"
#include <gmpxx.h> //permet de gérer les grands nombres
#include <thread>


using namespace std;

//On a ici un tableau de paires :  son premier �l�ment est le nombre bsmooth, le second est un tableau de paire (pour chaque nombre, on a le nombre premier puis son exposant).
using bSmoothList = vector<pair<mpz_class, vector<pair<mpz_class, int>>>>;


//Genere une liste des entiers premiers inferieurs � B
vector<int> eratosthene(int B);

//Genere une liste d'entiers BSmooth
bSmoothList BSmoothGenerator(int n, int listSize, int range, vector<int> primeList);

//Operation du crible quadratique
int quadraSieve(mpz_class n);

//teste si l'entier test est BSmooth, et si oui rempli context prime avec sa decomposition
bool isBsmooth(int test, vector<int> prime, vector<pair<int, int>> &contextPrime);

//genere la matrice qui pourra etre traitee ensuite a partir de la BSmoothList
vector<vector<int>> generateMatrix(bSmoothList bsl, vector<int> pl);
vector<vector<mpz_class>> generateMatrixMpz(bSmoothList bsl, vector<int> pl);

mpz_class concurrentSieve(mpz_class n, bool *continuer, vector<int> primeList);
