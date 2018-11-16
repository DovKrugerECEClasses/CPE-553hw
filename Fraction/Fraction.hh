#pragma once
#include <iostream>

class Fraction {
private:
	int num, den;
	void simplify();
public:
	Fraction(int n, int d);
	friend Fraction	operator +(Fraction left, Fraction right);
	Fraction operator -(Fraction f);
	friend std::ostream& operator <<(std::ostream& s, Fraction f);
};
