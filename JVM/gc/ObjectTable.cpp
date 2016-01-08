#include "ObjectTable.h"

ObjectTable::ObjectTable(size_t size)
{
	this->insert((Object*)NULL); // this value is reserved
}

ObjectTable::~ObjectTable()
{
}

size_t ObjectTable::insert(void * obj)
{
	this->hashMap.emplace(index, obj);

	DEBUG_PRINT("Inserting object with address: %p to index: %d\n", obj, index);

	return index++;
}

size_t ObjectTable::insert(void* ptr, bool systemObject)
{
	return this->insert(ptr);
}

Object * ObjectTable::get(size_t index)
{
	return (Object*)this->hashMap.at(index);
}

void ObjectTable::updateAddress(size_t index, void* newAddress)
{
	this->hashMap[index] = newAddress;
}

void ObjectTable::remove(size_t index)
{
	this->hashMap.erase(index);
}
