#include "OperandStack.h"
#include <cstdlib>

OperandStack::OperandStack(): OperandStack(DEFAULT_STACK_SIZE) {}

OperandStack::OperandStack(int size): Array(size)
{
}

OperandStack::~OperandStack()
{
}

void OperandStack::push(word value)
{
	if (this->isFull())
	{
		throw StackOverflowException();
	}

	this->allocatedArray[this->index++] = value;
}

word OperandStack::pop()
{
	if (this->isEmpty())
	{
		throw StackEmtpyException();
	}

	return this->allocatedArray[this->index--];
	/*
	JavaType & val = this->allocatedArray[this->index- 1];
	this->sp--;
	return val;
	*/
}

bool OperandStack::isEmpty() const
{
	return this->index == 0;
}

bool OperandStack::isFull() const
{
	return this->index >= this->allocatedSize - 1;
}
