#include "Validator.h"
#include "View.h"


bool Validator::fileOpenCheck(ifstream& in)
{
    if (!in) {
        View::canNotOpenAFile();
        return false;
    }
    return true;
}

bool Validator::canMultiplyMatrix(int m1, int m2)
{
    if (m1 == m2) return true;
    View::canNotMultiplyMatrix();
    return false;
}
