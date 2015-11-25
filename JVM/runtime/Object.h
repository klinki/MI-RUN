#pragma once
#include "Class.h"
#include "Field.h"
#include "LocalVariablesArray.h"

class Object
{
protected:
	Class * objectClass;
	LocalVariablesArray fields;



public:
	Object();
	~Object();
};
