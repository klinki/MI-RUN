#pragma once
#include "Class.h"
#include "Field.h"
#include "LocalVariablesArray.h"
#include "ObjectHeader.h"
#include "../gc/interfaces/GarbageCollectableInterface.h"

class Object : public ObjectHeader, public GarbageCollectableInterface
{
visibility:
	LocalVariablesArray * fields;

public:
	Object(size_t fields, Class * objectClass, byte * address): 
		ObjectHeader(objectClass)
	{
		if (fields > 0)
		{
			if (address == NULL)
			{
				address = (byte*)(this->fields + 1);
			}

			this->fields = new(address) LocalVariablesArray(fields, NULL);
		}
	};
	
	Object(size_t fields, Class* objectClass) : 
		ObjectHeader(objectClass)
	{
		this->fields = new LocalVariablesArray(fields);
	};

	Object(): ObjectHeader(NULL)
	{
	};

	~Object()
	{
	};
	
	static size_t getMemorySize(size_t fields = 0)
	{
		return sizeof(Object) 
			+ LocalVariablesArray::getMemorySize(fields) 
			- sizeof(LocalVariablesArray); // already included in size;
	}

	virtual void accept(ObjectVisitorInterface * visitor)
	{
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
