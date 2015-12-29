#pragma once
#include <string>
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

public:
	Method() : Method(0) {};
	Method(FLAG f) : ClassMember()
	{
		this->flags = f;
		this->operandStackSize = 0;
		this->localVariablesArraySize = 0;
		this->nativeMethod = nullptr;
	};
	~Method();

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

	void initInputArgs()
	{
		std::string descr = this->descriptor.toAsciiString();

		int i = 1;

		this->inputArgs = new TypeTag[100];

		int index = 0;

		while (descr[i] != ')')
		{
			switch (descr[i++])
			{
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
	}

	friend class ClassLoader;
};
