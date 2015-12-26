#pragma once
#include "ConstantPool.h"
#include "../gc/Heap.h"
#include "MethodArea.h"
#include "ExecutionEngine.h"
#include "../utils/Macros.h"

class Runtime
{
visibility:
//	ConstantPool constantPool; // TODO: Uncomment when ready and compileable!
	HeapInterface * heap;
	ClassMap * classTable;
	ExecutionEngine * executionEngine;

public:
	Runtime();
	~Runtime();
};
