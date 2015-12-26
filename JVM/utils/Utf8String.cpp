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

Utf8String::Utf8String(const std::string & str): Utf8String(str.c_str(), str.length()) {}

Utf8String::Utf8String(const char* data, size_t length)
{
	this->data = new unsigned char[length + 1];
	memcpy(this->data, data, length);
	this->data[length] = '\0';
	this->dataLength = length + 1;
	this->stringLength = length;

//	std::hash<std::string> hash;
	this->hash = this->calculateHash();
}

Utf8String::Utf8String(const unsigned char* data, size_t length): Utf8String((char*) data, length)
{
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
	this->data = new unsigned char[u.dataLength];
	memcpy(this->data, u.data, u.dataLength);
	this->dataLength = u.dataLength;
	this->stringLength = u.stringLength;
	this->hash = u.hash;

	return *this;
}


