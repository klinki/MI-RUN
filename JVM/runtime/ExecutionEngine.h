#pragma once
#include <math.h>
#include "InstructionSet.h"
#include "MethodFrame.h"
#include "Class.h"
#include "ArrayObject.h"
#include "MethodArea.h"
#include "ClassMap.h"
#include "../types/types.h"
#include "../types/ConversionFunctions.h"
#include "../exceptions/RuntimeExceptions.h"
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


class Runtime;
namespace java {
	namespace lang { 
		namespace Throwable { class Throwable; }
	} 
}

class ExecutionEngine
{
visibility:
	MethodFrame* frame;
	ClassMap* classMap;
	ObjectTable* objectTable;
	HeapInterface* heap;

	OperandStack * callStack;

	Runtime * runtime;

	struct {
		size_t constantPoolIndex = -1;
		size_t cpClassIndex = -1;
		size_t cpMethodIndex = -1;
		Class* classPtr = NULL;
		Method* methodPtr = NULL;
	} inlineCache;

	MethodFrame* getCurrentMethodFrame()
	{
		size_t index = getReferenceAddress(this->callStack->top());
		return (MethodFrame*)this->objectTable->get(index);
	}

public:
	ExecutionEngine();
	ExecutionEngine(Runtime* runtime);

	~ExecutionEngine();

	void execute(Method* method);
	int execute(MethodFrame * frame); // Instruction instructions[], unsigned int length);

	template <class T>
	inline void arrayStore()
	{
		word value = this->getCurrentMethodFrame()->operandStack->pop();
		int index = this->getCurrentMethodFrame()->operandStack->pop();
		int ref = this->getCurrentMethodFrame()->operandStack->popReference();

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
		int ref = this->getCurrentMethodFrame()->operandStack->popReference();

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

	inline short getShort()
	{
		const Instruction * instructions = this->getCurrentMethodFrame()->method->getBytecode();
		unsigned char HIGH = instructions[this->getCurrentMethodFrame()->pc++];
		unsigned char LOW = instructions[this->getCurrentMethodFrame()->pc++];
		short value = shortFromStack(HIGH, LOW);
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
		short offset = this->getShort();

		if (((value == 0) && (currentInstruction == IFEQ || currentInstruction == IFGE || currentInstruction == IFLE)) ||
			((value != 0) && (currentInstruction == IFNE)) ||
			((value > 0) && (currentInstruction == IFGT || currentInstruction == IFGE)) ||
			((value < 0) && (currentInstruction == IFLE || currentInstruction == IFLT)))
		{
			this->jumpWithOffset(offset - 2);
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
		else if (isnan(a) || isnan(b))
		{
			res = (currentInstruction == DCMPG || currentInstruction == FCMPG) ? 1 : -1;
		}

		this->getCurrentMethodFrame()->operandStack->push(res);
	}

	inline void jumpWithOffset(int offset)
	{
		this->getCurrentMethodFrame()->pc += offset -1;
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
		case CONSTANT_String:
		{
			size_t index = item->stringInfo.string_index;

			size_t insertedStrIndex = this->objectTable->insert(item->stringInfo.stringObject, true);
			this->getCurrentMethodFrame()->operandStack->pushReference(insertedStrIndex);
		}
		break;
		}
	}

	inline void iinc(size_t index, word value)
	{
		(*this->getCurrentMethodFrame()->localVariables)[index] += value;
	}

	inline bool isInstanceOf(Class* ref, Class* resolvedClass)
	{
		// 1) if ref is class
		//	if resolved is class -> same or parent of ref
		//	resolved is interface -> ref implements resolved
		// 2) if res is interface
		//	if resolved is class -> resolved is object
		//	if resolved is interface -> ref is same or extends resolved
		// 3) ref is array
		//	if resolved is class -> object
		//	if resolved is interface -> must be implemented by array
		//	if resolved is array -> same primitive array type
		//  ref and resolved are reference arrays - ref item must be castable to resolved item

		if (ref->fullyQualifiedName == resolvedClass->fullyQualifiedName)
		{
			return true;
		}
			
		if (ref->isClass())
		{

		}

		//if (ref->isSubclassOf(resolvedClass))

		return ref->isSubclassOf(resolvedClass) || ref->implementsInterface(resolvedClass);
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

	inline Method* resolveMethod(size_t index, Instruction instruction)
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

//		methodPtr->classPtr = classPtr;

		if (instruction == INVOKEVIRTUAL)
		{
			size_t inputArgsSize = methodPtr->inputArgsSize;
			size_t stackSize = this->getCurrentMethodFrame()->operandStack->index - 1;
			word reference = getReferenceAddress(this->getCurrentMethodFrame()->operandStack->operator[](stackSize - inputArgsSize));

			void* ptr = this->objectTable->get(reference);

			ObjectHeader* objectPtr = (ObjectHeader*)ptr;
			Method* overloadedPtr = objectPtr->objectClass->getMethod(methodPtr->name, methodPtr->descriptor);

//			overloadedPtr->classPtr = classPtr; // TODO: Verify this

			return overloadedPtr;
		}

		return methodPtr;
	}

	inline Field* resolveField(size_t index)
	{
		ConstantPoolItem * item = this->getCurrentMethodFrame()->constantPool->get(index);

		ConstantPoolItem * classItem = this->getCurrentMethodFrame()->constantPool->get(item->fieldInfo.class_index);
		ConstantPoolItem * className = this->getCurrentMethodFrame()->constantPool->get(classItem->classInfo.name_index);

		Class* classPtr = this->classMap->getClass(Utf8String(className->utf8Info.bytes, className->utf8Info.length));

		ConstantPoolItem * fieldNameAndType = this->getCurrentMethodFrame()->constantPool->get(item->fieldInfo.name_and_type_index);
		ConstantPoolItem * fieldName = this->getCurrentMethodFrame()->constantPool->get(fieldNameAndType->nameAndTypeInfo.name_index);
		ConstantPoolItem * fieldType = this->getCurrentMethodFrame()->constantPool->get(fieldNameAndType->nameAndTypeInfo.descriptor_index);

		Field* field = (Field*)classPtr->getField(Utf8String(fieldName->utf8Info.bytes, fieldName->utf8Info.length), Utf8String(fieldType->utf8Info.bytes, fieldType->utf8Info.length));

		return field;
	}

	inline Class* resolveClass(size_t index)
	{
		ConstantPoolItem * item = this->getCurrentMethodFrame()->constantPool->get(index);

		ConstantPoolItem * classItem = this->getCurrentMethodFrame()->constantPool->get(item->fieldInfo.class_index);
		ConstantPoolItem * className = this->getCurrentMethodFrame()->constantPool->get(classItem->classInfo.name_index);

		Class* classPtr = this->classMap->getClass(Utf8String(className->utf8Info.bytes, className->utf8Info.length));

		return classPtr;
	}

	inline MethodFrame* createMethodFrame(Method* method, Class* classPtr, Instruction currentInstruction)
	{
		unsigned char* data = this->heap->allocate(MethodFrame::getMemorySize(method->operandStackSize, method->localVariablesArraySize + 1));
		MethodFrame* newFrame = new (data) MethodFrame(method->operandStackSize, method->localVariablesArraySize + 1);

		newFrame->method = method;
		newFrame->constantPool = classPtr->constantPool;

		method->initInputArgs();

		size_t varPos = method->inputArgsSize;

		if (currentInstruction == INVOKESTATIC)
		{
			varPos--;
		}

		for (size_t i = method->countIntputArgs; i > 0; i--)
		{
			TypeTag type = method->inputArgs[i-1];

			switch (type)
			{
			case TypeTag::LONG:
			case TypeTag::DOUBLE:
			{
				word low = this->getCurrentMethodFrame()->operandStack->pop();
				word high = this->getCurrentMethodFrame()->operandStack->pop();

				(*newFrame->localVariables)[varPos--] = low;
				(*newFrame->localVariables)[varPos--] = high;
			}
			break;

			default:
				(*newFrame->localVariables)[varPos--] = this->getCurrentMethodFrame()->operandStack->pop();
				break;
			}
		}

		if (currentInstruction != INVOKESTATIC)
		{
			size_t reference = this->getCurrentMethodFrame()->operandStack->pop();
			(*newFrame->localVariables)[0] = reference;

			if (currentInstruction != INVOKESPECIAL)
			{
				void*ptr = this->objectTable->get(getReferenceAddress(reference));
				ObjectHeader* referencePtr = (ObjectHeader*)ptr;
				// newFrame->constantPool = referencePtr->objectClass->constantPool;
			}
		}

		return newFrame;
	}

	bool handleException(java::lang::Throwable::Throwable* e);

	void dropCurrentFrame()
	{
		this->callStack->pop();
	}
};
