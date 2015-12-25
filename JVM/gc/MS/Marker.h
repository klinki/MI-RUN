#pragma once
#include "../interfaces/ObjectVisitorInterface.h"

class Marker : public ObjectVisitorInterface
{
protected:
	const size_t oneRoundLimit = 150;
public:
	Marker();
	~Marker();

	virtual void visit(MethodFrame* methodFrame) = 0;
	virtual void visit(Object* object) = 0;
	virtual void visit(size_t address) = 0;
	virtual void visit(word address)
	{
		this->visit(address);
	}
};
