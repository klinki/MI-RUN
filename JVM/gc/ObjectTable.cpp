#include "ObjectTable.h"

ObjectTable::ObjectTable(size_t size): objectArray(size)
{
	this->insert((Object*)-1); // this value is reserved
}

ObjectTable::~ObjectTable()
{
}

size_t ObjectTable::insert(void * obj)
{
	if (this->objectArray.index >= this->objectArray.allocatedSize)
	{
		this->objectArray.resize();
	}

	size_t index = this->objectArray.index++;
	this->objectArray.allocatedArray[index] = (Object*)obj;

	return index;
}

Object * ObjectTable::get(size_t index)
{
	return this->objectArray[index];
}
