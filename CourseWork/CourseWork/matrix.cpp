#include "matrix.h"
#include "Validator.h"
#include "fileWriter.h"
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

void matrix::calculateMatrixB(int stage)
{
	MatrB = crIdentityMatrix(rows);
	for (int j = 0; j < rows; j++) {
		if (j == rows - stage-1) {
			MatrB[rows - stage - 1][rows - stage - 1] = 1 / (Matr[rows-stage][rows - stage - 1]);
		}
		else {
			MatrB[rows - stage - 1][j] = -1 * (Matr[rows-stage][j] / Matr[rows-stage][rows - stage - 1]);
		}
	}
	if (stage == 1) {
		MatrBN = MatrB;
	}
	else {
		MatrBN = multiplyMatrix(MatrBN, rows, rows, MatrB, rows, rows);
	}
}

double** matrix::calculateMatrixBReverse(double** Matr, int n,int stage)
{
	double** MatrReverse = crIdentityMatrix(n);
	for (int i = 0; i < n; i++) {
		MatrReverse[n-stage -1 ][i] = Matr[n - stage][i];
	}
	return MatrReverse;
}
void matrix::calculateMatrixP() {
	double** MatrD = Matr;
	vector<double> p;
	int k = 0;
	for (int i = 1; i < rows; i++) {
		calculateMatrixB(i);
		cout << "B:" << endl;
		View::outputMatr(MatrB, rows, rows);
		double** MatrBReverse = calculateMatrixBReverse(Matr, rows,i);
		cout << "B reverse:" << endl;
		View::outputMatr(MatrBReverse, rows, rows);
		MatrD = matrix::multiplyMatrix(matrix::multiplyMatrix(MatrBReverse, rows, rows, Matr, rows, rows), rows, rows, MatrB, rows, rows);
		Matr = MatrD;
		cout << "D:" << endl;
		double currentD;
		if (rows - 3 - k >= 0) {
			currentD = MatrD[rows - i - 1][rows - 3 - k];
			cout << "5" << " " << rows - 3 - k << " " << currentD<< endl;
			if (currentD == 0) {
				bool flag = false;
				for (int j = 0; j < rows - 3 - k; j++) {
					if (MatrD[rows - i - 1][j] != 0) {
						flag = true;
						for (int l = 0; l < rows; l++) {
							double temp = MatrD[l][rows - 3 - k];
							MatrD[l][rows - 3 - k] = MatrD[l][j];
							MatrD[l][j] = temp;
							double temp2 = MatrD[rows - 3 - k][l];
							MatrD[rows - 3 - k][l] = MatrD[j][l];
							MatrD[j][l] = temp2;
						}
						matrix newMatr(rows);
						newMatr.setMatr(MatrD);
						newMatr.Danilevsky();
					}
				}
				if (flag == false) {
					double** tempMatr = new double*[rows - 3 - k + 1];
					for (int u = 0; u < rows - 3 - k + 1; u++)tempMatr[u] = new double[rows - 3 - k + 1];
					for (int h = 0; h < rows - 3 - k + 1; h++) {
						for (int t = 0; t < rows - 3 - k + 1; t++) {
							tempMatr[h][t] = MatrD[h][t];
						}
					}
					matrix newMatr(rows - 3 - k + 1);
					newMatr.setMatr(tempMatr);
					newMatr.Danilevsky();
				}
			}
		}
		View::outputMatr(MatrD, rows, rows);
		k++;
	}
	for (int i = 0; i < rows; i++)p.push_back(MatrD[0][i]);
	this->p = p;
}
void matrix::Danilevsky() {
	fileWriter::outputMatr(*this);
	View::outputMatr(Matr, rows, rows);
	calculateMatrixP();
	findRoots();
	createSelfVectors();
	fileWriter::outputSelf(*this);
}

void matrix::Krylov() {
	View::outputMatr(Matr, rows, rows);
	fileWriter::outputMatr(*this);
	findSystem();
	Kramer();
	findRoots();
	findQ();
	findVectorsX();
	fileWriter::outputSelf(*this);
}
void matrix::createSelfVectors() {
	for (int i = 0; i < rows; i++) {
		double** tempMatr = new double*[rows];
		for (int j = 0; j < rows; j++) {
			tempMatr[j] = new double[1];
		}
		for (int k = 0; k < rows; k++) {
			double temp = real(r.mas[i]);
			cout << endl << "temp: " << temp << endl;
			tempMatr[k][0] = round(pow(temp, rows - k - 1)*1000)/1000;
		}cout << "Y" << i+1 << ":" << endl;
		View::outputMatr(tempMatr, rows, 1);
		View::outputMatr(MatrBN,rows , rows);
		double** tempMatr2 = matrix::multiplyMatrix(MatrBN, rows, rows, tempMatr, rows, 1);
		View::outputMatr(tempMatr2, rows, 1);
		matrix::toNorm(tempMatr2, rows);
		View::outputMatr(tempMatr2, rows, 1);
		vectorsX.push_back(tempMatr2);
	}
}
double** matrix::getMatr()
{
	return Matr;
}
void matrix::setMatr(double** tempMatr)
{
	Matr = tempMatr;
}
int matrix::getRows() {
	return rows;
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
void matrix::findSystem() {
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
void matrix::Kramer() {
	double** roots = new double* [rows];
	double** main = new double* [rows];
	for (int i = 0; i < rows; i++) {
		roots[i] = new double[1];
		roots[i][0] = system[i][rows];
		main[i] = new double[rows];
		for (int j = 0; j < rows; j++) {
			main[i][j] = system[i][j];
		}
	}
	double mainDet = det(main, rows);
	cout << " Check6" << endl;
	View::outputMatr(roots, rows, 1);
	cout << " Check7" << endl;
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
		cout << "root" << root << endl;
		this->p.push_back(root);
	}
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
void matrix::findQ() {
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
				q[i][j] = real(r.mas[j]) * q[i - 1][j] - p[i-1];
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
void matrix::findRoots() {
	Polinom polinom(this->p);
	Root r;
	Polinom::FindAllRoot(polinom, r);
	for (int i = 0; i < r.num; i++) {
		cout << "self:" << real(r.mas[i]) << endl;
	}
	this->r = r;
}