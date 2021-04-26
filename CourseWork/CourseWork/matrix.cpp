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
