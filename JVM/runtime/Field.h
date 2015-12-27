#pragma once
#include <string>
#include "AccessFlags.h"
//#include "../classfile/ClassLoader.h"
#include "../utils/Utf8String.h"
#include "ClassMember.h"
#include "../utils/Macros.h"
#include "../types/types.h"

class Field : public ClassMember
{
visibility:
	word value[2];
	TypeTag type;

public:
	Field(FLAG flags, const Utf8String & name, const Utf8String & descriptor) : ClassMember(name, descriptor)
	{
		this->type = (TypeTag)descriptor.toAsciiString()[0];
	}

	~Field() {}

	word getValue() const
	{
		return this->value[0];
	}

	doubleWord getValue2() const
	{
		return doubleWord(this->value[0], this->value[1]);
	}

	friend class ClassLoader;
};
