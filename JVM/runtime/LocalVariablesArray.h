#pragma once
#include "../utils/Array.h"
#include "../types/types.h"
class LocalVariablesArray : public Array<word>
{
public:
	LocalVariablesArray() : LocalVariablesArray(10) {};
	LocalVariablesArray(size_t size) : Array(size) {};
	~LocalVariablesArray() {}

#ifdef _DEBUG
	LocalVariablesArray(size_t size, bool debugging) : Array(size, debugging) {}
#endif
};
