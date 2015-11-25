#pragma once
#include <cstdlib>
#include "Macros.h"
#include "../types/types.h"

template <class T> 
class Array
{
	const int DEFAULT_ARRAY_SIZE = 64;
visibility:
	T* allocatedArray;
	size_t allocatedSize;
	size_t index;
public:
	Array() : Array(DEFAULT_ARRAY_SIZE) {};
	
	Array(size_t size)
	{
		this->allocatedArray = new T[size];
		this->allocatedSize = size;
		this->index = 0;
	}

	~Array()
	{
		delete[] this->allocatedArray;
		this->allocatedArray = NULL;
	}

	word & operator[] (int index)
	{
		if (index < 0 || index >= this->allocatedSize)
		{
			throw IndexOutOfBoundsException();
		}

		return this->allocatedArray[index];
	}

	const word & operator[] (int index) const
	{
		if (index < 0 || index >= this->allocatedSize)
		{
			throw IndexOutOfBoundsException();
		}

		return this->allocatedArray[index];
	}
};

class IndexOutOfBoundsException {};
