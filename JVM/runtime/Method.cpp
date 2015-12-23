#include "Method.h"




Method::~Method()
{
	delete[] this->byteCode;
	this->byteCode = NULL;
}
