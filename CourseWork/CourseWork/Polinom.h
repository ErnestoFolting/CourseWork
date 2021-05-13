#pragma once

#define MAX 30
class Polinom
{
	int pow;
	double mas[MAX];
public:
	int getPow() { return pow; }
	void setPow(int pow) { this->pow = pow; }
	double* getMas() { return mas; }
};

