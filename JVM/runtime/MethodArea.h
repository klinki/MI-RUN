#pragma once
#include "Method.h"
#include "../utils/HashMap.h"
#include "../utils/Utf16String.h"
#include "Class.h"

class MethodArea
{
protected:
	HashMap<Utf8String, Class*> hashmap;
public:
	MethodArea();
	~MethodArea();

	Method* getMethod(const Utf8String & name);
	void addMethod(Method* method);
};
