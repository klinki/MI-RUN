#pragma once
#include "../utils/Array.h"
#include "../types/types.h"
class LocalVariablesArray : public Array<JavaType>
{
public:
	LocalVariablesArray();
	~LocalVariablesArray();
};

