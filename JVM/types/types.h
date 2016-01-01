#pragma once
#include "Aliases.h"

union word
{
	intptr_t intValue;
	float floatValue;

	operator size_t() const { return intValue; }
	operator int() const { return intValue; }
	operator float() const { return floatValue; }
	operator unsigned short() const { return (unsigned short)intValue; }
	operator bool() const { return (bool)intValue; }
	operator short() const { return (short)intValue; }

	template <class T>
	operator T*() const { return (T*)intValue; }

	word() { intValue = 0; }
	word(size_t val) { intValue = val; }
	word(intptr_t val) { intValue = val; }
	word(float val) { floatValue = val;  }
	
	template <class T>
	word(T* ptr) { intValue = (intptr_t)ptr; }

	word & operator += (word val) { intValue += val.intValue; return *this;  }
};

union doubleWord
{
	unsigned int words[2];
	double doubleValue;
	long long longValue;

	doubleWord() { words[0] = words[1] = 0; }
	doubleWord(size_t high, size_t low) { words[0] = low; words[1] = high; }
        doubleWord(word high, word low) { words[0] = low; words[1] = high; }
	doubleWord(long long value) { longValue = value; }
	doubleWord(double value) { doubleValue = value; }

	operator double() const { return doubleValue; }
	operator long long() const { return longValue; }
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
