#pragma once
#include <cstring>
#include "Class.h"
#include "Field.h"
#include "LocalVariablesArray.h"
#include "ObjectHeader.h"
#include "../gc/interfaces/GarbageCollectableInterface.h"

class Object : public ObjectHeader
{
visibility:
	LocalVariablesArray * fields = NULL;

public:
	Object(size_t fields, Class * objectClass, byte * address): 
		ObjectHeader(objectClass)
	{
		if (fields > 0)
		{
			if (address == NULL)
			{
				address = (byte*)(&this->fields + 1);
			}

			this->fields = new(address) LocalVariablesArray(fields, NULL);
		}
	};
	
	Object(size_t fields, Class* objectClass) : 
		ObjectHeader(objectClass)
	{
		this->fields = new LocalVariablesArray(fields);
	};

	Object(const Object & source): Object(0, source.objectClass, NULL)
	{
		if (source.fields != NULL)
		{
			byte* address = (byte*)(&this->fields + 1);
			this->fields = new(address) LocalVariablesArray(source.fields->allocatedSize, NULL);

			memcpy(this->fields->allocatedArray, source.fields->allocatedArray, source.fields->allocatedSize);
		}
	}

	Object(): ObjectHeader(NULL)
	{
	};

	~Object()
	{
	};
	
	virtual void copyTo(byte* address)
	{
		new(address) Object(*this);
	}

	static size_t getMemorySize(size_t fields = 0)
	{
		return sizeof(Object)
			+ LocalVariablesArray::getMemorySize(fields);
	}

	virtual void accept(ObjectVisitorInterface * visitor)
	{
		if (this->fields == NULL)
		{
			return;
		}

		for (int i = 0; i < this->fields->index; i++)
		{
			visitor->visit(this->fields->get(i));
		}
	}

	virtual void accept(ObjectVisitorInterface & visitor)
	{
		this->accept(&visitor);
	}

	virtual bool requiresFinalization()
	{
		return true;
	}

	virtual Method* getFinalizationMethod()
	{
		return this->objectClass->getMethod("finalize", "()V");
	}

};
