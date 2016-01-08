#pragma once
#include <set>
#include "../interfaces/ObjectVisitorInterface.h"
#include "../ObjectTable.h"

class Marker : public ObjectVisitorInterface
{
protected:
	const size_t oneRoundLimit = 150;
	std::set<size_t> visitedObjects;
	ObjectTable * objectTable;

public:
	Marker();
	Marker(ObjectTable * objectTable);
	~Marker();

	virtual void mark(word root);

	virtual void visit(MethodFrame* methodFrame);
	virtual void visit(ObjectHeader* header);
	virtual void visit(Object* object);
	virtual void visit(word address);
};
