#pragma once

#include "../types/ConversionFunctions.h"
#include "InstructionSet.h"
#include "../types/types.h"
#include "MethodFrame.h"
#include "Class.h"
#include "../exceptions/RuntimeExceptions.h"
#include "ArrayObject.h"
#include "MethodArea.h"
#include "ClassMap.h"
#include "ObjectTable.h"
#include "../gc/Heap.h"

#define SINGLE_WORD_OPERATION(type, op) \
	type b = this->frame->operandStack->pop(); \
	type a = this->frame->operandStack->pop(); \
	this->frame->operandStack->push(a op b)

#define DOUBLE_OPERATION(op) \
 	double a = this->frame->operandStack->pop2(); \
	double b = this->frame->operandStack->pop2(); \
	this->frame->operandStack->push2((double)(a op b));


#define LONG_OPERATION(op) \
 	long long a = this->frame->operandStack->pop2(); \
	long long b = this->frame->operandStack->pop2(); \
	this->frame->operandStack->push2((long long)(a op b));


class ExecutionEngine
{
visibility:
	MethodFrame* frame;
	MethodArea* methodArea;
	ClassMap* classMap;
	ObjectTable* objectTable;
	Heap* heap;

	struct {
		size_t constantPoolIndex;
		size_t cpClassIndex;
		size_t cpMethodIndex;
		Class* classPtr;
		Method* methodPtr;
	} inlineCache;

public:
	ExecutionEngine();
	~ExecutionEngine();

	int execute(MethodFrame * frame); // Instruction instructions[], unsigned int length);

	inline void singleArrayStore()
	{
		ArrayObject<word>* ref = (ArrayObject<word>*)this->frame->operandStack->pop();
		int index = this->frame->operandStack->pop();
		word value = this->frame->operandStack->pop();

		if (ref == NULL)
		{
			throw Exceptions::Runtime::NullPointerException();
		}
		
		ref->operator[](index) = value;
	}

	inline void doubleArrayStore()
	{
		ArrayObject<double>* ref = (ArrayObject<double>*)this->frame->operandStack->pop();
		int index = this->frame->operandStack->pop();
		double value = this->frame->operandStack->pop2();

		if (ref == NULL)
		{
			throw Exceptions::Runtime::NullPointerException();
		}

		ref->operator[](index) = value;
	}

	inline void longArrayStore()
	{
		ArrayObject<long long>* ref = (ArrayObject<long long>*)this->frame->operandStack->pop();
		int index = this->frame->operandStack->pop();
		long long value = this->frame->operandStack->pop2();

		if (ref == NULL)
		{
			throw Exceptions::Runtime::NullPointerException();
		}

		ref->operator[](index) = value;
	}

	inline void singleWordLoad(size_t index)
	{
		word ptr = (*this->frame->localVariables)[index];
		this->frame->operandStack->push(ptr);
	}

	inline void singleWordStore(size_t index)
	{
		word val = this->frame->operandStack->pop();
		(*this->frame->localVariables)[index] = val;
	}

	inline void wload()
	{
		unsigned char index = this->frame->method->getBytecode()[this->frame->pc++];
		this->wload(index);
	}

	inline void wload(size_t index)
	{
		word val = (*this->frame->localVariables)[index];
		this->frame->operandStack->push(val);
	}


	inline void lload(size_t index)
	{
		word high = (*this->frame->localVariables)[index];
		word low = (*this->frame->localVariables)[index + 1];

		this->frame->operandStack->push(high);
		this->frame->operandStack->push(low);
	}

	inline void lstore(size_t index)
	{
		word low = this->frame->operandStack->pop();
		word high = this->frame->operandStack->pop();

		(*this->frame->localVariables)[index] = high;
		(*this->frame->localVariables)[index + 1] = low;
	}


	inline void dload(size_t index)
	{
		word high = (*this->frame->localVariables)[index];
		word low = (*this->frame->localVariables)[index + 1];

		this->frame->operandStack->push(high);
		this->frame->operandStack->push(low);
	}

	inline void dstore(size_t index)
	{
		word low = this->frame->operandStack->pop();
		word high = this->frame->operandStack->pop();

		 (*this->frame->localVariables)[index] = high;
		 (*this->frame->localVariables)[index + 1] = low;
	}

	inline unsigned short getShort()
	{
		const Instruction * instructions = this->frame->method->getBytecode();
		unsigned char HIGH = instructions[this->frame->pc++];
		unsigned char LOW = instructions[this->frame->pc++];
		unsigned short value = shortFromStack(HIGH, LOW);
		return value;
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

	inline void jumpIfEq(Instruction currentInstruction, int value)
	{
		unsigned short offset = this->getShort();

		if ( (value == 0 && (currentInstruction == IFEQ || currentInstruction == IFGE || currentInstruction == IFLE) ) ||
			 (value != 0 && currentInstruction == IFNE) || 
			 (value > 0 && (currentInstruction == IFGT || currentInstruction == IFGE) ) ||
			 (value < 0 && (currentInstruction == IFLE || currentInstruction == IFLT) ) )
		{
			this->jumpWithOffset(offset);
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

		this->frame->operandStack->push(res);
	}

	inline void jumpWithOffset(int offset)
	{
		this->frame->pc += offset - 1;
	}

	inline void pushFromConstantPool(int index)
	{
		/*
		int or float, or a reference to a string literal, or a symbolic reference to a class, method type, or method handle
		*/

		ConstantPoolItem * item = this->frame->constantPool->get(index);
		word value;

		switch (item->tag)
		{
		case CONSTANT_Float:
			value = item->floatInfo.value;
			this->frame->operandStack->push(value);
			break;
		case CONSTANT_Integer:
			value = item->integerInfo.value;
			this->frame->operandStack->push(value);
			break;
		case CONSTANT_Class:
			// TODO: Resolve class name, find class object
			break;
		case CONSTANT_MethodType:

			this->frame->operandStack->push(value);
			break;
		case CONSTANT_MethodHandle:
			this->frame->operandStack->push(value);
			break;

			// LDC_W
		case CONSTANT_Long:
			{
				word high = item->longInfo.high_bytes;
				word low = item->longInfo.low_bytes;

				this->frame->operandStack->push(high);
				this->frame->operandStack->push(low);
			}
			break;
		case CONSTANT_Double:
			{
				word high = item->doubleInfo.high_bytes;
				word low = item->doubleInfo.low_bytes;

				this->frame->operandStack->push(high);
				this->frame->operandStack->push(low);
			}
			break;
		}
	}

	inline void iinc(size_t index, word value)
	{
		(*this->frame->localVariables)[index] += value;
	}
};
