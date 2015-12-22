#pragma once
#include "../runtime/Object.h"
class ObjectTable : public Array<Object*>
{
visibility:
	size_t index;

	void resize();
public:
	ObjectTable(size_t size = 10);
	~ObjectTable();

	virtual size_t insert(Object* obj);
	virtual size_t insert(intptr_t ptr);
	virtual Object* get(size_t index);
};
