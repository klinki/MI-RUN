#pragma once
#include <iostream>
#include "../../../runtime/Class.h"
#include "../../../runtime/MethodFrame.h"
#include "../../../runtime/ArrayObject.h"

class ClassMap;

namespace java
{
	namespace io
	{
		class PrintStream
		{
			std::ostream * output;
		public:
			PrintStream(std::ostream * stream);
			~PrintStream();

			void close();
			void flush();
			void println();
			void println(double d);
			void println(const Utf8String & ref);
			void write(java_byte);
			void write(ArrayObject<java_byte> * arr);
			void write(ArrayObject<java_byte> * arr, size_t offset, size_t length);
		};

		namespace PrintStr
		{
			Class* initialize(ClassMap* map);

			NATIVE_METHOD_HEADER(printlnEmpty);
			NATIVE_METHOD_HEADER(printlnString);
			NATIVE_METHOD_HEADER(printlnDouble);
		}
	}
}
