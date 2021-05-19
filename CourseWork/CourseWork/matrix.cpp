#include "matrix.h"
#include "Validator.h"
#include <complex>
#include <vector>
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
void matrix::findSystem(double** Matr, int rows) {
	double** startVector2 = new double* [rows];
	double** system = new double* [rows];
	for (int i = 0; i < rows; i++) {
		startVector2[i] = new double[1];
		system[i] = new double[rows + 1];
	}
	for (int i = 0; i < rows; i++) {
		cout << "Input start vector:" << endl;
		cin >> startVector2[i][0];
	}
	vectorsY.push_back(startVector2);
	for (int i = 0; i < rows; i++) {
		system[i][rows - 1] = startVector2[i][0];
	}
	View::outputMatr(startVector2, rows, 1);
	for (int i = 0; i < rows; i++) {
		startVector2 = matrix::multiplyMatrix(Matr, rows, rows, startVector2, rows, 1);
		View::outputMatr(startVector2, rows, 1);
		vectorsY.push_back(startVector2);
		for (int j = 0; j < rows; j++) {
			system[j][(rows - 2) - i] = startVector2[j][0];
		}
	}
	for (int i = 0; i < rows; i++) {
		system[i][rows] = startVector2[i][0];
	}
	cout << "Check " << endl;
	View::outputMatr(system, rows, rows+1);
	this->system = system;
}
vector<double> matrix::Kramer(double** Matr,int rows ) {
	vector<double> p;
	double** roots = new double* [rows];
	double** main = new double* [rows];
	for (int i = 0; i < rows; i++) {
		roots[i] = new double[1];
		roots[i][0] = Matr[i][rows];
		main[i] = new double[rows];
		for (int j = 0; j < rows; j++) {
			main[i][j] = Matr[i][j];
		}
	}
	double mainDet = det(main, rows);
	View::outputMatr(roots, rows, 1);
	View::outputMatr(main, rows, rows);
	for (int l = 0; l < rows; l++) {
		double** tempMatr = new double* [rows];
		for (int k = 0; k < rows; k++)tempMatr[k] = new double[rows];
		for (int j = 0; j < rows; j++) {
			for (int i = 0; i < rows; i++) {
				if (j != l) {
					tempMatr[i][j] = main[i][j];
				}
				else {
					tempMatr[i][j] = roots[i][0];
				}
			}
		}
		double tempDet = det(tempMatr, rows);
		double root = round(tempDet / mainDet*1000)/1000;
		p.push_back(root);
	}
	return p;
}
double matrix::det(double** Matr, int N)
{
	double determ;
	int sub, s;
	double** Matr2;
	if (N < 1) return nan("1");
	if (N == 1)
		return Matr[0][0];
	if (N == 2)
		return Matr[0][0] * Matr[1][1] - Matr[0][1] * Matr[1][0];
	else {

		Matr2 = new double* [N - 1];
		determ = 0;
		s = 1;
		for (int i = 0; i < N; i++)
		{
			sub = 0;
			for (int j = 0; j < N; j++)
				if (i != j)
					Matr2[sub++] = Matr[j] + 1;

			determ = determ + s * Matr[i][0] * det(Matr2, N - 1);
			s = -s;
		};
		delete[] Matr2;
		return determ;
	}
}
void matrix::findQ(vector<double> roots, Root selfNumbers, int rows) {
	double** q = new double* [rows];
	for (int i = 0; i < rows; i++) {
		q[i] = new double[rows];
	}
	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < rows; i++) {
			if (i == 0) {
				q[i][j] = 1;
			}
			else {
				q[i][j] = real(selfNumbers.mas[j]) * q[i - 1][j] - roots[i-1];
			}
		}
	}
	View::outputMatr(q, rows, rows);
	this->q = q;
}

void matrix::findVectorsX() {
	for (int i = 0; i < rows; i++) {
		matrix tempRes(rows,1);
		for (int k = 0; k < rows; k++) {
			matrix tempY(rows,1);
			tempY.Matr = vectorsY[rows - 1 - k];
			if (k == 0) {
				tempRes = tempY * q[k][i];
			}
			else {
				tempRes = tempRes + tempY * q[k][i];
			}
		}
		toNorm(tempRes.Matr, rows);
		View::outputMatr(tempRes.Matr, rows, 1);
		vectorsX.push_back(tempRes.Matr);
	}
}

matrix matrix::operator*(double x)
{
	matrix newMatr(rows, columns);
	newMatr.Matr = new double*[rows];
	for (int i = 0; i < rows; i++){
		newMatr.Matr[i] = new double[columns];
		for (int j = 0; j < columns; j++) {
			newMatr.Matr[i][j] = this->Matr[i][j] * x;
		}
	}
	return newMatr;
}

matrix matrix::operator+(matrix tempMatr)
{
	matrix newMatr(rows, columns);
	newMatr.Matr = new double* [rows];
	for (int i = 0; i < rows; i++) {
		newMatr.Matr[i] = new double[columns];
		for (int j = 0; j < columns; j++) {
			newMatr.Matr[i][j] = Matr[i][j] + tempMatr.Matr[i][j];
		}
	}
	return newMatr;
}

matrix matrix::operator-(matrix tempMatr)
{
	matrix newMatr(rows, columns);
	newMatr.Matr = new double* [rows];
	for (int i = 0; i < rows; i++) {
		newMatr.Matr[i] = new double[columns];
		for (int j = 0; j < columns; j++) {
			newMatr.Matr[i][j] = Matr[i][j] - tempMatr.Matr[i][j];
		}
	}
	return newMatr;
}