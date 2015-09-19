#include "Complex.h"
#include <iostream>
using namespace std;

Complex::Complex(int real, int imag) : real_(real), imag_(imag)
{

}

Complex::~Complex()
{

}

void Complex::Display() const
{
	cout << "real : " << real_ << " iamg : " << imag_ << endl;
}

Complex Complex::operator+(const Complex& other)
{
	int r = real_ + other.real_;
	int i = imag_ + other.imag_;

	return Complex(r, i);
}

Complex operator+(const Complex& c1, const Complex& c2)
{
	int r = c1.real_ + c2.real_;
	int i = c1.imag_ + c2.imag_;

	return Complex(r, i);
}
