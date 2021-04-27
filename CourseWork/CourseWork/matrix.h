#pragma once
class matrix
{
public:
	static double** multiplyMatrix(double** Matr1, int n1, int m1, double** Matr2, int n2, int m2);
	static double** crIdentityMatrix(int n);
	static double** calculateMatrixB(double** Matr, int n, int stage);
	static double** calculateMatrixBReverse(double** Matr, int n,int stage);
	static double** calculateMatrixP(double** Matr, double**& similarMatrix, int n);
};

