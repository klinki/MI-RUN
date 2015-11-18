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
	Type type;
	// modifiers
	FLAG flags;
	
	ConstantPool constantPool;

	// This is used for object creation
	Field * fields;
	unsigned int countFields;

	Field * staticFields;
	unsigned int countStaticFields;

	Method * methods;
	unsigned int countMethods;

	Class * parentClass;

	// For bootstrap loader NULL
	Class * classLoader;

	Class * classMetaClass;

public:
	Class(FLAG flag) : flags(flag) {};
	~Class();

	unsigned int getCountFields() const;
	bool isFlagSet(FLAG flag) const;

	friend class ClassLoader;
};
