#pragma once
#include "../utils/Array.h"
#include "../types/types.h"
#include "../gc/GarbageCollector.h"

class OperandStack : public Array<word>
{
	static const int DEFAULT_STACK_SIZE = 64;
public:
	OperandStack();
	OperandStack(size_t size, byte * address);
	OperandStack(size_t size);
	~OperandStack();

	void push(word value);
	void push(word high, word low);

	word pop();

	bool isEmpty() const;
	bool isFull() const;

	word & operator[] (int index);
	const word & operator[] (int index) const;

	friend class GarbageCollector;
};

class StackOverflowException {};
class StackEmtpyException {};
