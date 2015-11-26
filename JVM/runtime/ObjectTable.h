#pragma once
#include "Object.h"
class ObjectTable
{
protected:
	Array<Object*> objectArray;
public:
	ObjectTable();
	~ObjectTable();

	size_t insert(Object* obj);
	Object* get(size_t index);
};
