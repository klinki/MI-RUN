#pragma once
#include "Method.h"
#include "AccessFlags.h"
#include "../utils/Utf8String.h"
//#include "../classfile/ClassLoader.h"
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
	
	ConstantPool * constantPool;

	// This is used for object creation
	Field * fields;
	size_t countFields;

	Field * staticFields;
	size_t countStaticFields;

	Method * methods;
	size_t countMethods;

	Class * parentClass;

	// For bootstrap loader NULL
	Class * classLoader;

	Class * classMetaClass;

public:
	Class(FLAG flag) : flags(flag) {};
	~Class();
	//void setConstantPool(ConstantPool CP);
	//void setName(Utf8String name);
	size_t getCountFields() const;
	bool isFlagSet(FLAG flag) const;

	friend class ClassLoader;
};
