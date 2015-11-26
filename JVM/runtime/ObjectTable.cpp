#include "ObjectTable.h"



ObjectTable::ObjectTable()
{
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

	size_t index = this->objectArray.index;
	this->objectArray.allocatedArray[index] = obj;

	return index;
}

Object * ObjectTable::get(size_t index)
{
	return this->objectArray[index];
}
