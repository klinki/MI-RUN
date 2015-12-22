#include "ObjectTable.h"

ObjectTable::ObjectTable(size_t size): objectArray(size)
{
	this->insert((Object*)-1); // this value is reserved
}

ObjectTable::~ObjectTable()
{
}

size_t ObjectTable::insert(Object * obj)
{
	if (this->objectArray.index >= this->objectArray.allocatedSize)
	{
		this->objectArray.resize();
	}

	size_t index = this->objectArray.index++;
	this->objectArray.allocatedArray[index] = obj;

	return index;
}

size_t ObjectTable::insert(intptr_t ptr)
{
	return this->insert((Object*)ptr);
}

Object * ObjectTable::get(size_t index)
{
	return this->objectArray[index];
}
