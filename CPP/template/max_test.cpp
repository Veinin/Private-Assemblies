#include <iostream>
#include "max.h"

using namespace std;

int main(void)
{
	cout << ::max(5.5, 6.6) << endl; //自动推导max(const int&, const int&)
	cout << ::max('a', 'c') << endl;

	const char *a = "aaa";
	const char *b = "ccc";
	cout << ::max(a, b) << endl;

	cout << ::max(1, 5, 3) << endl;

	cout << ::max(97, 100) << endl;	     //max(const int& a, const int& b)
	cout << ::max<>(97, 100) << endl;    //自动推导max(const int&, const int&)
	cout << ::max<int>(97, 100) << endl; //显示指定模板

	return 0;
}
