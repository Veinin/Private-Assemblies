#ifndef _COMPLEX_H_
#define _COMPLEX_H_

class Complex
{
public:
	Complex(int real, int imag);
	~Complex();

	void Display() const;

	Complex operator+(const Complex& other);
	friend Complex operator+(const Complex& c1, const Complex& c2); //重载相同的函数时，优先调用成员函数

private:
	int real_;
	int imag_;
};

#endif
