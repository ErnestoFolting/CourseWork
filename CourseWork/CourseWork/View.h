#pragma once
#include <iostream>
#include <iomanip>
using namespace std;
class View
{
public:
	static void outputMatr(double** Matr, int n, int m);
	static void canNotOpenAFile();
	static void canNotMultiplyMatrix();
};

