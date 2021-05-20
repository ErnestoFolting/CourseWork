#pragma once
#include "Root.h"
#include "Polinom.h"
#include <vector>

class matrix
{
	int columns;
	double** system;
	std::vector<double> p;
	double** q;
	Root r;
	std::vector<double**> vectorsY;
	std::vector<double**> vectorsX;
	double** MatrP;
	double** MatrBN;
	double** MatrB;
	int rows;
public:
	double** Matr;
	int getRows();
	matrix(int n):rows(n),columns(n){}
	matrix(int n, int m):rows(n),columns(m){}
	static double** multiplyMatrix(double** Matr1, int n1, int m1, double** Matr2, int n2, int m2);
	static double** crIdentityMatrix(int n);
	void calculateMatrixB (int stage);
	static double** calculateMatrixBReverse(double** Matr, int n,int stage);
	void calculateMatrixP();
	void createSelfVectors();
	static void toNorm(double** Matr, int rows);
	void findRoots();
	void findSystem();
	void Kramer();
	static double det(double** matr, int N);
	void findQ();
	void findVectorsX();
	matrix operator*(double x);
	matrix operator+(matrix tempMatr);
	matrix operator-(matrix tempMatr);
};

