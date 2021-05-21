#pragma once
#include "matrix.h"
#include <fstream>
#include <iomanip>
using namespace std;
class fileWriter
{
public:
	static void outputSelf(matrix tempMatr);
	static void outputMatr(matrix tempMatr);
};

