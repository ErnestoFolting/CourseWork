#pragma once
#include <fstream>
#include <iostream>
using namespace std;
class Validator
{
public:
	static bool fileOpenCheck(ifstream& in);
	static bool canMultiplyMatrix(int m1, int m2);
};

