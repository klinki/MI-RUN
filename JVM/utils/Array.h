#pragma once
#include <cstdlib>
#include "Macros.h"
#include "../types/types.h"

template <class T> 
class Array
{
visibility:
	size_t allocatedSize;
	T * allocatedArray;

public:
	Array()
	{
		this->allocatedArray = NULL;
		this->allocatedSize = 0;
	};
	
	Array(size_t size)
	{
		this->allocatedSize = size;
		this->allocatedArray = (T*) (&this->allocatedArray + 1);//address;
	}

	~Array()
	{
		this->allocatedArray = NULL;
	}

	T & operator[] (size_t index)
	{
		if (index >= this->allocatedSize)
		{
			throw IndexOutOfBoundsException();
		}

		return this->allocatedArray[index];
	}

	const T & operator[] (size_t index) const
	{
		if (index >= this->allocatedSize)
		{
			throw IndexOutOfBoundsException();
		}

		return this->allocatedArray[index];
	}

	static size_t getMemorySize(size_t items)
	{
		return sizeof(Array<T>) + items * sizeof(T);
	}



#ifdef _DEBUG
	Array(size_t size, bool debugging)
	{
		this->allocatedSize = size;
		this->allocatedArray = new T[size];
	}
#endif
};

class IndexOutOfBoundsException {};
