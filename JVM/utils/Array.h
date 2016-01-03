#pragma once
#include <cstdlib>
#include "Macros.h"
#include "../types/types.h"

class IndexOutOfBoundsException {};


template <class T> 
class Array
{
	static const int DEFAULT_ARRAY_SIZE = 64;
visibility:
	size_t allocatedSize;
	size_t index;
	bool preallocated = false;
	T * allocatedArray;

public:
	Array() : Array(DEFAULT_ARRAY_SIZE) {};
	
	Array(size_t size)
	{
		this->allocatedArray = new T[size];
		this->allocatedSize = size;
		this->index = 0;

		this->initialize();
	}

	Array(size_t size, byte * address)
	{
		this->preallocated = true;
		this->index = 0;
		this->allocatedSize = size;
		this->allocatedArray = (T*) (&this->allocatedArray + 1);//address;

		this->initialize();
	}

	~Array()
	{
		if (!this->preallocated)
		{
			delete[] this->allocatedArray;
		}

		this->allocatedArray = NULL;
	}

	void initialize()
	{
		memset(this->allocatedArray, 0, sizeof(*this->allocatedArray) * this->allocatedSize);
	}

	void resize()
	{
		int oldSize = this->allocatedSize;
		this->allocatedSize *= 2;

		T * oldArray = this->allocatedArray;
		this->allocatedArray = new T[this->allocatedSize];

		for (int i = 0; i < oldSize; i++)
		{
			this->allocatedArray[i] = oldArray[i];
		}

		delete[] oldArray;
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
};

