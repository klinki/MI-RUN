#pragma once

#include "../types/ConversionFunctions.h"
#include "InstructionSet.h"
#include "../types/types.h"
#include "MethodFrame.h"
#include "Class.h"
#include "../exceptions/RuntimeExceptions.h"
#include "ArrayObject.h"

#define SINGLE_WORD_OPERATION(type, op) \
	type a = this->frame->stack.pop(); \
	type b = this->frame->stack.pop(); \
	this->frame->stack.push(a op b)

#define DOUBLE_OPERATION(op) \
 	double a = this->getDoubleFromStack(); \
	double b = this->getDoubleFromStack(); \
	this->pushDouble(a op b);


#define LONG_OPERATION(op) \
 	long long a = this->getLongFromStack(); \
	long long b = this->getLongFromStack(); \
	this->pushLong(a op b)


class ExecutionEngine
{
protected:
	MethodFrame* frame;
public:
	ExecutionEngine();
	~ExecutionEngine();

	int execute(MethodFrame * frame); // Instruction instructions[], unsigned int length);

	inline void singleArrayStore()
	{
		ArrayObject<word>* ref = (ArrayObject<word>*)this->frame->operandStack.pop();
		int index = this->frame->operandStack.pop();
		word value = this->frame->operandStack.pop();

		if (ref == NULL)
		{
			throw Exceptions::Runtime::NullPointerException();
		}
		
		ref->operator[](index) = value;
	}

	inline void doubleArrayStore()
	{
		ArrayObject<double>* ref = (ArrayObject<double>*)this->frame->operandStack.pop();
		int index = this->frame->operandStack.pop();
		double value = this->getDoubleFromStack();

		if (ref == NULL)
		{
			throw Exceptions::Runtime::NullPointerException();
		}

		ref->operator[](index) = value;
	}

	inline void longArrayStore()
	{
		ArrayObject<long long>* ref = (ArrayObject<long long>*)this->frame->operandStack.pop();
		int index = this->frame->operandStack.pop();
		long long value = this->getLongFromStack();

		if (ref == NULL)
		{
			throw Exceptions::Runtime::NullPointerException();
		}

		ref->operator[](index) = value;
	}

	inline void aload(unsigned char index)
	{
		word ptr = this->frame->localVariables[index];
		this->frame->operandStack.push(ptr);
	}

	inline void astore(unsigned char index)
	{}
	
	inline void iload(unsigned char index)
	{
		int val = (int)this->frame->localVariables[index];
		this->frame->operandStack.push(JavaInt(val));
	}

	inline void istore(unsigned char index)
	{
		int val = (int)this->frame->operandStack.pop();
		this->frame->localVariables[index] = val;
	}

	inline void fload(unsigned char index)
	{
		float val = (float)this->frame->localVariables[index];
		this->frame->operandStack.push(JavaFloat(val));
	}

	inline void fstore(unsigned char index)
	{
		float val = (float)this->frame->operandStack.pop();
		this->frame->localVariables[index] = index;
	}

	inline void wload()
	{
		unsigned char index = this->frame->method->getBytecode()[this->frame->pc++];
		this->wload(index);
	}

	inline void wload(unsigned char index)
	{
		word val = this->frame->localVariables[index];
		this->frame->operandStack.push(val);
	}


	inline void lload(unsigned char index)
	{
		word high = this->frame->localVariables[index];
		word low = this->frame->localVariables[index + 1];

		this->frame->operandStack.push(high);
		this->frame->operandStack.push(low);
	}

	inline void lstore(unsigned char index)
	{

	}


	inline void dload(unsigned char index)
	{
		word high = this->frame->localVariables[index];
		word low = this->frame->localVariables[index + 1];

		this->frame->operandStack.push(high);
		this->frame->operandStack.push(low);
	}

	inline void dstore(unsigned char index)
	{

	}




	inline unsigned short getShort()
	{
		const Instruction * instructions = this->frame->method->getBytecode();
		unsigned char LOW = instructions[this->frame->pc++];
		unsigned char HIGH = instructions[this->frame->pc++];
		unsigned short index = shortFromStack(HIGH, LOW);
		return index;
	}
	
	inline unsigned int getInt()
	{
		const Instruction * instructions = this->frame->method->getBytecode();
		unsigned char HIGH_HIGH = instructions[this->frame->pc++];
		unsigned char HIGH_LOW = instructions[this->frame->pc++];
		unsigned char LOW_HIGH = instructions[this->frame->pc++];
		unsigned char LOW_LOW = instructions[this->frame->pc++];

		int value = intFromBytes(HIGH_HIGH, HIGH_LOW, LOW_HIGH, LOW_LOW);
		return value;
	}

	inline long long getLongFromStack()
	{
		unsigned int a_low = this->frame->operandStack.pop();
		unsigned int a_high = this->frame->operandStack.pop();
		return longFromStack(a_high, a_low);
	}

	inline double getDoubleFromStack()
	{
		unsigned int a_low = this->frame->operandStack.pop();
		unsigned int a_high = this->frame->operandStack.pop();
		return doubleFromStack(a_high, a_low);
	}

	inline void pushLong(long long value)
	{
		
	}

	inline void pushDouble(double value)
	{

	}

	inline void jumpIfEq(Instruction currentInstruction, int value)
	{
		unsigned short index = this->getShort();

		if ((value == 0 && (currentInstruction == IFEQ || currentInstruction == IFGE || currentInstruction == IFLE))
			||
			(currentInstruction == IFNE || (value > 0 && (currentInstruction == IFGT || currentInstruction == IFGE)) ||
				(value < 0 && (currentInstruction == IFLE || currentInstruction == IFLT))))
		{
			// JUMP
		}
	}

	inline void singleAdd()
	{

	}

	inline void doubleAdd()
	{

	}


	template<class T>
	inline void fdcmp(T a, T b, Instruction currentInstruction)
	{

		int res = 0;

		if (a > b)
		{
			res = 1;
		}
		else if (a == b)
		{
			res = 0;
		}
		else if (a < b)
		{
			res = -1;
		}
		else if ((a == NAN || b == NAN))
		{
			res = (currentInstruction == DCMPG || currentInstruction == FCMPG) ? 1 : -1;
		}

		this->frame->operandStack.push(res);
	}

};
