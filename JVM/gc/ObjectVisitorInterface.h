#pragma once
class Object;


class ObjectVisitorInterface
{
public:
	virtual ~ObjectVisitorInterface() {};

	virtual void visit(MethodFrame* methodFrame) = 0;
	virtual void visit(Object* object) = 0;
	virtual void visit(size_t address) = 0;
	virtual void visit(word address) 
	{
		this->visit(address);
	}
};
