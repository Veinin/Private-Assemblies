#ifndef _STRING_H_
#define _STRING_H_
#include <iostream>
using namespace std;

class String
{
public:
	String();
	explicit String(const char* str);
	String(const String& other);
	~String(void);

	String& operator=(const String& other);
	String& operator=(const char *str);

	bool operator!() const;

	char& operator[](unsigned int index);
	const char& operator[](unsigned int index) const;

	friend String operator+(const String& s1, const String& s2);	
	String& operator+=(const String& other);

	friend ostream& operator<<(ostream& os, const String& str);
	friend istream& operator>>(istream& is, String& str);

	void Display() const;

private:
	char* AllocAndCpy(const char* str);
	char *str_;
};

#endif
