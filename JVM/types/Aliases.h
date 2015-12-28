#pragma once
#include <cstdint>
#include <string>

typedef unsigned int ProgramCounter;
typedef unsigned char Instruction;

typedef char java_byte;
typedef short java_short;
typedef int java_int;
typedef long long java_long;
typedef unsigned short java_char;
typedef float java_float;
typedef double java_double;
typedef void* java_ref;

typedef unsigned char byte;
typedef unsigned int Flag;

enum class TypeTag
{
	JAVA_VOID = 'V',
	BOOL = 'B',
	BYTE = 'Z',
	CHAR = 'C',
	SHORT = 'S',
	INT = 'I',
	LONG = 'J',
	FLOAT = 'F',
	DOUBLE = 'D',
	REFERENCE = 'L',
	ARRAY = '['
};

struct JavaType
{
	std::string className;
	TypeTag tag;
	int dimensions;

	JavaType(TypeTag tag) 
	{
		this->tag = tag;
		this->className = nullptr;
	}

	JavaType(TypeTag tag, const std::string & className)
	{
		this->tag = tag;
		this->className = className;
	}
};
