#pragma once
#include "Object.h"
template<class T>
class ArrayObject : public Object
{
protected:
	size_t size;
	T * arrayData;

public:
	ArrayObject();
	~ArrayObject();

	size_t getSize() const { return this->size; }

	T & operator[] (int index)
	{
		if (index < 0 || index >= this->size)
		{
			throw Exceptions::Runtime::ArrayIndexOutOfBoundsException();
		}

		return this->arrayData[index];
	}

	const T & operator[] (int index) const
	{
		if (index < 0 || index >= this->size)
		{
			throw Exceptions::Runtime::ArrayIndexOutOfBoundsException();
		}

		return this->arrayData[index];
	}

};
