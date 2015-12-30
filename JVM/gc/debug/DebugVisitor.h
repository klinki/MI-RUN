#pragma once
#include "../interfaces/ObjectVisitorInterface.h"
#include "../ObjectTable.h"
#include <iostream>

class DebugVisitor : public ObjectVisitorInterface
{
	ObjectTable * table;
	size_t level = 0;
public:
	DebugVisitor(ObjectTable *table)
	{
		this->table = table;
	}

	virtual void visit(MethodFrame* methodFrame)
	{
		std::cerr << std::string(level * 2, '-');
		std::cerr << "Inside methodFrame " << methodFrame << std::endl;
		level++;
		methodFrame->accept(this);
		level--;

		if (methodFrame->parentFrame != NULL)
		{
			methodFrame->parentFrame->accept(this);
		}
	}

	virtual void visit(Object* object)
	{
		std::cerr << std::string(level * 2, '-');
		std::cerr << "Inside object " << object << " " << object->objectClass->fullyQualifiedName.toAsciiString() << std::endl;
		level++;
		object->accept(this);
		level--;
	}


	virtual void visit(ObjectHeader* object)
	{
		std::cerr << std::string(level * 2, '-');
		std::cerr << "Inside object header " << object << " " << object->objectClass->fullyQualifiedName.toAsciiString() << std::endl;
	}

	virtual void visit(void* pointer)
	{
		VisitableInterface* visitable = (VisitableInterface*)pointer;
		ObjectHeader * header = (ObjectHeader*)visitable;
		visitable->accept(this);
	}

	virtual void visit(size_t address)
	{
		try
		{
			if (isReferenceAddress(address))
			{
				int unmasked = getReferenceAddress(address);

				std::cerr << std::string(level * 2, '-');
				std::cerr << "Inside address " << unmasked << "   ";
				void* object = this->table->get(unmasked);
				this->visit((void*)object);
			}
		}
		catch (...) 
		{

		}

	}

	virtual void visit(word address)
	{
		this->visit((size_t)address);
	}
};
