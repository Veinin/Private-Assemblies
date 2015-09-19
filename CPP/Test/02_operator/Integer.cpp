#include "Integer.h"
#include <iostream>
using namespace std;

Integer::Integer(int n) : n_(n)
{

}

void Integer::Display() const
{
	cout << n_ << endl;
}

Integer& Integer::operator++()
{
	++n_;
	return *this;
}

//Integer& operator++(Integer& i)
//{
//	++i.n_;
//	return i;
//}

Integer Integer::operator++(int i)
{
	Integer temp(n_);
	n_++;
	return temp;
}

//Integer operator++(int i)
//{
//	Integer temp(n_);
//	n_++;
//	return temp;
//}
