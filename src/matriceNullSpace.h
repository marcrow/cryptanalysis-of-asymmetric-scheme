#ifndef NULL_SPACE_H
#define NULL_SPACE_H

#include <iostream>
#include <stddef.h>
#include <vector>
#include <cstdlib> //abs()
#include <gmpxx.h> //permet de gérer les grands nombres

/*Génère une matrice identité de taille colonne*colonne*/
void generateId(int column, std::vector<std::vector<int>> &id);
/*Affiche une matrice*/
void displayMatrix(std::vector<std::vector<int>> matrix);
void displayMatrix(std::vector<std::vector<mpz_class>> matrix);
/* intervertis deux lignes d'une matrice*/
void swapRow(std::vector<std::vector<int>> &matrix, int row1, int row2);
void swapRow(std::vector<std::vector<mpz_class>> & matrix, int row1, int row2);
/* Tente d'intervertir les lignes pour obtenir une matrice avec
diagonale composée de 1*/
void generateDiagonal(int column, int row, std::vector<std::vector<int>> &matrix, std::vector<std::vector<int>> &id);
void generateDiagonal(int column, int row, std::vector<std::vector<int>> &matrix, std::vector<std::vector<int>> &id);
/* sort les vecteurs générateurs de la matrice qui a ddéjà subit le process generateDiagonal*/
std::vector<std::vector<int>> resolveNullSpace(int column, int row, std::vector<std::vector<int>> &matrix);
std::vector<std::vector<mpz_class>> resolveNullSpace(int column, int row, std::vector<std::vector<mpz_class>> &matrix);
//passe une matrice modulo 2
std::vector<std::vector<int>> modulo2(std::vector<std::vector<int>> &matrix);
/*Fait tout, combine generateDiagonal et resolveNullSpace*/
std::vector<std::vector<int>> resolve(std::vector<std::vector<int>> &matrix);
std::vector<std::vector<mpz_class>> resolve(std::vector<std::vector<mpz_class>> &matrix);
/* Permet de faire la transposé d'une matrice*/
std::vector<std::vector<int>> transpose(std::vector<std::vector<int>> matrix);
std::vector<std::vector<mpz_class>> transpose(std::vector<std::vector<mpz_class>> matrix);
/* Réalise l'opération matrixA * matrixB */
std::vector<std::vector<int>> multiplication(std::vector<std::vector<int>> matrixA, std::vector<std::vector<int>> matrixB);
std::vector<std::vector<mpz_class>> multiplicationMpz(std::vector<std::vector<int>> matrixA, std::vector<std::vector<int>> matrixB);
/*Permet de résoudre l'opération T * primeList pour chaque solution trouvé on obtient un vecteur ou chaque valeur est un Y potentiel*/
std::vector<std::vector<mpz_class>> properDxPrimeList(std::vector<std::vector<int>> matrixA, std::vector<int> primeList, mpz_class n);
std::vector<std::vector<mpz_class>> properDxPrimeList(std::vector<std::vector<mpz_class>> matrixA, std::vector<int> primeList, mpz_class n);
std::vector<std::vector<mpz_class>> properDxPrimeList(std::vector<std::vector<int>> matrixA, std::vector<mpz_class> primeList, mpz_class n);
std::vector<std::vector<mpz_class>> properDxPrimeList(std::vector<std::vector<mpz_class>> matrixA, std::vector<mpz_class> primeList, mpz_class n);

//permet de résoudre le dernier calcul pgcd((X-Y),n) si auncun résultat valable retourne un vector vide
std::vector<mpz_class> finalGCD(std::vector<std::vector<mpz_class>> yList, std::vector<std::vector<mpz_class>> xList, mpz_class n);
#endif
