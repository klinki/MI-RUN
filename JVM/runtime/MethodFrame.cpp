#include "MethodFrame.h"



MethodFrame::MethodFrame()
{
}

MethodFrame::MethodFrame(size_t stackSize, size_t localVariablesSize): operandStack(stackSize), localVariables(localVariablesSize)
{
}

MethodFrame::~MethodFrame()
{
}
