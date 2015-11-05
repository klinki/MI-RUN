#pragma once
#include "types.h"
#include "GarbageCollector.h"

class OperandStack
{
	const int DEFAULT_STACK_SIZE = 64;
protected:
	TypeHeader* stackArray;
	unsigned int sp;
	unsigned int allocatedSize;
public:
	OperandStack();
	OperandStack(int size);
	~OperandStack();

	void push(TypeHeader);
	TypeHeader pop();
	bool isEmpty() const;
	bool isFull() const;

	friend class GarbageCollector;
};

class StackOverflowException {};
class StackEmtpyException {};
