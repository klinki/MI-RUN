#pragma once
#include "Method.h"

class MethodArea
{
protected:

public:
	MethodArea();
	~MethodArea();

	Method* getMethod(const std::string name);
	void addMethod(Method* method);
};
