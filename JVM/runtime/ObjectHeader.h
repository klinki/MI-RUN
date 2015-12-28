#pragma once
#include "Class.h"

class ObjectHeader
{
visibility:
	Class * objectClass;

public:
	ObjectHeader(Class* classPtr)
	{
		this->objectClass = classPtr;
	}
};
