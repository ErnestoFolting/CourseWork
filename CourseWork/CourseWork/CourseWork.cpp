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
	View::outputMatr(res, n,n);
}
