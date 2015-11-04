#pragma once
#include "Method.h"

class MethodArea
{
public:
	MethodArea();
	~MethodArea();

	Method* getMethod(const std::string name);
	void addMethod(Method* method);
};
