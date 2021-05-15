#include "matrix.h"
#include "Validator.h"
#include <complex>
#include "View.h"
typedef std::complex<double> complex;
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
				}
				Matr[i][j] = round(Matr[i][j] * 1000) / 1000;
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
void matrix::createSelfVectors(Root roots,double** MatrB) {
	for (int i = 0; i < roots.num; i++) {
		double** tempMatr = new double*[roots.num];
		for (int j = 0; j < roots.num; j++) {
			tempMatr[j] = new double[1];
		}
		for (int k = 0; k < roots.num; k++) {
			double temp = round(real(roots.mas[i])*1000)/1000;
			cout << endl << "temp: " << temp << endl;
			tempMatr[k][0] = pow(temp, roots.num - k - 1);
		}cout << "Y" << i+1 << ":" << endl;
		View::outputMatr(tempMatr, roots.num, 1);
		double** tempMatr2 = matrix::multiplyMatrix(MatrB, 4, 4, tempMatr, 4, 1);
		View::outputMatr(tempMatr2, 4, 1);
		matrix::toNorm(tempMatr2, 4);
		View::outputMatr(tempMatr2, 4, 1);
	}
}
void matrix::toNorm(double** Matr, int rows) {
	double sum = 0;
	for (int i = 0; i < rows; i++) {
		sum += pow(Matr[i][0], 2);
	}
	sum = sqrt(sum);
	cout << "sum " << sum << endl;
	for (int i = 0; i < rows; i++) {
		Matr[i][0] = round(Matr[i][0] / sum*1000)/1000;
	}
}
void matrix::findY(double** Matr, int rows, int columns) {
	double** startVector = new double* [rows];
	for (int i = 0; i < rows; i++) {
		startVector[i] = new double[1];
	}
	for (int i = 0; i < rows; i++) {
		startVector[i][0] = rand() % 2;
	}
	View::outputMatr(startVector, rows, 1);
	for (int i = 0; i < rows; i++) {
		startVector = matrix::multiplyMatrix(Matr, rows, columns, startVector, rows, 1);
		View::outputMatr(startVector, rows, 1);
	}
}
