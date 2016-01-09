#pragma once
#include "../../types/types.h"
class Object;
class MethodFrame;
class ObjectHeader;

class ObjectVisitorInterface
{
public:
	virtual ~ObjectVisitorInterface() {};

	virtual void visit(MethodFrame* methodFrame) = 0;
	virtual void visit(ObjectHeader* header) = 0;
	virtual void visit(Object* object) = 0;
	virtual void visit(word address) = 0;
	virtual void visit(size_t address)
	{
		this->visit((word)address);
	}
};
