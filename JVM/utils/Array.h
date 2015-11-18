#pragma once
#include <cstdlib>
#include "../types/types.h"

template <class T> 
class Array
{
	const int DEFAULT_ARRAY_SIZE = 64;
protected:
	T* allocatedArray;
	unsigned int allocatedSize;
	unsigned int index;
public:
	Array() : Array(DEFAULT_ARRAY_SIZE) {};
	
	Array(int size)
	{
		this->allocatedArray = new T[size];
	}

	~Array()
	{
		delete[] this->allocatedArray;
		this->allocatedArray = NULL;
	}

	word & operator[] (int index)
	{
		if (index < 0 || index >= this->index)
		{
			throw IndexOutOfBoundsException();
		}

		return this->allocatedArray[index];
	}

	const word & operator[] (int index) const
	{
		if (index < 0 || index >= this->index)
		{
			throw IndexOutOfBoundsException();
		}

		return this->allocatedArray[index];
	}
};

class IndexOutOfBoundsException {};
