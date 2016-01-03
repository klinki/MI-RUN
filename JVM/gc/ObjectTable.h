#pragma once
#include <map>
#include "../runtime/Object.h"
#include "../utils/HashMap.h"

class ObjectTable
{
visibility:
	size_t index = 0;
	std::unordered_map<int, void*> hashMap;
public:
	ObjectTable(size_t size = 10);
	~ObjectTable();

	virtual size_t insert(void * ptr);
	virtual size_t insert(void* ptr, bool systemObject);
	virtual Object* get(size_t index);
	virtual void updateAddress(size_t index, void* newAddress);
};
