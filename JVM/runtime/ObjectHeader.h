#pragma once
#include "../gc/interfaces/GarbageCollectableInterface.h"
#include "Class.h"

class ObjectHeader : GarbageCollectableInterface
{
visibility:
	Class * objectClass;

public:
	ObjectHeader(Class* classPtr)
	{
		this->objectClass = classPtr;
	}
};
