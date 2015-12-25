#pragma once
#include "OperandStack.h"
#include "Method.h"
#include "LocalVariablesArray.h"
#include "../gc/interfaces/GarbageCollectableInterface.h"

class Method;

class MethodFrame : public GarbageCollectableInterface
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
	MethodFrame(Method * method, MethodFrame* parent = NULL);
	MethodFrame(size_t stackSize, size_t localVariablesSize, MethodFrame * parent, ConstantPool * constantPool, Method * method, byte * address);
	~MethodFrame();

	static size_t getMemorySize(size_t stackSize = 0, size_t localVariblesSize = 0);

	virtual void accept(ObjectVisitorInterface * visitor);
	virtual void accept(ObjectVisitorInterface & visitor);

	virtual bool requiresFinalization();

	friend class ExecutionEngine;
	friend class Method;
};
