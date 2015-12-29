#pragma once
#include "../../includes.h"
#include <iostream>

namespace java
{
	namespace lang
	{
		namespace Throwable
		{
			class Throwable : public Object
			{
			protected:
				Method* callStack[100];
				size_t callStackSize = 100;
				size_t callStackIndex = 0;
			public:
				Throwable(Class* classPtr);
				~Throwable();

				void printStackTrace();
				void printStackTrace(std::ostream & os);

				void addStackTrace(Method* method);
			};

			Class* initialize(ClassMap * map);

			NATIVE_METHOD_HEADER(init);
			NATIVE_METHOD_HEADER(initWithMessage);
			NATIVE_METHOD_HEADER(initWithMessageAndThrowable);
			
			NATIVE_METHOD_HEADER(printStackTrace);


			static size_t getMemorySize()
			{
				return sizeof(Throwable)
					+ LocalVariablesArray::getMemorySize(2)
					- sizeof(LocalVariablesArray); // already included in size;
			}
		}
	}
}
