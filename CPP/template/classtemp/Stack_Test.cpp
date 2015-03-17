#include <iostream>
#include "Stack.h"

using namespace std;

int main(void)
{
	Stack<int> s(5);
	s.Push(1);
	s.Push(2);
	s.Push(3);

	while(!s.IsEmpty()) 
	{
		cout << s.Top() << endl;
		s.Pop();
	}

	return 0;
}
