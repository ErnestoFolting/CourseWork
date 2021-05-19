#include <iostream>
#include "View.h"
#include "matrix.h"
#include "fileReader.h"
#include <cmath>
#include <ctime>
#include "Polinom.h"
#include "Root.h"
#include <complex>
#include <vector>

#define NMAX 30
typedef std::complex<double> complex;

int main()
{
	/*double** similarMatrix = matrix::calculateMatrixB(Matr, n, 1);
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
	*/
	srand(time(0));
	int n;
	double** Matr = fileReader::inputMatr(n);
	View::outputMatr(Matr, n, n);
	double** system = matrix::findSystem(Matr, n);
	std::vector<double> roots = matrix::Kramer(system, n);
	for (int i = 0; i < roots.size(); i++) {
		std::cout << "Root:" << roots[i] << std::endl;
	}
	Polinom polinom(roots);
	Root r;
	Polinom::FindAllRoot(polinom, r);
	for (int k = 0; k < r.num; k++) {
		double temp = round(real(r.mas[k]) * 1000) / 1000;
		std::cout << std::endl << "temp: " << temp << std::endl;
		//matrix::findY(Matr, n, n );
	} 
	matrix::findQ(roots, r, n);
}
