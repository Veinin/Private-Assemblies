#include "String.h"
#include <string.h>

String::String()
{
	str_ = new char[0];
}

String::String(const char *str)
{
	str_ = AllocAndCpy(str);
}

String::String(const String& other)
{
	str_ = AllocAndCpy(other.str_);
}

String::~String()
{
	delete [] str_;
}

String& String::operator=(const String& other)
{
	if (&other == this)
		return *this;

	delete [] str_;
	str_ = AllocAndCpy(other.str_);
	return *this;
}

String& String::operator=(const char* str)
{
	delete [] str_;
	str_ = AllocAndCpy(str);
	return *this;
}

bool String::operator!() const
{
	return strlen(str_) != 0;
}

char& String::operator[](unsigned int index)
{
	return const_cast<char&>(static_cast<const String&>(*this)[index]);
}

const char& String::operator[](unsigned int index) const
{
	return str_[index];
}

String operator+(const String& s1, const String& s2)
{
	String str = s1;
	str += s2;
	return str;
}

String& String::operator+=(const String& other)
{
	int len = strlen(str_) + strlen(other.str_) + 1;
	char *newstr = new char[len];
	memset(newstr, 0, len);
	strcpy(newstr, str_);
	strcat(newstr, other.str_);

	delete [] str_;
	
	str_ = newstr;
	return *this;
}

ostream& operator<<(ostream& os, const String& str)
{
	os << str.str_;
	return os;
}

istream& operator>>(istream& is, String& str)
{
	char tmp[1024];
	is >> tmp;
	str = tmp;
	return is;
}

void String::Display() const
{
	cout << str_ << endl;
}

char* String::AllocAndCpy(const char *str)
{
	int len = strlen(str) + 1;
	char *newstr = new char[len];
	memset(newstr, 0, len);
	strcpy(newstr, str);

	return newstr;
}
