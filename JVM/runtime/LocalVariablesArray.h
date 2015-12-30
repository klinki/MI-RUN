#pragma once
#include "../utils/Array.h"
#include "../types/types.h"
class LocalVariablesArray : public Array<word>
{
public:
	LocalVariablesArray() : LocalVariablesArray(10) {};
	LocalVariablesArray(size_t size) : Array(size) {};
	LocalVariablesArray(size_t size, byte * address) : Array(size, address + sizeof(LocalVariablesArray)) {}
	~LocalVariablesArray() {}

	word get(size_t index)
	{
		return (*this)[index];
	}

	doubleWord get2(size_t index)
	{
		word high = (*this)[index];
		word low = (*this)[index + 1];

		return doubleWord(high, low);
	}

	void set(size_t itemIndex, word value)
	{
		(*this)[itemIndex] = value;
	}

	void set2(size_t itemIndex, doubleWord value)
	{
		(*this)[itemIndex] = value.words[1];
		(*this)[itemIndex + 1] = value.words[0];
	}
};
