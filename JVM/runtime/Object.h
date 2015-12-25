#pragma once
#include "Class.h"
#include "Field.h"
#include "LocalVariablesArray.h"
#include "../gc/interfaces/GarbageCollectableInterface.h"

class Object : public GarbageCollectableInterface
{
visibility:
	Class * objectClass;
	LocalVariablesArray fields;

public:
	Object(size_t fields, Class * objectClass, byte * address) : 
		objectClass(objectClass), fields(fields, address + sizeof(objectClass))
	{
	};
	
	Object(size_t fields, Class* objectClass) : 
		objectClass(objectClass), fields(fields) 
	{
	};

	Object()
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
		for (int i = 0; i < this->fields.index; i++)
		{
			visitor->visit(this->fields[i]);
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
