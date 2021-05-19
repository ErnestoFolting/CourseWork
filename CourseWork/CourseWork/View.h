#pragma once
#include <iostream>
#include <iomanip>
#include <vector>

class View
{
public:
	static void outputMatr(double** Matr, int n, int m);
	static void outputVector(std::vector<double> tempVector);
	static void canNotOpenAFile();
	static void canNotMultiplyMatrix();
};

