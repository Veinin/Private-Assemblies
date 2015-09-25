#include "Integer.h"

int main(void)
{
	Integer i1(5);
	i1.Display();
	Integer i2 = ++i1;
	i1.Display();
	i2.Display();

	Integer i3 = i1++;
	i1.Display();
	i3.Display();

	return 0;
}
