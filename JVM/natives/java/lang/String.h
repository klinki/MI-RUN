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
			class String : public ObjectHeader, public Utf8String
			{
			public:
				String(size_t length, Class* classPtr): ObjectHeader(classPtr),  Utf8String(length, true) {};
				String(Utf8String & str, Class* classPtr);

				static size_t getMemorySize(size_t items)
				{
					return sizeof(String) + items * sizeof(char);
				}
			};

			Class* initialize(ClassMap * classMap);

			NATIVE_METHOD_HEADER(init);
			NATIVE_METHOD_HEADER(initFromArray);

			NATIVE_METHOD_HEADER(length);
			NATIVE_METHOD_HEADER(hashCode);
			NATIVE_METHOD_HEADER(toString);
			
			NATIVE_METHOD_HEADER(clone);
		}
	}
}
