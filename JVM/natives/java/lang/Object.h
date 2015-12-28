#pragma once
#include "../../../utils/Macros.h"

class Class;
class Object;
class MethodFrame;

namespace Java
{
	namespace Lang
	{
		namespace Object
		{
			Class* initialize();

			NATIVE_METHOD_HEADER(init);
			NATIVE_METHOD_HEADER(finalize);

			NATIVE_METHOD_HEADER(clone);

			NATIVE_METHOD_HEADER(equals);
			NATIVE_METHOD_HEADER(hashCode);

			NATIVE_METHOD_HEADER(getClass);

			NATIVE_METHOD_HEADER(notify);
			NATIVE_METHOD_HEADER(notifyAll);

			NATIVE_METHOD_HEADER(toString);
			
			NATIVE_METHOD_HEADER(waitEmpty);
			NATIVE_METHOD_HEADER(waitTimeout);
			NATIVE_METHOD_HEADER(waitTimeoutNanos);
		}
	}
}
