/**
函数对象

*/
#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

class FunObj {
public:
	void operator()() {
		cout << "hello fun obj" << endl;
	}

	void operator()(int n) {
		cout << "hello2 fun obj" << endl;
	}
};

class PrintObj {
public:
	void operator()(int n) {
		cout << n << ' ';
	}
};

int main(void) {
	//普通函数对象使用
	FunObj fo;
	fo();
	fo(1);

	FunObj()();	//第一个括号构造一个对象，第二个调用括号运算符

	//函数对象与容器
	map<int, string> mapTest;
	mapTest.insert(map<int, string>::value_type(1, "aaa"));
	mapTest.insert(map<int, string>::value_type(3, "bbb"));
	mapTest.insert(map<int, string>::value_type(2, "ccc"));

	map<int, string>::iterator it;
	for(it = mapTest.begin(); it != mapTest.end(); ++it) {
		cout << it->first << " : " << it->second << endl;	//1 2 3
	}

	//函数对象运用于算法
	int a[] = {1, 2, 3, 4, 5};
	vector<int> v(a, a + 5);
	for_each(v.begin(), v.end(), PrintObj());	//传入匿名函数对象
	cout << endl;

	return 0;
}