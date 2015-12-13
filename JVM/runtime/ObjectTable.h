#pragma once
#include "Object.h"
class ObjectTable
{
protected:
	Array<Object*> objectArray;
public:
	ObjectTable(size_t size = 10);
	~ObjectTable();

	size_t insert(Object* obj);
	size_t insert(intptr_t ptr);
	Object* get(size_t index);
};
