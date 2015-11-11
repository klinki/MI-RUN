#include "OperandStack.h"
#include <cstdlib>

OperandStack::OperandStack(): OperandStack(DEFAULT_STACK_SIZE) {}

OperandStack::OperandStack(int size)
{
	this->allocatedSize = size;
	this->sp = 0;
	this->stackArray = new JavaType[this->allocatedSize];
}

OperandStack::~OperandStack()
{
	delete[] this->stackArray;
	this->stackArray = NULL;
}

void OperandStack::push(JavaType value)
{
	if (this->sp == this->allocatedSize)
	{
		throw StackOverflowException();
	}

	this->stackArray[this->sp++] = value;
}

JavaType OperandStack::pop()
{
	if (this->sp == 0)
	{
		throw StackEmtpyException();
	}

	JavaType & val = this->stackArray[this->sp - 1];
	this->sp--;
	return val;
}

bool OperandStack::isEmpty() const
{
	return this->sp == 0;
}

bool OperandStack::isFull() const
{
	return this->sp >= this->allocatedSize - 1;
}
