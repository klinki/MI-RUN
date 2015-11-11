#pragma once
#include "Method.h"
#include "AccessFlags.h"
#include "../utils/Utf8String.h"
#include "../classfile/ClassLoader.h"
#include "Field.h"

class Class
{
public:
	enum Type
	{
		INTERFACE,
		CLASS 
	};

protected:
	Utf8String fullyQualifiedName;
	Utf8String parentFullyQualifiedName;
	Type type;
	// modifiers
	FLAG flags;
	
	ConstantPool constantPool;
	Field * fields;
	Field * staticFields;

	// Fields
	// static variables

	Method * methods;
	unsigned int countMethods;

	Class * classLoader;
	Class * classMetaClass;

public:
	Class(FLAG flag) : flags(flag) {};
	~Class();

	friend class ClassLoader;
};
