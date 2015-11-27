#pragma once
#include "Aliases.h"

union word
{
	intptr_t intValue;
	float floatValue;

	operator int() const { return intValue; }
	operator unsigned int() const { return (unsigned int)intValue; }
	operator float() const { return floatValue; }
	operator unsigned short() const { return (unsigned short)intValue; }


	template <class T>
	operator T*() const { return (T*)intValue; }

	word() { intValue = 0; }
	word(unsigned int val) { intValue = val; }
	word(intptr_t val) { intValue = val; }
	word(float val) { floatValue = val;  }

	word & operator += (word val) { intValue += val.intValue; return *this;  }
};

enum class TypeTag
{
	JAVA_VOID = 0,
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
/*
class ValueType;
class Integer;
class Long;
class Short;
class Char;
class Boolean;
class Double;
class Float;

class Array;
*/

class JavaType;
class JavaValueType;
class JavaVoid;
class JavaByte;
class JavaChar;
class JavaBoolean;
class JavaShort;
class JavaInt;
class JavaLong;
class JavaFloat;
class JavaDouble;
class JavaRefType;
class JavaArray;
class JavaObject;


inline word JavaInt(int val)
{
	return val;
};

inline word JavaFloat(float val)
{
	return val;
};

inline word JavaByte(java_char val)
{
	return val;
};

inline word JavaShort(java_short val)
{
	return val;
};


class JavaType
{
public:
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

public:
	JavaType() {}
	JavaType(TypeTag tag) : tag(tag) {}

	JavaType operator+(JavaType &);
};

class JavaValueType : public JavaType
{
};

class JavaVoid : public JavaType
{
public:
	JavaVoid(): JavaType(TypeTag::JAVA_VOID) { }
};


class JavaInt : public JavaType
{
public:
	JavaInt(): JavaInt(0) {}
	JavaInt(int value): JavaType(TypeTag::INT)
	{
		this->intValue = value;
	}
};

class JavaFloat : public JavaType
{
public:
	JavaFloat(float value) : JavaType(TypeTag::FLOAT)
	{
		this->floatValue = value;
	}
};

class JavaLong : public JavaType
{
public:
	JavaLong(long value) : JavaType(TypeTag::LONG)
	{
		this->longValue = value;
	}
};

class JavaDouble : public JavaType
{
public:
	JavaDouble(double value) : JavaType(TypeTag::DOUBLE)
	{
		this->doubleValue = value;
	}
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
