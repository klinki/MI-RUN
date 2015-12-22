#pragma once
#include "Object.h"
#include "../exceptions/RuntimeExceptions.h"
#include "../gc/VisitableInterface.h"

template<class T>
class ArrayObject : public VisitableInterface
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


	void accept(ObjectVisitorInterface * visitor)
	{}

	void accept(ObjectVisitorInterface & visitor)
	{}
};


template <>
void ArrayObject<Object*>::accept(ObjectVisitorInterface * visitor)
{
	for (int i = 0; i < this->size; i++)
	{
		visitor->visit(this->arrayData[i]);
	}
}

template <>
void ArrayObject<Object*>::accept(ObjectVisitorInterface & visitor)
{
	this->accept(&visitor);
}
