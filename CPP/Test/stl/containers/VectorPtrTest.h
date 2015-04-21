#ifndef _VECTOR_PTR_TEST
#define _VECTOR_PTR_TEST

#include <vector>
#include <memory>

template <typename T>
class VectorPtrTest : public std::vector<T*> {
public:
	~VectorPtrTest() {
		clear();
	}

	void clear() {
		typename std::vector<T*>::iterator it;
		for(it = std::vector<T*>::begin(); it != std::vector<T*>::end(); ++it)
			delete *it;			//释放存储指针的内存

		std::vector<T*>::clear();	//释放本身内存 erase(begin, end)
	}

	void push_back(T* const &val) {
		std::auto_ptr<T> ptr(val);			//用auto_ptr接管val所有权
		std::vector<T*>::push_back(val);	//operator new，可能分配内存失败
		ptr.release();						//分配成功，ptr释放所有权
	}

	void push_back(std::auto_ptr<T> &val) {
		std::vector<T*>::push_back(val.get());
		val.release();
	}
};

#endif