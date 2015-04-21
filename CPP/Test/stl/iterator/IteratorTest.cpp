/**
共有五种迭代器：
InputIterator ：只读，从序列中读取数据
OutputIterator ：只写，向序列中写入数据
ForwardIterator ：读写，既是输入迭代器又是输出迭代器，并且可以对序列进行单向的遍历
BidirectionalIterator ：读写，与前向迭代器相似，但是在两个方向上都可以对数据遍历
RandomAccessIterator ：也是双向迭代器，但能够在序列中的任意两个位置之间进行跳转

迭代器的分类的依据并不是迭代器的类型，而是迭代器所支持的操作。换句话说，某个类型只要支持相应的操作，就可以作为迭代器使用。
五种迭代器中有四种可以按层级组织，上层分类（如 RandomAccessIterator）支持下层分类（如 InputIterator）的功能。如果迭代
器满足这些分类的其中之一，而且同时满足 OutputIterator 的要求，那么就称之为可变迭代器，同时支持输入和输出。非可变迭代器又称常量迭代器。
*/

#include <iostream>
#include <vector>
using namespace std;

int main(void) {
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	vector<int>::iterator it;	//iterator 基于 const_iterator
	for(it = v.begin(); it != v.end(); ++it) {
		cout << *it << ' ';
	}
	cout << endl;

	vector<int>::reverse_iterator ri;				//reverse_iterator 基于 iterator
	for(ri = v.rbegin(); ri != v.rend(); ++ri) {	//rbegin指向 iterator.end    rend指向iterator.begin
		cout << *ri << ' ';							//--*ri
	}
	cout << endl;

	return 0;
}