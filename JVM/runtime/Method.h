#pragma once
#include <string>
#include "ConstantPool.h"
#include "../types/types.h"
#include "ExceptionTable.h"
#include "../utils/Utf8String.h"
//#include "../classfile/ClassLoader.h"
#include "../utils/Macros.h"
#include "../natives/Declarations.h"
#include "AccessFlags.h"

class Method
{
visibility:
	const FLAG flags;
	Utf8String name;
	Utf8String descriptor;

	Instruction* byteCode;
	size_t byteCodeLength;

	size_t operandStackSize;
	size_t localVariablesArraySize;

	ExceptionTable exceptionTable;

	NativeMethodPtr nativeMethod;

public:
	Method(FLAG f) : flags(f) {};
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
