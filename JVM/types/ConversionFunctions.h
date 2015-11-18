#pragma once
#include "../runtime/InstructionSet.h"

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

inline long longFromStack(unsigned int HIGH, unsigned int LOW)
{
	return ((long long)HIGH << 32) | LOW;
}

inline double doubleFromStack(unsigned int HIGH, unsigned int LOW)
{
	return 0;
}
