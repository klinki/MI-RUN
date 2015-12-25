#include "Method.h"

Utf8String Method::getName()
{
	return this->name;
}


Method::~Method()
{
	delete[] this->byteCode;
	this->byteCode = NULL;
}
