#pragma once
#include "Class.h"
#include "Field.h"
#include "LocalVariablesArray.h"

class Object
{
visibility:
	Class * objectClass;
	LocalVariablesArray fields;

public:
	Object(size_t fields, Class * objectClass, byte * address);
	Object(size_t fields, Class* objectClass);
	Object();
	~Object();


	static size_t getMemorySize();
	static size_t getMemorySize(size_t fields);
};
