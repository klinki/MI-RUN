#pragma once
#include "../types/types.h"
const char* namedInstructions[];


class OperandStack;
class LocalVariablesArray;
class MethodFrame;

void printOperandStack(OperandStack* stack);
void printLocalVariables(MethodFrame* frame);
void printValue(word value);
void printValue(doubleWord value, TypeTag type);

#ifdef _DEBUG
	#define PRINT_STACK(stack) printOperandStack(stack);
	#define PRINT_LOCAL_VARIABLES(frame) printLocalVariables(frame);
#else
	#define PRINT_STACK(stack)
#endif
