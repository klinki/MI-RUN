#pragma once
#include "Method.h"
#include "AccessFlags.h"
#include "../utils/Utf8String.h"
#include "Field.h"
#include "MethodArea.h"
#include "LocalVariablesArray.h"
#include "ClassMemberMap.h"

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
	FLAG flags;
	
	ConstantPool * constantPool;

	// This is used for object creation
	Field ** fields;
	size_t countFields;

	Field * staticFields;
	size_t countStaticFields;

	MethodArea methodArea;

	size_t countMethods;

	Class * parentClass;
	Class * classLoader; 	// For bootstrap loader NULL

	Class * classMetaClass;
	
	LocalVariablesArray * staticVariables;
	ClassMemberMap staticVariablesMap;

	bool isNative;

public:
	Class(FLAG flag) : flags(flag) {};
	~Class();
	size_t getCountFields() const;
	bool isFlagSet(FLAG flag) const;

	Method* getMethod(const Utf8String & methodName, const Utf8String & descriptor);

	friend class ClassLoader;
};
