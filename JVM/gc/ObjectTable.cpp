#include "ObjectTable.h"

ObjectTable::ObjectTable(size_t size): Array<Object*>()
{
	this->allocatedArray = new Object*[size];
	this->allocatedSize = size;

	this->insert((Object*)-1); // this value is reserved
}

ObjectTable::~ObjectTable()
{
	delete[] this->allocatedArray;
}

void ObjectTable::resize()
{
	int oldSize = this->allocatedSize;
	this->allocatedSize *= 2;

	Object ** oldArray = this->allocatedArray;
	this->allocatedArray = new Object*[this->allocatedSize];

	for (int i = 0; i < oldSize; i++)
	{
		this->allocatedArray[i] = oldArray[i];
	}

	delete[] oldArray;
}

size_t ObjectTable::insert(Object * obj)
{
	if (this->index >= this->allocatedSize)
	{
		this->resize();
	}

	size_t index = this->index++;
	this->allocatedArray[index] = obj;

	return index;
}

size_t ObjectTable::insert(intptr_t ptr)
{
	return this->insert((Object*)ptr);
}

Object * ObjectTable::get(size_t index)
{
	return this->allocatedArray[index];
}
