/**
智能指针


思想：
栈区（stack）— 由编译器自动分配释放 ，存放函数的参数值，局部变量的值等。
堆区（heap） — 由程序员分配释放， 若程序员不释放，程序结束时可能由OS回收 。

将堆对象生存周期用栈对象来管理，
当new一个堆对象的时候，立刻用智能指针（栈对象）来接管
具体做法是在构造函数进行初始化，在析构函数中调用delete来释放堆对象。
由于智能指针是一个堆对象，它的作用于结束的时候，自动调用了析构函数，从而调用了delete释放堆对象

 boost智能指针类型：
 scoped_ptr<T> 作用域结束的时候自动释放，与auto_ptr不同，其所有权不能转移，但可以交换
 scoped_array<T> 与scoped_ptr相似，用来处理指针
 shared_ptr<T> 内部为何一个引用计数来判断此指针是不是需要被释放，线程安全
 shared_array<T> 与shared_ptr相似，用来处理指针
 intrusive_ptr<T> 也维护一个引用计数，比shared_ptr性能更好，但要求T提供计数器
 weak_ptr<T> 弱指针，不控制对象生命周期，但知道对象是否还活着
*/

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

using namespace std;

class A{
public:
	A() {
		cout << "A()..." << endl;
	}

	~A() {
		cout << "~A()" << endl;
	}
};

int main(void) {
	cout << "Enter main ..." << endl;
	{
		boost::scoped_ptr<A> p(new A);	//结束自动调用析构函数释放
		// boost::scoped_ptr<A> p2 = p;	//error，不可被引用
	}
	cout << "Exiting main ..." << endl;

	cout << "-------------------" << endl;

	cout << "Enter main ..." << endl;
	{
		boost::shared_ptr<A> p(new A);
		cout << p1.use_count() << endl;	//1个引用计数
		boost::shared_ptr<A> p2 = p1;
		cout << p2.use_count() << endl;	//2个引用计数
		p1.reset();
		cout << p2.use_count() << endl;	//p1断开，剩余1个引用计数
		p2.reset();						//引用计数变为0，自动释放
		//ps： 如不调用reset也可以自动释放，栈对象p、p1释放的时候引用计数也会减1
	}
	cout << "Exiting main ..." << endl;

	return 0;
}