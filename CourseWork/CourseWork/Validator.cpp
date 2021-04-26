#include "Validator.h"

bool Validator::fileOpenCheck(ifstream& in)
{
    if (!in) {
        cout << " Can not open a file to read. \n";
        return false;
    }
    return true;
}
