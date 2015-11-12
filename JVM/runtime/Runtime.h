#pragma once
#include "ConstantPool.h"
#include "../gc/Heap.h"
#include "FrameStack.h"
#include "MethodArea.h"
#include "ExecutionEngine.h"

class Runtime
{
protected:
//	ConstantPool constantPool;
	Heap heap;
	FrameStack frameStack;
	MethodArea methodArea;
	ExecutionEngine executionEngine;

public:
	Runtime();
	~Runtime();
};
