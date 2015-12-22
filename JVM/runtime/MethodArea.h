#pragma once
#include "Method.h"
#include "../utils/HashMap.h"
#include "../utils/Utf8String.h"

class Class;

class MethodArea
{
protected:
	HashMap<Utf8String, Class*> hashmap;
public:
	MethodArea();
	~MethodArea();

	void addClass(Class* classRef);
	Class* getClass(const Utf8String & name);

	Method* getMethod(const Utf8String & name, const Utf8String & descriptor);
	void addMethod(Method* method);
};
