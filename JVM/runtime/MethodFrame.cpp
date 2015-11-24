#include "MethodFrame.h"



MethodFrame::MethodFrame()
{
}

MethodFrame::MethodFrame(int stackSize, int localVariablesSize): operandStack(stackSize), localVariables(localVariablesSize)
{
}

MethodFrame::~MethodFrame()
{
}
