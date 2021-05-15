#include <iostream>
#include "View.h"
#include "matrix.h"
#include "fileReader.h"
#include <cmath>
#include "Polinom.h"
#include "Root.h"
#include <complex>
#define NMAX 30
typedef std::complex<double> complex;

int main()
{
	int n;
	double** Matr = fileReader::inputMatr(n);
	View::outputMatr(Matr, n, n);
	double** similarMatrix = matrix::calculateMatrixB(Matr, n, 1);
	double** MatrP = matrix::calculateMatrixP(Matr, similarMatrix, n);
	std::cout << "Matr P: " << std::endl;
	View::outputMatr(MatrP, n, n);
	std::cout << "Matr B:" << std::endl;
	View::outputMatr(similarMatrix, n, n);
	setlocale(LC_ALL, "Russian");
	Polinom p(MatrP, n);
	Root r;
	Polinom::FindAllRoot(p, r);
	matrix::createSelfVectors(r, similarMatrix);
}