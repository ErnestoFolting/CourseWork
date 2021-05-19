#include "View.h"
using namespace std;
void View::outputMatr(double** Matr, int n, int m)
{
    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(10) << Matr[i][j];
        }
        cout << endl;
    }
}

void View::outputVector(vector<double> tempVector)
{
    for (int i = 0; i < tempVector.size(); i++) {
        cout << tempVector[i] << endl;
    }
}

void View::canNotOpenAFile()
{
    cout << " Can not open a file to read. \n";
}

void View::canNotMultiplyMatrix()
{
    cout << "Can not multiply matrix\n";
}
