#include "PrintStream.h"
#include "../../Declarations.h"
#include "../../includes.h"

using namespace TypeDescriptors;
namespace java
{
	namespace io
	{
		PrintStream::PrintStream(std::ostream * stream)
		{
			this->output = stream;
		}

		PrintStream::~PrintStream()
		{
		}

		void PrintStream::close()
		{
			delete this->output;
		}

		void PrintStream::flush()
		{
			this->output->flush();
		}

		void PrintStream::println()
		{
			*this->output << std::endl;
		}

		void PrintStream::println(const Utf8String & ref)
		{
			*this->output << ref.toAsciiString() << std::endl;
		}

		void PrintStream::println(double d)
		{
			*this->output << d << std::endl;
		}

		void PrintStream::write(java_byte byte)
		{
			*this->output << byte;
		}

		void PrintStream::write(ArrayObject<java_byte>* arr)
		{
			this->write(arr, 0, arr->getSize());
		}

		void PrintStream::write(ArrayObject<java_byte>* arr, size_t offset, size_t length)
		{
			for (int i = offset; i < length; i++)
			{
				*this->output << (*arr)[i];
			}
		}


		namespace PrintStr
		{
			Class* initialize(ClassMap* classMap)
			{
				Class * objectClass = classMap->getClass("java/lang/Object");

				Class * aClass = new Class(0);
				aClass->parentClass = objectClass;
				aClass->classLoader = NULL;
				aClass->fullyQualifiedName = "java/io/PrintStream";

				aClass->methodArea.addMethod(getNativeMethod("println", "(D)V", &printlnDouble));
				aClass->methodArea.addMethod(getNativeMethod("println", "(Ljava/lang/String;)V", &printlnString));

				Class * filterOutputStream = new Class(0);
				filterOutputStream->fullyQualifiedName = "java.io.FilterOutputStream";

				Class * outputStream = new Class(0);
				outputStream->fullyQualifiedName = "java/io/OutputStream";
				outputStream->parentClass = objectClass;

				return aClass;
			};

			NATIVE_METHOD_HEADER(printlnEmpty)
			{
				PrintStream * printStream = (PrintStream*)engine->getCurrentMethodFrame()->operandStack->pop();
				printStream->println();
			}
			
			NATIVE_METHOD_HEADER(printlnDouble)
			{
				double value = engine->getCurrentMethodFrame()->operandStack->pop2();
				PrintStream * printStream = (PrintStream*)engine->getCurrentMethodFrame()->operandStack->pop();
				printStream->println(value);
			}

			NATIVE_METHOD_HEADER(printlnString)
			{
				Utf8String * string = (Utf8String *)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());

				//Utf8String
				PrintStream * printStream = (PrintStream*)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());

				if (string == NULL || printStream == NULL)
				{
					throw Exceptions::Runtime::NullPointerException();
				}

				printStream->println(*string);
			}

			void println(::Object * obj, MethodFrame * frm)
			{
				

			}

			void close(::Object *, MethodFrame *);
			void flush(::Object *, MethodFrame *);
			void write(::Object *, MethodFrame *);
			void writeWithOffset(::Object *, MethodFrame *);
			void writeSingleByte(::Object *, MethodFrame *);
		}
	}
}
