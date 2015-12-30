#pragma once
#include "../../includes.h"
#include "../../../runtime/ArrayObject.h"
#include "String.h"

class Runtime;
class Class;

namespace java
{
	namespace lang
	{
		class StringBuilder : public ArrayObject<char>
		{
		protected:
			size_t bytesLength = 0;
		public:
			StringBuilder(Class* classPtr);
			StringBuilder(int size, Class* classPtr);
			~StringBuilder();

			void copy(const StringBuilder & src);

			bool canAppend(String::String* string) const;
			void append(String::String * string);

			size_t lengthInBytes() const 
			{
				return this->bytesLength;
			}

			char* getData() const
			{
				return this->arrayData;
			}

			static size_t getMemorySize(size_t fields)
			{
				return sizeof(StringBuilder) + sizeof(char) * fields;
			}
		};

		namespace StrBuilder
		{
			static const int DEFAULT_SIZE = 255;

			Class* initialize(ClassMap * runtime);

			NATIVE_METHOD_HEADER(init);

			NATIVE_METHOD_HEADER(toString);
			NATIVE_METHOD_HEADER(appendString);

		}
	}
}
