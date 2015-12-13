#include "Utf8String.h"
using namespace std;

Utf8String::Utf8String()
{
	this->data = NULL;
	this->dataLength = 0;
	this->stringLength = 0;
}

Utf8String::Utf8String(const char* data, size_t length)
{
	this->data = new unsigned char[length];
	this->dataLength = length;
}


Utf8String::~Utf8String()
{
	delete[] this->data;
}

string Utf8String::toAsciiString()
{
	return "";
}

bool Utf8String::equals(const Utf8String & b) const
{
	if (this->dataLength != b.dataLength)
	{
		return false;
	}

	for (size_t i = 0; i < this->dataLength; i++)
	{
		if (this->data[i] != b.data[i])
		{
			return false;
		}
	}

	return true;
}

inline size_t std::hash<Utf8String>::operator()(const Utf8String & x) const
{
	std::hash<std::string> hash;
	return hash(x.value);
}

inline bool operator==(const Utf8String & a, const Utf8String & b)
{
	return a.hash == b.hash;
}

inline bool operator!=(const Utf8String & a, const Utf8String & b)
{
	return !(a == b);
}
