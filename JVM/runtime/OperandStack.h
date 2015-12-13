#pragma once
#include "../utils/Array.h"
#include "../types/types.h"
#include "../gc/GarbageCollector.h"

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

	word pop();
	doubleWord pop2();

	bool isEmpty() const;
	bool isFull() const;

	word & operator[] (size_t index);
	const word & operator[] (size_t index) const;

	friend class GarbageCollector;
};

class StackOverflowException {};
class StackEmtpyException {};
