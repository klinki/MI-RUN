#pragma once
#include <iostream>
#include "../../Declarations.h"
#include "../../includes.h"

class Class;
class ClassMap;

namespace java
{
	namespace io
	{
		namespace FileInputStream
		{
			static Class* staticClassPtr = nullptr;

			Class* initialize(ClassMap* map);

			NATIVE_METHOD_HEADER(initFromString);
		}
	}
}
