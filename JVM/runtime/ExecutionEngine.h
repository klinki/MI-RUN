#pragma once
#include "types.h"
#include "InstructionSet.h"

class ExecutionEngine
{
public:
	ExecutionEngine();
	~ExecutionEngine();

	int execute(Instruction instructions[], unsigned int length);
};

