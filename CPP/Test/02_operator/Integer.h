#ifndef _INTEGER_H_
#define _INTEGER_H_

class Integer
{
public:
	Integer(int n);
	void Display() const;

	Integer& operator++();
	//friend Integer& operator++(Integer& i);

	Integer operator++(int i);
	//friend Integer operator++(int i);

private:
	int n_;
};

#endif
