#pragma once
#include "Object.h"
template<class T>
class ArrayObject : public Object
{
protected:
	unsigned int size;
	T * arrayData;

public:
	ArrayObject();
	~ArrayObject();

	unsigned int getSize() const { return this->size; }

	T & operator[] (int index)
	{
		if (index < 0 || index >= this->size)
		{
			throw Exceptions::Runtime::ArrayIndexOutOfBoundsException();
		}
	}

};
