#include <iostream>
#include "View.h"
#include "matrix.h"
#include "fileReader.h"
int main()
{
	int n;
	double** Matr = fileReader::inputMatr(n);
	View::outputMatr(Matr, n, n);
	double** similarMatrix = matrix::calculateMatrixB(Matr, n, 1);
	double** MatrD = matrix::calculateMatrixP(Matr, similarMatrix, n);
	cout << endl;
	View::outputMatr(similarMatrix, n, n);
}
