#include <iostream>
#include "View.h"
#include "matrix.h"
#include "fileReader.h"
int main()
{
	int n;
	double** Matr = fileReader::inputMatr(n);
	View::outputMatr(Matr, n, n);
	double** MatrD = matrix::calculateMatrixP(Matr, n);
	cout << endl;
	View::outputMatr(MatrD, n, n);
}
