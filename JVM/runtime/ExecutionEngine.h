#pragma once
#include "../types/types.h"
#include "InstructionSet.h"
#include "MethodFrame.h"

class ExecutionEngine
{
protected:
	MethodFrame* frame;
public:
	ExecutionEngine();
	~ExecutionEngine();

	int execute(Instruction instructions[], unsigned int length);
};
