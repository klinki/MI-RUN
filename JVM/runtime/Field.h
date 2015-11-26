#pragma once
#include <string>
#include "AccessFlags.h"
//#include "../classfile/ClassLoader.h"
#include "../utils/Utf8String.h"

class Field
{
protected:
	const FLAG flags;
	const Utf8String name;
	const Utf8String descriptor;

	// attributes - constant value 

public:
	Field(FLAG f) : flags(f) {};
	~Field();

	friend class ClassLoader;
};
