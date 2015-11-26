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

	T & operator[] (size_t index)
	{
		if (index >= this->size)
		{
			throw Exceptions::Runtime::ArrayIndexOutOfBoundsException();
		}

		return this->arrayData[index];
	}

	const T & operator[] (size_t index) const
	{
		if (index >= this->size)
		{
			throw Exceptions::Runtime::ArrayIndexOutOfBoundsException();
		}

		return this->arrayData[index];
	}

};
