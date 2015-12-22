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
	const int attributesSize;
	// attributes - constant value 
	int * attributes; //references to const table


public:
	//Field(FLAG f) : flags(f) {};
	Field(FLAG f, Utf8String n, Utf8String d, int a) : flags(f), name(n), descriptor(d), attributesSize(a) { attributes = new int[a]; };
	void setAttribute(int pos, int ref);
	~Field();

	friend class ClassLoader;
};
