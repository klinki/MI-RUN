#pragma once
#include <string>
class Method
{
protected:
	const std::string name;
	const char* byteCode;
	unsigned int byteCodeLength;
	// exception table
	// constant table
public:
	Method();
	~Method();
};
