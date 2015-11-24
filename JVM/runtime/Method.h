#pragma once
#include <string>
#include "ConstantPool.h"
#include "../types/types.h"
#include "ExceptionTable.h"
#include "../utils/Utf8String.h"
#include "../classfile/ClassLoader.h"
#include "../utils//Macros.h"

class Method
{
visibility:
	const Utf8String name;
	const Utf8String descriptor;

	Instruction* byteCode;
	unsigned int byteCodeLength;

	unsigned int operandStackSize;
	unsigned int localVariablesArraySize;

	ExceptionTable exceptionTable;
public:
	Method();
	~Method();

	const Instruction* getBytecode() const
	{
		return this->byteCode;
	}
	
	const unsigned int getByteCodeLength() const
	{
		return this->byteCodeLength;
	}

	friend class ClassLoader;
};
