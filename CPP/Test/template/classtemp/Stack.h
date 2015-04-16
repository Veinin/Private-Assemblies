#ifndef _STACK_H_
#define _STACK_H_

#include <exception>

using namespace std;

template <typename T>
class Stack
{
public:
	explicit Stack(int maxSize);
	~Stack();

	void Push(const T& elem);
	void Pop();
	T& Top();
	const T& Top() const;
	bool IsFull() const;
	bool IsEmpty() const;
private:
	T* elems_;
	int maxSize_;
	int top_;
};

template <typename T>
Stack<T>::Stack(int maxSize) : maxSize_(maxSize), top_(-1)
{
	elems_ = new int[maxSize_];
}

template <typename T>
Stack<T>::~Stack()
{
	delete[] elems_;
}

template <typename T>
void Stack<T>::Push(const T& elem)
{
	if(IsFull()) 
		throw out_of_range("stack is full.");

	elems_[++top_] = elem;
}

template <typename T>
void Stack<T>::Pop()
{
	if(IsEmpty())
		throw out_of_range("stack is empty.");

	--top_;
}

template <typename T>
T& Stack<T>::Top()
{
	if(IsEmpty())
		throw out_of_range("stack is empty.");

	return elems_[top_];
}

template <typename T>
const T& Stack<T>::Top() const
{
	if(IsEmpty())
		throw out_of_range("stack is empty.");

	return elems_[top_];
}

template <typename T>
bool Stack<T>::IsFull() const
{
	return top_ + 1 >= maxSize_;
}

template <typename T>
bool Stack<T>::IsEmpty() const
{
	return top_ + 1 <= 0;
}

#endif
