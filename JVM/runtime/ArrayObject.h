#pragma once
#include "Object.h"
#include "../exceptions/RuntimeExceptions.h"

template<class T>
class ArrayObject
{
protected:
	Class* objectClass;
	size_t size;
	T * arrayData;

public:
	ArrayObject(size_t arraySize, T defaultValue, Class* objectClass, byte* address)
	{
		this->size = arraySize;
		this->objectClass = objectClass;
		this->arrayData = new(&this->arrayData + sizeof(this->arrayData) / sizeof(int)) T[arraySize];
		
		for (int i = 0; i < arraySize; i++)
		{
			this->arrayData[i] = defaultValue;
		}
	}

	~ArrayObject()
	{
		// DO NOT DELETE DATA HERE!!
	}

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


	static size_t getMemorySize();
	static size_t getMemorySize(size_t fields)
	{
		return sizeof(ArrayObject<T>) + sizeof(T) * fields; // already included in size;
	}
};
