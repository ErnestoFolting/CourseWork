#include <iostream>
#include "View.h"
#include "matrix.h"
#include "fileReader.h"
#include "Polinom.h"

int main()
{
	//int n;
	//double** Matr = fileReader::inputMatr(n);
	//View::outputMatr(Matr, n, n);
	//double** similarMatrix = matrix::calculateMatrixB(Matr, n, 1);
	//double** MatrP = matrix::calculateMatrixP(Matr, similarMatrix, n);
	//cout << "Matr P: " << endl;
	//View::outputMatr(MatrP, n, n);
	////View::outputMatr(similarMatrix, n, n);
	Polinom tempPol;
	tempPol.setPow(3);
	cout << tempPol.getPow();
	double* Mas = tempPol.getMas();
	Mas[0] = 5;
	cout << tempPol.getMas()[0];
}