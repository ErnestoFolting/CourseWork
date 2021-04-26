#include "View.h"

void View::outputMatr(double** Matr, int n, int m)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(6) << Matr[i][j];
        }
        cout << endl;
    }
}
