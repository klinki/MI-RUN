#pragma once
#include <cstdint>
#include <string>

typedef unsigned int ProgramCounter;
typedef unsigned char Instruction;

//typedef uintptr_t word;

typedef char java_byte;
typedef short java_short;
typedef int java_int;
typedef long long java_long;
typedef unsigned short java_char;

typedef float java_float;
typedef double java_double;

typedef void* java_ref;

typedef unsigned int Flag;

typedef unsigned char byte;


enum class TypeTag
{
	JAVA_VOID,
	BOOL,
	BYTE,
	CHAR,
	SHORT,
	INT,
	LONG,
	FLOAT,
	DOUBLE,
	REFERENCE
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
