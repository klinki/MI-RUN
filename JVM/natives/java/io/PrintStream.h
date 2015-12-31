#pragma once
#include <iostream>
#include "../../../runtime/Class.h"
#include "../../../runtime/MethodFrame.h"
#include "../../../runtime/ArrayObject.h"
#include "FileOutputStream.h"
#include "../../../types/types.h"

class ClassMap;

namespace java
{
	namespace io
	{
		class PrintStream : public ObjectHeader
		{
			std::ostream * output;
			::word outputStreamIndex;

		public:
			PrintStream(::word streamIndex, FileOutputStream::FileOutputStream * stream);
			PrintStream(std::ostream * stream);
			PrintStream(const PrintStream & copy) : PrintStream(copy.output) {}
			~PrintStream();

			virtual void copyTo(byte* address)
			{
				new(address) PrintStream(*this);
			}

			void close();
			void flush();
			void println();

			void println(double type);
			
			void println(const Utf8String & ref);

			std::ostream & print(const Utf8String & ref);

//			template <class T>
			std::ostream & print(double type);
			

			void write(java_byte);
			void write(ArrayObject<java_byte> * arr);
			void write(ArrayObject<java_byte> * arr, size_t offset, size_t length);


			virtual void accept(ObjectVisitorInterface * visitor)
			{
				visitor->visit(this);
			};

			virtual void accept(ObjectVisitorInterface & visitor)
			{
				this->accept(&visitor);
			};

			virtual bool requiresFinalization()
			{
				return false;
			}
		};

		namespace PrintStr
		{
			Class* initialize(ClassMap* map);

			NATIVE_METHOD_HEADER(initFromFileOutputStream);
			NATIVE_METHOD_HEADER(printlnEmpty);
			NATIVE_METHOD_HEADER(printlnString);
			NATIVE_METHOD_HEADER(printlnDouble);
		}
	}
}
