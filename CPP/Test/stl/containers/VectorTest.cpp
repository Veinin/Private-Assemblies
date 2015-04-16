/**
template<
    class T,
    class Allocator = std::allocator<T>
> class vectorvector;
std::vector 是一种序列容器，是对大小可变数组封装。
与对应的静态数组相比，vector 所占的内存通常要更多（内存分配器allocator），因为它还分配了额外的内存以应对将来可能的扩张。
数组中的元素是连续存储的，所以除了能够通过迭代器访问外，还可以通过常规的指针偏移量访问元素。

效率：
随机访问 O(1)
插入元素 O(1)
删除元素 O(n) 为至vector尾部的线性距离 
*/

#include <vector>
#include <iostream>
using namespace std;

int main(void)
{
	vector<int> v;

   	v.push_back(1);
   	v.push_back(2);
   	cout << v.capacity() << endl;	//已分配内存空间，空间不足时，会自动分配双倍(G++)容量内存
   	cout << v.size() << endl;

   	vector<int> v2 = v;				//拷贝

   	vector<int> v3(10, 1);				//有10个元素，每个数都为1
   	cout << v3.size() << endl;
   	for(vector<int>::iterator it = v3.begin(); it != v3.end(); ++it) {
   		cout << *it << " ";
   	}

	return 0;
}


