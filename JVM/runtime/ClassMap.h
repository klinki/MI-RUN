#pragma once
#include "../utils/HashMap.h"
#include "../utils/Macros.h"
#include "../utils/Utf8String.h"
#include "Class.h"

class ClassMap
{
visibility:
	HashMap<Utf8String, Class*> hashmap;
public:
	ClassMap();
	~ClassMap();

	void addClass(Class* classRef);
	Class* getClass(const Utf8String & name);
};
