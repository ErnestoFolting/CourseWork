#include "matrix.h"
#include "Validator.h"
#include "View.h"

double** matrix::multiplyMatrix(double** Matr1, int n1, int m1, double** Matr2, int n2, int m2)
{
	if (Validator::canMultiplyMatrix(m1, n2)) {
		double** Matr = new double* [n1];
		for (int i = 0; i < n1; i++) {
			Matr[i] = new double[m2];
		}
		for (int i = 0; i < n1; i++) {
			for (int j = 0; j < m2; j++) {
				Matr[i][j] = 0;
				for (int k = 0; k < n2; k++) {
					Matr[i][j] += Matr1[i][k] * Matr2[k][j];
					if (abs(Matr[i][j] - static_cast<int>(Matr[i][j])) < 0.00001) {
						Matr[i][j] = static_cast<int>(Matr[i][j]);
					}
				}
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

double** matrix::calculateMatrixB(double** Matr, int n, int stage)
{
	double** MatrB = crIdentityMatrix(n);
	for (int j = 0; j < n; j++) {
		if (j == n - stage-1) {
			MatrB[n - stage - 1][n - stage - 1] = 1 / (Matr[n-stage][n - stage - 1]);
		}
		else {
			MatrB[n - stage - 1][j] = -1 * (Matr[n-stage][j] / Matr[n-stage][n - stage - 1]);
		}
	}
	return MatrB;
}

double** matrix::calculateMatrixBReverse(double** Matr, int n,int stage)
{
	double** MatrReverse = crIdentityMatrix(n);
	for (int i = 0; i < n; i++) {
		MatrReverse[n-stage -1 ][i] = Matr[n - stage][i];
	}
	return MatrReverse;
}
double** matrix::calculateMatrixP(double** Matr, double**& similarMatrix, int n) {
	//add Matr copy
	double** MatrD = Matr;
	int k = 0;
	for (int i = 1; i < n; i++) {
		double** MatrB = calculateMatrixB(Matr, n, i);
		if (k >= 1) {
			similarMatrix = matrix::multiplyMatrix(similarMatrix, n, n, MatrB, n, n);
		}
		cout << "B:" << endl;
		View::outputMatr(MatrB, n, n);
		double** MatrBReverse = calculateMatrixBReverse(Matr, n,i);
		cout << "B reverse:" << endl;
		View::outputMatr(MatrBReverse, n, n);
		MatrD = matrix::multiplyMatrix(matrix::multiplyMatrix(MatrBReverse, n, n, Matr, n, n), n, n, MatrB, n, n);
		Matr = MatrD;
		cout << "D:" << endl;
		View::outputMatr(MatrD, n, n);
		k++;
	}
	return MatrD;
}