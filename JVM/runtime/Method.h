#pragma once
#include <string>
#include <cstring>
#include "ConstantPool.h"
#include "../types/types.h"
#include "ExceptionTable.h"
#include "../utils/Utf8String.h"
//#include "../classfile/ClassLoader.h"
#include "../utils/Macros.h"
#include "../natives/Declarations.h"
#include "AccessFlags.h"
#include "ClassMember.h"

class Method : public ClassMember
{
visibility:
	Instruction* byteCode;
	size_t byteCodeLength;

	size_t operandStackSize;
	size_t localVariablesArraySize;

	ExceptionTable * exceptionTable;

	NativeMethodPtr nativeMethod;
	Class*  classPtr;

	TypeTag * inputArgs;
	size_t countIntputArgs;

	size_t inputArgsSize;

	void setDescriptor(const Utf8String & str)
	{
		this->descriptor = str;
		this->initInputArgs();
	}

protected:
	void resizeInputArgs()
	{
		TypeTag * newArray = new TypeTag[this->countIntputArgs];
		memcpy(newArray, this->inputArgs, this->countIntputArgs * sizeof(*this->inputArgs));
		delete[] this->inputArgs;
		this->inputArgs = newArray;
	}

public:
	Method() : Method(0) {};
	Method(FLAG f) : ClassMember()
	{
		this->flags = f;
		this->operandStackSize = 0;
		this->localVariablesArraySize = 0;
		this->byteCode = nullptr;
		this->nativeMethod = nullptr;
		this->byteCodeLength = 0;
		this->exceptionTable = nullptr;
		this->classPtr = nullptr;
		this->inputArgs = new TypeTag[255];
		this->countIntputArgs = 0;
		this->inputArgsSize = 0;
	};
	~Method()
	{
		delete[] this->byteCode;
		this->byteCode = NULL;

		delete[] this->inputArgs;
		this->inputArgs = NULL;


		delete this->exceptionTable;
		this->exceptionTable = NULL;
	}

	bool isNative() const
	{
		return this->nativeMethod != nullptr;
	}

	const Instruction* getBytecode() const
	{
		return this->byteCode;
	}

	const size_t getByteCodeLength() const
	{
		return this->byteCodeLength;
	}

	bool returnsData() const
	{
		return this->descriptor != "V";
	}

	bool isSpecial() const
	{

	}

	bool isConstructor() const
	{
		return false;
	}

	bool isAbstract() const
	{
		return (this->flags & (int)MethodAccessFlags::ABSTRACT) == (int)(MethodAccessFlags::ABSTRACT);
	}

	void initInputArgs()
	{
		std::string descr = this->descriptor.toAsciiString();

		int i = 1;

		int index = 0;

		this->inputArgsSize = 0;

		while (descr[i] != ')')
		{
			switch (descr[i++])
			{
			case '[':
			case 'L':
				while (descr[i++] != ';');
				this->inputArgs[index++] = TypeTag::REFERENCE;
				this->inputArgsSize++;
				break;
			case 'D':
				this->inputArgs[index++] = TypeTag::DOUBLE;
				this->inputArgsSize += 2;
				break;
			case 'J':
				this->inputArgs[index++] = TypeTag::LONG;
				this->inputArgsSize += 2;
				break;
			default:
				this->inputArgs[index++] = TypeTag::INT;
				this->inputArgsSize++;
				break;
			}
		}

		this->countIntputArgs = index;
		this->resizeInputArgs();
	}

	friend class ClassLoader;
};
