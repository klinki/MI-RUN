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
visibility:
	Utf8String fullyQualifiedName;
	FLAG flags;
	
	ConstantPool * constantPool;

	size_t countNonStaticFields; // This is used for object creation

	MethodArea methodArea;
	ClassMemberMap fieldsMap;

	Class * parentClass;

	Class ** implementedInterfaces;
	size_t countInterfaces;

	Class * classLoader; 	// For bootstrap loader NULL
	
	LocalVariablesArray * staticVariablesValues;

	void addField(Field* field);

public:
	Class(FLAG flag) : flags(flag) {};
	~Class();
	size_t getCountFields() const;
	bool isFlagSet(FLAG flag) const;

	Method* getMethod(const Utf8String & methodName, const Utf8String & descriptor);
	Field* getField(const Utf8String & name, const Utf8String & descriptor);

	bool isClass() const
	{
		return !this->isInterface();
	}

	bool isInterface() const
	{
		return (this->flags & (int)ClassAccessFlags::INTERFACE) == (int)ClassAccessFlags::INTERFACE;
	}

	bool isAbstract() const
	{
		return (this->flags & (int)ClassAccessFlags::ABSTRACT) == (int)ClassAccessFlags::ABSTRACT;
	}

	bool isSubclassOf(Class* parent);
	bool implementsInterface(Class* parentInterface);

	friend class ClassLoader;
};
