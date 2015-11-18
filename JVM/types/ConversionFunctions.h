#pragma once
#include "../runtime/InstructionSet.h"

inline short shortFromStack(unsigned char HIGH, unsigned char LOW)
{
	return HIGH << 8 | LOW;
}

inline long longFromStack(unsigned int HIGH, unsigned int LOW)
{
	return ((long long)HIGH << 32) | LOW;
}

