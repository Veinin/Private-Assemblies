#include "String.h"

int main(void)
{
	String s1("abc");

	//拷贝构造函数
	String s2(s1);

	//赋值运算符重载
	String s3 = s2;
	s3.Display();

	s3 = "haha";
	s3.Display();

	//!运算符重载
	String s4;
	cout << !s4 << endl;

	s4 = "lol";
	cout << !s4 << endl;

	//[]运算符重载
	char ch = s4[1];
	cout << ch << endl;

	s4[1] = 'l'; //非const运算符重载
	s4.Display();

	const String s5("abc");
	ch = s5[1]; //const运算符重载
	cout << ch << endl;

	//=运算符重载
	String s6;
	s6 = "aaa";
	String s7;
	s7 = "bbb";
	String s8 = s6 + s7;
	s8.Display();

	//+=运算符重载
	s8 += s7;
	s8.Display();

	//流对象重载
	cout << s8 << endl;

	String s9;
	cin >> s9;
	cout << s9 << endl;
	
	return 0;
}
