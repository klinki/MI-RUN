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
	const TypeTag type;

public:
	Field(FLAG flags, const Utf8String & name, const Utf8String & descriptor) : ClassMember(name, descriptor), type((TypeTag)descriptor.toAsciiString()[0])
	{
            this->flags = flags;
            this->fieldIndex = -1; // uninitialized
	}

	~Field() {}

	static size_t getMemorySize()
	{
		return sizeof(Field);
	}

	friend class ClassLoader;
};
