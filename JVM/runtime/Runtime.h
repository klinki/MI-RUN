#pragma once
#include "ConstantPool.h"
#include "../gc/Heap.h"
#include "FrameStack.h"
#include "MethodArea.h"
#include "ExecutionEngine.h"

class Runtime
{
protected:
//	ConstantPool constantPool; // TODO: Uncomment when ready and compileable!
	Heap heap;
	FrameStack frameStack;
	ClassMap classTable;
	ExecutionEngine executionEngine;

public:
	Runtime();
	~Runtime();
};
