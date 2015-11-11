#pragma once
#include "OperandStack.h"
#include "Method.h"
#include "LocalVariablesArray.h"

class MethodFrame
{
protected:
	OperandStack stack;
	ProgramCounter pc;
	unsigned int sp;
	Method* method;
	
	LocalVariablesArray ar; // array of local variables
	OperandStack operandStack;
	ConstantPool * constantPool;

public:
	MethodFrame();
	~MethodFrame();

	friend class ExecutionEngine;
};
