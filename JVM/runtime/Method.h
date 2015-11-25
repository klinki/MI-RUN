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
	size_t byteCodeLength;

	size_t operandStackSize;
	size_t localVariablesArraySize;

	ExceptionTable exceptionTable;
public:
	Method();
	~Method();

	const Instruction* getBytecode() const
	{
		return this->byteCode;
	}
	
	const size_t getByteCodeLength() const
	{
		return this->byteCodeLength;
	}

	friend class ClassLoader;
};
