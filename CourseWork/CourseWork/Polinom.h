#pragma once
#include <iostream>
#include <cmath>
#include <complex>
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
    Polinom():n(0){};
};

