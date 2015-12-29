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

Utf8String::Utf8String(const char * string, bool preallocated): Utf8String(string, strlen(string), preallocated)
{
}

Utf8String::Utf8String(const std::string & str): Utf8String(str.c_str(), str.length()) {}

Utf8String::Utf8String(const char * string, size_t length, bool preallocated)
{
	if (!preallocated)
	{
		this->data = new char[length + 1];
	}
	else
	{
		this->data = (char*)(&this->data + 1);
	}

	memcpy(this->data, string, length);
	this->data[length] = '\0';
	this->dataLength = length + 1;
	this->stringLength = length;
	this->hash = this->calculateHash();
}

Utf8String::Utf8String(const char* data, size_t length): Utf8String(data, length, false)
{
}

Utf8String::Utf8String(const unsigned char* data, size_t length): Utf8String((char*) data, length)
{
}

Utf8String::Utf8String(const Utf8String & copy)
{
	this->data = NULL;
	this->operator=(copy);
}

Utf8String::~Utf8String()
{
	delete[] this->data;
}

size_t Utf8String::calculateHash()
{
	// FNV-1a hash
	// http://www.isthe.com/chongo/tech/comp/fnv/#FNV-1a 

	size_t hash = 2166136261;

	for (size_t i = 0; i < this->dataLength; i++)
	{
		hash = (hash * 16777619) ^ this->data[i];
	}

	return hash;
}

const char* Utf8String::toAsciiString() const
{
	return this->data;
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
	delete[] this->data;
	this->data = new char[u.dataLength];
	memcpy(this->data, u.data, u.dataLength);
	this->dataLength = u.dataLength;
	this->stringLength = u.stringLength;
	this->hash = u.hash;

	return *this;
}
