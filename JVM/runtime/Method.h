#pragma once
#include <string>
#include "types.h"

class Method
{
protected:
	const std::string name;
	const std::string descriptor;

	Instruction byteCode[1];
	unsigned int byteCodeLength;

	// exception table
	// constant table
public:
	Method();
	~Method();
};
