#pragma once
#include "../../includes.h"

class Class;
class Runtime;

namespace java
{
	namespace lang
	{
		namespace String
		{
			Class* initialize(Runtime * runtime);

			NATIVE_METHOD_HEADER(init);
			NATIVE_METHOD_HEADER(initFromArray);

			NATIVE_METHOD_HEADER(length);
			NATIVE_METHOD_HEADER(hashCode);
			NATIVE_METHOD_HEADER(toString);
			
			NATIVE_METHOD_HEADER(clone);
		}
	}
}
