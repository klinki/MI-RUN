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
};
