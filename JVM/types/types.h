#pragma once

typedef unsigned int ProgramCounter;
typedef unsigned char Instruction;


typedef char java_byte;
typedef short java_short;
typedef int java_int;
typedef long java_long;
typedef unsigned short java_char;

typedef float java_float;
typedef double java_double;

typedef void* java_ref;

typedef unsigned int Flag;

enum TypeTag
{
	VOID = 0,
	NULL_TYPE,
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

class Object;
//class ReferenceType;

class ValueType;
class Integer;
class Long;
class Short;
class Char;
class Boolean;
class Double;
class Float;

class Array;

struct TypeHeader
{
	TypeTag tag; // 1B
	Flag flags; // 1B
	// 2 or 6B free
	union {
		double doubleValue; // 8B
		long long longValue; // 8B
		Object* objectPtr; // 4-8B

		int intValue; // 4B 
		float floatValue; // 4B
		bool boolValue;
		short shortValue;
		char byteValue;
		unsigned short charValue;
	}; // 8B
};





// JAVA type hierarchy
/*
class ValueType;
class   VoidType;
class   IntType;
class     IntConstant;
class     IntInterval;
class   LongType;
class     LongConstant;
class   FloatType;
class     FloatConstant;
class   DoubleType;
class     DoubleConstant;
class   ObjectType;
class     ObjectConstant;
class     ArrayType;
class       ArrayConstant;
class     InstanceType;
class       InstanceConstant;
class     ClassType;
class       ClassConstant;
class   AddressType;
class     AddressConstant;
class   IllegalType;
*/
