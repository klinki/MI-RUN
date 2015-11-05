#pragma once
#include "ConstantPool.h"
#include "Heap.h"
#include "FrameStack.h"
#include "MethodArea.h"

class Runtime
{
protected:
//	ConstantPool constantPool;
	Heap heap;
	FrameStack frameStack;
	MethodArea methodArea;

public:
	Runtime();
	~Runtime();
};
