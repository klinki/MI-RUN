#include <cstring>
#include "Utf8String.h"
using namespace std;

Utf8String::Utf8String()
{
	this->data = NULL;
	this->dataLength = 0;
	this->stringLength = 0;
}

Utf8String::Utf8String(const char * string): Utf8String(string, strlen(string))
{
}

Utf8String::Utf8String(const char* data, size_t length)
{
	this->data = new unsigned char[length + 1];
	memcpy(this->data, data, length);
	this->dataLength = length + 1;
	this->stringLength = length;
}

Utf8String::Utf8String(const unsigned char* data, size_t length): Utf8String((char*) data, length)
{
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

Utf8String& Utf8String::operator=(const Utf8String & u)
{
	
	delete[] data;
	this->data = u.data;
	this->dataLength = u.dataLength;
	return *this;
}

