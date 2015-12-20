#pragma once
#include "ObjectVisitorInterface.h"
class VisitableInterface
{
public:
	virtual ~VisitableInterface() {}
	virtual void accept(ObjectVisitorInterface * visitor) = 0;
	virtual void accept(ObjectVisitorInterface & visitor) = 0;
};
