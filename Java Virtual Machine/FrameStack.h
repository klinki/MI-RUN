#pragma once
#include "types.h"

class FrameStack
{
protected:
	ProgramCounter PC;
public:
	FrameStack();
	~FrameStack();
};

