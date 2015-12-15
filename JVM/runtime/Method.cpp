#include "Method.h"



Method::Method()
{
}


Method::~Method()
{
	delete[] this->byteCode;
	this->byteCode = NULL;
}
