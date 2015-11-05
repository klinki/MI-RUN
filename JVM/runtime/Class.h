#pragma once
#include "Method.h"
class Class
{
protected:
	Method * methods;
	unsigned int countMethods;
	// constant table

public:
	Class();
	~Class();
};
