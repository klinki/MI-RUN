#pragma once
#include "OperandStack.h"
#include "Method.h"
#include "LocalVariablesArray.h"

class MethodFrame
{
visibility:
	OperandStack stack;
	ProgramCounter pc;
	unsigned int sp;
	Method* method;
	
	LocalVariablesArray localVariables; // array of local variables
	OperandStack operandStack;
	ConstantPool * constantPool;

public:
	MethodFrame();
	MethodFrame(int stackSize, int localVariablesSize);
	~MethodFrame();

	friend class ExecutionEngine;
};
