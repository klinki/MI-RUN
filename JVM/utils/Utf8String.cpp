#include "Utf8String.h"
using namespace std;

Utf8String::Utf8String()
{
	this->data = NULL;
	this->dataLength = 0;
	this->stringLength = 0;
}

Utf8String::Utf8String(const char* data, int length)
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
