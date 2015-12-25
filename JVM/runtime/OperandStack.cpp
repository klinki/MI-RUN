#include "OperandStack.h"
#include <cstdlib>

OperandStack::OperandStack(): array()
{
	this->index = 0;
}

OperandStack::OperandStack(size_t size, bool debugging)
{
	this->index = 0;
	this->array = new Array<word>(size, debugging);
}

OperandStack::OperandStack(size_t size)
{
	this->index = 0;
	this->array = new (&this->array + 1) Array<word>(size);
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

	this->array->allocatedArray[this->index++] = value;
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

	return this->array->allocatedArray[--this->index];
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
	return this->index >= this->array->allocatedSize;
}

word & OperandStack::operator[] (size_t index)
{
	if (index > this->index)
	{
		throw IndexOutOfBoundsException();
	}

	return this->array->allocatedArray[index];
}

const word & OperandStack::operator[] (size_t index) const
{
	if (index >= this->index)
	{
		throw IndexOutOfBoundsException();
	}

	return this->array->allocatedArray[index];
}
