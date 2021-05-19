#pragma once
#include "Root.h"
#include <vector>

class matrix
{
public:
	double** Matr;
	int rows;
	int columns;
	std::vector<double> startVector;
	double** system;
	double** q;
	std::vector<double**> vectorsY;
	std::vector<double**> vectorsX;
	matrix(int n):rows(n),columns(n){}
	matrix(int n, int m):rows(n),columns(m){}
	static double** multiplyMatrix(double** Matr1, int n1, int m1, double** Matr2, int n2, int m2);
	static double** crIdentityMatrix(int n);
	static double** calculateMatrixB(double** Matr, int n, int stage);
	static double** calculateMatrixBReverse(double** Matr, int n,int stage);
	static double** calculateMatrixP(double** Matr, double**& similarMatrix, int n);
	static void createSelfVectors(Root roots, double** MatrB);
	static void toNorm(double** Matr, int rows);
	void findSystem(double** Matr, int rows);
	static std::vector<double>Kramer(double** Matr, int rows);
	static double det(double** matr, int N);
	void findQ(std::vector<double> roots, Root selfNumbers, int rows);
	void findVectorsX();
	matrix operator*(double x);
	matrix operator+(matrix tempMatr);
	matrix operator-(matrix tempMatr);
};

