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
	size_t fieldIndex;
	word value[2];
	const TypeTag type;

public:
	Field(FLAG flags, const Utf8String & name, const Utf8String & descriptor) : ClassMember(name, descriptor), type((TypeTag)descriptor.toAsciiString()[0])
	{
	}

	~Field() {}

	word getValue() const
	{
		return this->value[0];
	}

	doubleWord getValue2() const
	{
		return doubleWord((unsigned int)this->value[0], (unsigned int)this->value[1]);
	}

	friend class ClassLoader;
};
