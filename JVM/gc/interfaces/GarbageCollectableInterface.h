#pragma once
#include "FinalizableInterface.h"
#include "VisitableInterface.h"

class GarbageCollectableInterface : public VisitableInterface, public FinalizableInterface
{
public:
	virtual void repairAfterGC()
	{

	};

	virtual void copyTo(byte* memory) = 0;
};
