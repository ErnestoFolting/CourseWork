#include <iostream>
#include "View.h"
#include "matrix.h"
#include "fileReader.h"
int main()
{
	int n;
	double** Matr = fileReader::inputMatr(n);
	View::outputMatr(Matr, n, n);
	double** res = matrix::multiplyMatrix(Matr, n, n, Matr, n, n);
	View::outputMatr(res, n, n);
	double** iden = matrix::crIdentityMatrix(4);
	View::outputMatr(iden, 4, 4);
	double** res2 = matrix::calculateMatrixB(Matr, n);
	View::outputMatr(res2, n, n);
	cout << endl;
	double** res3 = matrix::calculateMatrixBReverse(Matr, n);
	View::outputMatr(res3, n, n);
	double** res4 = matrix::multiplyMatrix(matrix::multiplyMatrix(res3, n, n, Matr, n, n), n, n, res2, n, n);
	cout << endl;
	View::outputMatr(res4, n, n);
}
