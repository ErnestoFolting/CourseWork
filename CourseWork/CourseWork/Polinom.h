#pragma once
#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include "Root.h"
typedef std::complex<double> complex;
#define NMAX 20
class Polinom
{
public:
    complex  mas[NMAX];
    int n;
    static complex FPol(Polinom& p, complex& x);
    static void FindAllRoot(Polinom& pp, Root& r);
    Polinom(double** Matr, int n);
    Polinom(std::vector<double>);
    Polinom() :n(0) {};

};

