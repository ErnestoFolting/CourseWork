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
	int n;
	std::cout << "Input the number of raws and columns:" << std::endl;
	std::cin >> n;
	srand(time(0));
	matrix Matrix(n);
	Matrix.Matr = fileReader::inputMatr(Matrix.rows);
	View::outputMatr(Matrix.Matr, Matrix.rows, Matrix.rows);
	Matrix.findSystem();
	Matrix.Kramer();
	for (int i = 0; i < Matrix.p.size(); i++) {
		std::cout << "Root: " << Matrix.p[i] << std::endl;
	}
	Polinom polinom(Matrix.p);
	Root r;
	Polinom::FindAllRoot(polinom, r);
	for (int k = 0; k < r.num; k++) {
		double temp = round(real(r.mas[k]) * 1000) / 1000;
		std::cout << std::endl << "temp: " << temp << std::endl;
	} 
	Matrix.findQ(Matrix.p, r, n);
	Matrix.findVectorsX();

}
