#pragma once
#include <cstdlib>
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
};
