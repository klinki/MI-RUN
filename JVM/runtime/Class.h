#pragma once
#include <string>
#include "Method.h"
#include "AccessFlags.h"
class Class
{
public:
	enum Type
	{
		INTERFACE,
		CLASS 
	};

protected:
	std::string fullyQualifiedName;
	std::string parentFullyQualifiedName;
	Type type;
	// modifiers
	FLAG flags;
	
	ConstantPool constantPool;
	// Fields
	// static variables

	Method * methods;
	unsigned int countMethods;

	// class loader
	// class


public:
	Class(FLAG flag) : flags(flag) {};
	~Class();
};
