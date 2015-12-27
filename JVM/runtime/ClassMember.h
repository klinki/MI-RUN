#pragma once
#include <string>
#include "AccessFlags.h"
#include "../utils/Utf8String.h"
#include "../utils/Macros.h"

class ClassMember
{
visibility:
	FLAG flags;
	Utf8String name;
	Utf8String descriptor;

public:
	ClassMember() {};
	ClassMember(const Utf8String & name, const Utf8String & descriptor) : name(name), descriptor(descriptor) {}
	virtual ~ClassMember() {}

	bool isStatic() const
	{
		return (this->flags & (int)FieldAccessFlags::STATIC) == (int)FieldAccessFlags::STATIC;
	}

	friend class ClassLoader;
};
