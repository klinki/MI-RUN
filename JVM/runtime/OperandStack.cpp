#include "OperandStack.h"
#include <cstdlib>

OperandStack::OperandStack(): OperandStack(OperandStack::DEFAULT_STACK_SIZE) {}

OperandStack::OperandStack(size_t size): Array(size)
{
}

OperandStack::OperandStack(size_t size, byte * address) : Array(size, address)
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

	return this->allocatedArray[--this->index];
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
	return this->index >= this->allocatedSize;
}

word & OperandStack::operator[] (int index)
{
	if (index < 0 || index > this->index)
	{
		throw IndexOutOfBoundsException();
	}

	return this->allocatedArray[index];
}

const word & OperandStack::operator[] (int index) const
{
	if (index < 0 || index >= this->index)
	{
		throw IndexOutOfBoundsException();
	}

	return this->allocatedArray[index];
}
