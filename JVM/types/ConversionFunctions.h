#pragma once
#include "types.h"
#include "../runtime/InstructionSet.h"

unsigned const int REFERENCE_MASK = 0xF0000000;

union doubleUnion
{
	unsigned int words[2];
	double val;
};

inline short shortFromStack(unsigned char HIGH, unsigned char LOW)
{
	return HIGH << 8 | LOW;
}

inline int intFromBytes(unsigned char HIGH_HIGH, unsigned char HIGH_LOW, unsigned char LOW_HIGH, unsigned char LOW_LOW)
{
	return (((int)HIGH_HIGH << 24)) |
			((int)(HIGH_LOW << 16)) |
			((int)(LOW_HIGH << 8))  |
			((int)LOW_LOW);
}

inline long long longFromStack(unsigned int HIGH, unsigned int LOW)
{
	return ((long long)HIGH << 32) | LOW;
}

inline double doubleFromStack(unsigned int HIGH, unsigned int LOW)
{
	doubleUnion un;
	un.words[0] = HIGH;
	un.words[1] = LOW;
	return un.val;
}


inline unsigned int lowWord(long long val)
{
	return (unsigned int)val;
}

inline unsigned int highWord(long long val)
{
	return (unsigned int)(val >> 32);
}

inline unsigned int lowWord(double val)
{
	doubleUnion un;
	un.val = val;

	return un.words[1];
}

inline unsigned int highWord(double val)
{
	doubleUnion un;
	un.val = val;

	return un.words[0];
}

inline unsigned char lowByte(short val)
{
	return (unsigned char)val;
}

inline unsigned char highByte(short val)
{
	return (unsigned char)(val >> 8);
}

inline unsigned short highShort(int val)
{
	return (unsigned short)(val >> 16);
}

inline unsigned short lowShort(int val)
{
	return (unsigned short)val;
}


inline bool isReferenceAddress(word value)
{
	return (((int)(value)) & REFERENCE_MASK) == REFERENCE_MASK;
}

inline unsigned int getReferenceAddress(word value)
{
	return (int)(value) ^ REFERENCE_MASK;
}

inline word makeReferenceAddress(word value)
{
	return (int)value | REFERENCE_MASK;
}
