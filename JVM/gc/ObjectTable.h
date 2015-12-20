#pragma once
#include "../runtime/Object.h"
class ObjectTable
{
protected:
	Array<Object*> objectArray;
public:
	ObjectTable(size_t size = 10);
	~ObjectTable();

	virtual size_t insert(Object* obj);
	virtual size_t insert(intptr_t ptr);
	virtual Object* get(size_t index);
};
