#pragma once
#include "OperandStack.h"
#include "Method.h"
#include "LocalVariablesArray.h"
#include "../gc/MemoryCell.h"
#include "../gc/VisitableInterface.h"

class Method;

class MethodFrame : VisitableInterface
{
visibility:
	ProgramCounter pc;
	size_t sp;
	Method* method;
	ConstantPool * constantPool;
	MethodFrame * parentFrame;
	MethodFrame * childFrame;

	LocalVariablesArray * localVariables; // array of local variables
	OperandStack * operandStack;
public:
	MethodFrame();
	MethodFrame(size_t stackSize, size_t localVariablesSize);
	MethodFrame(size_t stackSize, size_t localVariablesSize, MethodFrame * parent, ConstantPool * constantPool, Method * method, byte * address);
	~MethodFrame();

	static size_t getMemorySize();
	static size_t getMemorySize(size_t stackSize, size_t localVariblesSize);

	virtual void accept(ObjectVisitorInterface * visitor);
	virtual void accept(ObjectVisitorInterface & visitor);

	friend class ExecutionEngine;
	friend class Method;
};
