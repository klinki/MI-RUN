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
#include "../gc/ObjectTable.h"
#include "../gc/Heap.h"

#define SINGLE_WORD_OPERATION(type, op) \
	type b = this->getCurrentMethodFrame()->operandStack->pop(); \
	type a = this->getCurrentMethodFrame()->operandStack->pop(); \
	this->getCurrentMethodFrame()->operandStack->push(a op b);

#define DOUBLE_WORD_OPERATION(type, op) \
	type b = this->getCurrentMethodFrame()->operandStack->pop2(); \
	type a = this->getCurrentMethodFrame()->operandStack->pop2(); \
	this->getCurrentMethodFrame()->operandStack->push2((type)(a op b));


class ExecutionEngine
{
visibility:
	MethodFrame* frame;
	ClassMap* classMap;
	ObjectTable* objectTable;
	HeapInterface* heap;

	OperandStack * callStack;

	struct {
		size_t constantPoolIndex;
		size_t cpClassIndex;
		size_t cpMethodIndex;
		Class* classPtr;
		Method* methodPtr;
	} inlineCache;

	MethodFrame* getCurrentMethodFrame()
	{
		size_t index = this->callStack->top();
		return (MethodFrame*)this->objectTable->get(index);
	}

public:
	ExecutionEngine();
	~ExecutionEngine();

	int execute(MethodFrame * frame); // Instruction instructions[], unsigned int length);

	template <class T>
	inline void arrayStore()
	{
		word value = this->getCurrentMethodFrame()->operandStack->pop();
		int index = this->getCurrentMethodFrame()->operandStack->pop();
		int ref = this->getCurrentMethodFrame()->operandStack->pop();

		if (ref == NULL)
		{
			throw Exceptions::Runtime::NullPointerException();
		}

		ArrayObject<T>* ptr = (ArrayObject<T>*)this->objectTable->get(ref);

		if (ptr == NULL)
		{
			throw Exceptions::Runtime::NullPointerException();
		}
		
		ptr->operator[](index) = (T)value;
	}

	template <class T>
	inline void arrayStore2()
	{
		doubleWord value = this->getCurrentMethodFrame()->operandStack->pop2();
		int index = this->getCurrentMethodFrame()->operandStack->pop();
		int ref = this->getCurrentMethodFrame()->operandStack->pop();

		if (ref == NULL)
		{
			throw Exceptions::Runtime::NullPointerException();
		}

		ArrayObject<T>* ptr = (ArrayObject<T>*)this->objectTable->get(ref);

		if (ptr == NULL)
		{
			throw Exceptions::Runtime::NullPointerException();
		}
		ptr->operator[](index) = value;
	}

	template <class T>
	inline void arrayLoad()
	{
		int index = this->getCurrentMethodFrame()->operandStack->pop();
		int ref = this->getCurrentMethodFrame()->operandStack->pop();

		if (ref == NULL)
		{
			throw Exceptions::Runtime::NullPointerException();
		}

		ArrayObject<T>* ptr = (ArrayObject<T>*)this->objectTable->get(ref);

		if (ptr == NULL)
		{
			throw Exceptions::Runtime::NullPointerException();
		}

		this->getCurrentMethodFrame()->operandStack->push(ptr->operator[](index));
	}

	template <class T>
	inline void arrayLoad2()
	{
		int index = this->getCurrentMethodFrame()->operandStack->pop();
		int ref = this->getCurrentMethodFrame()->operandStack->pop();

		if (ref == NULL)
		{
			throw Exceptions::Runtime::NullPointerException();
		}

		ArrayObject<T>* ptr = (ArrayObject<T>*)this->objectTable->get(ref);

		if (ptr == NULL)
		{
			throw Exceptions::Runtime::NullPointerException();
		}

		this->getCurrentMethodFrame()->operandStack->push2(ptr->operator[](index));
	}

	inline void singleWordLoad(size_t index)
	{
		word ptr = (*this->getCurrentMethodFrame()->localVariables)[index];
		this->getCurrentMethodFrame()->operandStack->push(ptr);
	}

	inline void singleWordStore(size_t index)
	{
		word val = this->getCurrentMethodFrame()->operandStack->pop();
		(*this->getCurrentMethodFrame()->localVariables)[index] = val;
	}

	inline void wload()
	{
		unsigned char index = this->getCurrentMethodFrame()->method->getBytecode()[this->getCurrentMethodFrame()->pc++];
		this->wload(index);
	}

	inline void wload(size_t index)
	{
		word val = (*this->getCurrentMethodFrame()->localVariables)[index];
		this->getCurrentMethodFrame()->operandStack->push(val);
	}


	inline void lload(size_t index)
	{
		word high = (*this->getCurrentMethodFrame()->localVariables)[index];
		word low = (*this->getCurrentMethodFrame()->localVariables)[index + 1];

		this->getCurrentMethodFrame()->operandStack->push(high);
		this->getCurrentMethodFrame()->operandStack->push(low);
	}

	inline void lstore(size_t index)
	{
		word low = this->getCurrentMethodFrame()->operandStack->pop();
		word high = this->getCurrentMethodFrame()->operandStack->pop();

		(*this->getCurrentMethodFrame()->localVariables)[index] = high;
		(*this->getCurrentMethodFrame()->localVariables)[index + 1] = low;
	}


	inline void dload(size_t index)
	{
		word high = (*this->getCurrentMethodFrame()->localVariables)[index];
		word low = (*this->getCurrentMethodFrame()->localVariables)[index + 1];

		this->getCurrentMethodFrame()->operandStack->push(high);
		this->getCurrentMethodFrame()->operandStack->push(low);
	}

	inline void dstore(size_t index)
	{
		word low = this->getCurrentMethodFrame()->operandStack->pop();
		word high = this->getCurrentMethodFrame()->operandStack->pop();

		 (*this->getCurrentMethodFrame()->localVariables)[index] = high;
		 (*this->getCurrentMethodFrame()->localVariables)[index + 1] = low;
	}

	inline unsigned short getShort()
	{
		const Instruction * instructions = this->getCurrentMethodFrame()->method->getBytecode();
		unsigned char HIGH = instructions[this->getCurrentMethodFrame()->pc++];
		unsigned char LOW = instructions[this->getCurrentMethodFrame()->pc++];
		unsigned short value = shortFromStack(HIGH, LOW);
		return value;
	}
	
	inline unsigned int getInt()
	{
		const Instruction * instructions = this->getCurrentMethodFrame()->method->getBytecode();
		unsigned char HIGH_HIGH = instructions[this->getCurrentMethodFrame()->pc++];
		unsigned char HIGH_LOW = instructions[this->getCurrentMethodFrame()->pc++];
		unsigned char LOW_HIGH = instructions[this->getCurrentMethodFrame()->pc++];
		unsigned char LOW_LOW = instructions[this->getCurrentMethodFrame()->pc++];

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

		this->getCurrentMethodFrame()->operandStack->push(res);
	}

	inline void jumpWithOffset(int offset)
	{
		this->getCurrentMethodFrame()->pc += offset - 1;
	}

	inline void pushFromConstantPool(int index)
	{
		/*
		int or float, or a reference to a string literal, or a symbolic reference to a class, method type, or method handle
		*/

		ConstantPoolItem * item = this->getCurrentMethodFrame()->constantPool->get(index);
		word value;

		switch (item->tag)
		{
		case CONSTANT_Float:
			value = item->floatInfo.value;
			this->getCurrentMethodFrame()->operandStack->push(value);
			break;
		case CONSTANT_Integer:
			value = item->integerInfo.value;
			this->getCurrentMethodFrame()->operandStack->push(value);
			break;
		case CONSTANT_Class:
			// TODO: Resolve class name, find class object
			break;
		case CONSTANT_MethodType:

			this->getCurrentMethodFrame()->operandStack->push(value);
			break;
		case CONSTANT_MethodHandle:
			this->getCurrentMethodFrame()->operandStack->push(value);
			break;

			// LDC_W
		case CONSTANT_Long:
			{
				word high = item->longInfo.high_bytes;
				word low = item->longInfo.low_bytes;

				this->getCurrentMethodFrame()->operandStack->push(high);
				this->getCurrentMethodFrame()->operandStack->push(low);
			}
			break;
		case CONSTANT_Double:
			{
				word high = item->doubleInfo.high_bytes;
				word low = item->doubleInfo.low_bytes;

				this->getCurrentMethodFrame()->operandStack->push(high);
				this->getCurrentMethodFrame()->operandStack->push(low);
			}
			break;
		}
	}

	inline void iinc(size_t index, word value)
	{
		(*this->getCurrentMethodFrame()->localVariables)[index] += value;
	}


	inline int recursiveAllocateArray(int dimensions, int dimensionsArray[], int currentLevel = 0, ArrayObject<Object*> * previousLevel = NULL)
	{
		int currentDimension = dimensionsArray[currentLevel];

		void* memory = (ArrayObject<Object*>*)this->heap->allocate(ArrayObject<Object*>::getMemorySize(currentDimension));
		ArrayObject<Object*>* object = new(memory) ArrayObject<Object*>(currentDimension, NULL, NULL, NULL);

		int index = this->objectTable->insert((Object*)object);

		while (currentDimension-- > 0)
		{
			if (dimensions > 1)
			{
				(*object)[currentDimension] = (Object*)this->recursiveAllocateArray(dimensions - 1, dimensionsArray, currentLevel + 1, NULL);
			}
		}

		return index;
	}

	inline Method* resolveMethod(size_t index)
	{
		Method* methodPtr = nullptr;
		Class * classPtr = nullptr;

		if (index == this->inlineCache.constantPoolIndex)
		{
			// best-case scenario
		}
		else
		{
			ConstantPoolItem * item = this->getCurrentMethodFrame()->constantPool->get(index);

			classPtr = item->methodInfo.classPtr;
			methodPtr = item->methodInfo.methodPtr;

			int classIndex = item->methodInfo.class_index;
			int nameAndTypeIndex = item->methodInfo.name_and_type_index;

			ConstantPoolItem * nameAndType = this->getCurrentMethodFrame()->constantPool->get(nameAndTypeIndex);
			ConstantPoolItem * name = this->getCurrentMethodFrame()->constantPool->get(nameAndType->nameAndTypeInfo.name_index);
			ConstantPoolItem * descr = this->getCurrentMethodFrame()->constantPool->get(nameAndType->nameAndTypeInfo.descriptor_index);

			ConstantPoolItem * classConst = this->getCurrentMethodFrame()->constantPool->get(classIndex);
			ConstantPoolItem * className = this->getCurrentMethodFrame()->constantPool->get(classConst->classInfo.name_index);

			classPtr = this->classMap->getClass(Utf8String(className->utf8Info.bytes, className->utf8Info.length));

			methodPtr = classPtr->getMethod(Utf8String(name->utf8Info.bytes, name->utf8Info.length), Utf8String(descr->utf8Info.bytes, descr->utf8Info.length));

			if (classIndex == this->inlineCache.cpClassIndex)
			{
				this->inlineCache.cpClassIndex = 0;
				//method = this->inlineCache.classPtr->getMethod(name->utf8Info);
			}
		}

		methodPtr->classPtr = classPtr;

		return methodPtr;
	}

	inline MethodFrame* createMethodFrame(Method* method, Class* classPtr, Object* reference = NULL)
	{
		unsigned char* data = this->heap->allocate(MethodFrame::getMemorySize(method->operandStackSize, method->localVariablesArraySize + 1));
		MethodFrame* newFrame = new (data) MethodFrame(method->operandStackSize, method->localVariablesArraySize + 1);

		newFrame->method = method;
		newFrame->constantPool = classPtr->constantPool;

		size_t varPos = 0;

		if (reference != NULL)
		{
			(*newFrame->localVariables)[varPos++] = reference;
		}

		method->initInputArgs();

		for (size_t i = 0; i < method->countIntputArgs; i++)
		{
			TypeTag type = method->inputArgs[i];

			switch (type)
			{
			case TypeTag::LONG:
			case TypeTag::DOUBLE:
			{
				word low = this->getCurrentMethodFrame()->operandStack->pop();
				word high = this->getCurrentMethodFrame()->operandStack->pop();

				(*newFrame->localVariables)[varPos++] = low;
				(*newFrame->localVariables)[varPos++] = high;
			}
			break;

			default:
				(*newFrame->localVariables)[varPos++] = this->getCurrentMethodFrame()->operandStack->pop();
				break;
			}
		}

		return newFrame;
	}
};
