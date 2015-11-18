#pragma once
#include "Class.h"
#include "Field.h"

class Object
{
protected:
	// Does it need fields? Or would just data be enough?
	Field * fields;
	unsigned int countFields;
	Class * objectClass;
public:
	Object();
	~Object();
};
