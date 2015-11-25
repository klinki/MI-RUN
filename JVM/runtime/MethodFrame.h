#pragma once
#include "OperandStack.h"
#include "Method.h"
#include "LocalVariablesArray.h"

class MethodFrame
{
visibility:
	ProgramCounter pc;
	size_t sp;
	Method* method;
	
	LocalVariablesArray localVariables; // array of local variables
	OperandStack operandStack;
	ConstantPool * constantPool;

public:
	MethodFrame();
	MethodFrame(size_t stackSize, size_t localVariablesSize);
	~MethodFrame();

	friend class ExecutionEngine;
};
