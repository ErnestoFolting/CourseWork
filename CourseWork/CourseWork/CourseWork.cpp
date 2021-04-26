#include <iostream>
#include "View.h"
#include "fileReader.h"
int main()
{
	int n;
	double** Matr = fileReader::inputMatr(n);
	View::outputMatr(Matr, n, n);
}
