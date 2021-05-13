#include "fileReader.h"
#include "Validator.h"

double** fileReader::inputMatr(int& n)
{
    cout << "Input the number of raws and columns:" << endl;
    cin >> n;
    double** Matr = new double* [n];
    for (int i = 0; i < n; i++) {
        Matr[i] = new double[n];
    }
    ifstream inFile("Example.txt");
    if (Validator::fileOpenCheck(inFile)) {
        double tempNum;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {   
                inFile >> tempNum;
                Matr[i][j] = tempNum;
            }
        }
    }
    return Matr;
}
