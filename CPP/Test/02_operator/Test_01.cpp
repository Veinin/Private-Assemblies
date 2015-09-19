#include "Complex.h"

int main(void)
{
	Complex c1(3, 5);
	Complex c2(5, 6);

	Complex c3 = c1 + c2; // c3 = c1.operator+(c3)
	c1.Display();
	c2.Display();
	c3.Display();

	return 0;
}
