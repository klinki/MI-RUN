#pragma once
#include "Object.h"
#include "../exceptions/RuntimeExceptions.h"
#include "../gc/interfaces/GarbageCollectableInterface.h"
#include "ObjectHeader.h"
#include "../utils/Utf8String.h"

template<class T>
class ArrayObject : public ObjectHeader
{
protected:
	size_t size;
	T * arrayData;

public:
	ArrayObject(size_t arraySize, T defaultValue, Class* objectClass, byte* address): ObjectHeader(objectClass)
	{
		this->size = arraySize;
		this->objectClass = objectClass;

		if (address == NULL)
		{
			address = (byte*)(&this->arrayData + sizeof(this->arrayData) / sizeof(int));
		}

		this->arrayData = new(address) T[arraySize];
		
		for (int i = 0; i < arraySize; i++)
		{
			this->arrayData[i] = defaultValue;
		}
	}

	ArrayObject(const ArrayObject & copy): ArrayObject(copy.size, 0, copy.objectClass, NULL)
	{
		memcpy(this->arrayData, copy.arrayData, copy.size * sizeof(T));
	}

	~ArrayObject()
	{
		// DO NOT DELETE DATA HERE!!
	}

	virtual void copyTo(byte* address)
	{
		new(address) ArrayObject<T>(*this);
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
	{
		visitor->visit(this);
	}

	void accept(ObjectVisitorInterface & visitor)
	{
		this->accept(&visitor);
	}

	virtual bool requiresFinalization()
	{
		return false;
	}

	virtual Method* getFinalizationMethod()
	{
		return NULL;
	}
};

#ifdef _MSC_VER
template <>
void ArrayObject<Object*>::accept(ObjectVisitorInterface * visitor)
{
	visitor->visit(this);

	for (int i = 0; i < this->size; i++)
	{
		visitor->visit((word)this->arrayData[i]);
	}
}

template <>
void ArrayObject<Object*>::accept(ObjectVisitorInterface & visitor)
{
	this->accept(&visitor);
}

template <>
bool ArrayObject<Object*>::requiresFinalization()
{
	return false;
}

template <>
Method* ArrayObject<Object*>::getFinalizationMethod()
{
	return this->objectClass->getMethod("finalize", "()V");
}

#endif
