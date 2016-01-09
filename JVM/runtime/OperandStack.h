#pragma once
#include "../utils/Array.h"
#include "../types/types.h"

class OperandStack : public Array<word>
{
	static const int DEFAULT_STACK_SIZE = 64;
public:
	OperandStack();
	OperandStack(size_t size, byte * address) : Array(size, address) {}
	OperandStack(size_t size);
	~OperandStack();

	void push(word value);
	void push2(doubleWord value);
	void pushReference(word value);

	const word & top() const;
	word pop();
	doubleWord pop2();
	word popReference();

	void clear();

	bool isEmpty() const;
	bool isFull() const;

	word & operator[] (size_t index);
	const word & operator[] (size_t index) const;
};

class StackOverflowException {};
class StackEmtpyException {};
