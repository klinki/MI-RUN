#pragma once
#include <map>
#include "../runtime/Object.h"
#include "../utils/HashMap.h"

class ObjectTable
{
protected:
	std::unordered_map<int, void*> hashMap;
	Array<Object*> objectArray;
public:
	ObjectTable(size_t size = 10);
	~ObjectTable();

	virtual size_t insert(void * ptr);
	virtual Object* get(size_t index);
};
