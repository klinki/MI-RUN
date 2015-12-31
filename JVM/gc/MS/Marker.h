#pragma once
#include "../interfaces/ObjectVisitorInterface.h"

class Marker : public ObjectVisitorInterface
{
	class Sweeper : public ObjectVisitorInterface
	{
		virtual void visit(MethodFrame* methodFrame);
		virtual void visit(ObjectHeader* header);
		virtual void visit(Object* object);
		virtual void visit(word address);
	};

protected:
	const size_t oneRoundLimit = 150;
public:
	Marker();
	~Marker();

	virtual void visit(MethodFrame* methodFrame);
	virtual void visit(ObjectHeader* header);
	virtual void visit(Object* object);
	virtual void visit(word address);
};
