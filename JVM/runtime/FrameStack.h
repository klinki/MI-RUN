#pragma once
#include "../types/types.h"

class FrameStack
{
protected:
	ProgramCounter PC;
public:
	FrameStack();
	~FrameStack();
};

