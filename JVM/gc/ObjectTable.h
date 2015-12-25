#pragma once
#include <unordered_map>

class Object;

class ObjectTable
{
protected:
	std::unordered_map<int, void*> hashMap;

public:
	ObjectTable(size_t size = 10);
	~ObjectTable();

	virtual size_t insert(void * ptr);
	virtual Object* get(size_t index);
};
