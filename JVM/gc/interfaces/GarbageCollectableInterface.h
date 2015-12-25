#pragma once
#include "FinalizableInterface.h"
#include "VisitableInterface.h"

class GarbageCollectableInterface : public VisitableInterface, public FinalizableInterface
{
	
};
