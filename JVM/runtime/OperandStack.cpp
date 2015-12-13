#include "OperandStack.h"
#include <cstdlib>

OperandStack::OperandStack(): OperandStack(OperandStack::DEFAULT_STACK_SIZE) {}

OperandStack::OperandStack(size_t size): Array(size)
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

void OperandStack::push2(doubleWord value)
{
	this->push(value.words[1]); // High
	this->push(value.words[0]); // Low
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

doubleWord OperandStack::pop2()
{
	unsigned int low = this->pop();
	unsigned int high = this->pop();
	return doubleWord(high, low);
}

bool OperandStack::isEmpty() const
{
	return this->index == 0;
}

bool OperandStack::isFull() const
{
	return this->index >= this->allocatedSize;
}

word & OperandStack::operator[] (size_t index)
{
	if (index > this->index)
	{
		throw IndexOutOfBoundsException();
	}

	return this->allocatedArray[index];
}

const word & OperandStack::operator[] (size_t index) const
{
	if (index >= this->index)
	{
		throw IndexOutOfBoundsException();
	}

	return this->allocatedArray[index];
}
