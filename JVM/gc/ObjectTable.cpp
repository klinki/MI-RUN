#include "ObjectTable.h"

ObjectTable::ObjectTable(size_t size)
{
	this->insert((Object*)-1); // this value is reserved
}

ObjectTable::~ObjectTable()
{
}

size_t ObjectTable::insert(void * obj)
{
	size_t index = this->hashMap.size();
	this->hashMap.emplace(index, obj);

	return index;
}

Object * ObjectTable::get(size_t index)
{
	return (Object*)this->hashMap.at(index);
}
