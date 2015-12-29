#pragma once
#include "../../includes.h"

class Class;
class Runtime;

namespace java
{
	namespace lang
	{
		namespace Exception
		{
			Class* initialize(ClassMap * classMap, const char* name, const char* parent = "java/lang/Exception");
		}
	}
}
