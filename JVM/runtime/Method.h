#pragma once
#include <string>
#include "ConstantPool.h"
#include "../types/types.h"
#include "ExceptionTable.h"

class Method
{
protected:
	const std::string name;
	const std::string descriptor;

	Instruction byteCode[1];
	unsigned int byteCodeLength;

	unsigned int operandStackSize;
	unsigned int localVariablesArraySize;

	ExceptionTable exceptionTable;
public:
	Method();
	~Method();
};
