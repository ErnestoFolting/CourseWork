#include <iostream>
#include "View.h"
#include "matrix.h"
#include "fileReader.h"
#include <cmath>
#include <ctime>
#include "Polinom.h"
#include "Root.h"
#include <complex>
#include <vector>

#define NMAX 30
typedef std::complex<double> complex;

int main()
{
	int k, n;
	std::cout << "input k " << std::endl;
	std::cin >> k;
	std::cout << "Input the number of raws and columns:" << std::endl;
	std::cin >> n;
	srand(time(0));
	matrix Matrix(n);
	Matrix.setMatr(fileReader::inputMatr(Matrix.getRows()));
	if (k == 1) {
		Matrix.Danilevsky();
	}
	else {
		Matrix.Krylov();
	}
}
