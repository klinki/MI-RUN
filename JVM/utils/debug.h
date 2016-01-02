#pragma once
#include "../types/types.h"

class OperandStack;
class LocalVariablesArray;
class MethodFrame;

void printOperandStack(OperandStack* stack);
void printLocalVariables(MethodFrame* frame);
void printValue(word value);
void printValue(doubleWord value, TypeTag type);

const char** getNamedInstructions();
