#pragma once
#include "Method.h"
#include "../utils/HashMap.h"
#include "../utils/Utf16String.h"
#include "Class.h"

class MethodArea
{
protected:
	HashMap<std::u16string, Class*> hashmap;
public:
	MethodArea();
	~MethodArea();

	Method* getMethod(const Utf16String & name);
	void addMethod(Method* method);
};
