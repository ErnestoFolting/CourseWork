#include "matrix.h"
#include "Validator.h"

double** matrix::multiplyMatrix(double** Matr1, int n1, int m1, double** Matr2, int n2, int m2)
{
	if (Validator::canMultiplyMatrix(m1, n2)) {
		double** Matr = new double* [n1];
		for (int i = 0; i < n1; i++) {
			Matr[i] = new double[m2];
		}
		for (int i = 0; i < n1; i++) {
			for (int j = 0; j < m2; j++) {
				double el = 0;
				for (int k = 0; k < n2; k++) {
					el += Matr1[i][k] * Matr2[k][j];
				}
				Matr[i][j] = el;
			}
		}
		return Matr;
	}
}

double** matrix::crIdentityMatrix(int n)
{
	double** Matr = new double* [n];
	for (int i = 0; i < n; i++) {
		Matr[i] = new double[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				Matr[i][j] = 1;
			}
			else {
				Matr[i][j] = 0;
			}
		}
	}
	return Matr;
}

double** matrix::calculateMatrixB(double** Matr, int n)
{
	double** MatrB = crIdentityMatrix(n);
	for (int j = 0; j < n; j++) {
		if (j == n - 2) {
			MatrB[n - 2][n - 2] = 1 / (Matr[n-1][n - 2]);
		}
		else {
			MatrB[n - 2][j] = -1 * (Matr[n-1][j] / Matr[n-1][n - 2]);
		}
	}
	return MatrB;
}

double** matrix::calculateMatrixBReverse(double** Matr, int n)
{
	double** MatrReverse = crIdentityMatrix(n);
	for (int i = 0; i < n; i++) {
		MatrReverse[n-2][i] = Matr[n - 1][i];
	}
	return MatrReverse;
}
