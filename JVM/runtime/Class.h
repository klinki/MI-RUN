#pragma once
#include "Method.h"
#include "AccessFlags.h"
#include "../utils/Utf8String.h"
#include "Field.h"
#include "MethodArea.h"
#include "LocalVariablesArray.h"

class Class
{
public:
	enum class Type
	{
		INTERFACE,
		CLASS 
	};

visibility:
	Utf8String fullyQualifiedName;
	Type type;
	// modifiers
	FLAG flags;
	
	ConstantPool * constantPool;

	// This is used for object creation
	Field ** fields;
	size_t countFields;

	Field * staticFields;
	size_t countStaticFields;

	MethodArea methodArea;
//	Method * methods;
	size_t countMethods;

	Class * parentClass;

	// For bootstrap loader NULL
	Class * classLoader;

	Class * classMetaClass;
	
	LocalVariablesArray * staticVariables;


public:
	Class(FLAG flag) : flags(flag) {};
	~Class();
	//void setConstantPool(ConstantPool CP);
	//void setName(Utf8String name);
	size_t getCountFields() const;
	bool isFlagSet(FLAG flag) const;

	Method* getMethod(const Utf8String & methodName, const Utf8String & descriptor);

	friend class ClassLoader;
};
