#pragma once
#include "../types/types.h"
#include "../gc/GarbageCollector.h"

class OperandStack
{
	const int DEFAULT_STACK_SIZE = 64;
protected:
	JavaType* stackArray;
	unsigned int sp;
	unsigned int allocatedSize;
public:
	OperandStack();
	OperandStack(int size);
	~OperandStack();

	void push(JavaType);
	JavaType pop();
	bool isEmpty() const;
	bool isFull() const;

	friend class GarbageCollector;
};

class StackOverflowException {};
class StackEmtpyException {};
