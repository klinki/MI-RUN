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

		void PrintStream::println(Utf8String)
		{
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
			Method* getNativeMethod(const std::string & name, const std::string & descriptor, void* nativeMethod)
			{
				Method * method = new Method();
				method->name = Utf8String(name);
				method->descriptor = Utf8String(descriptor);
				method->byteCode = NULL;
				method->byteCodeLength = 0;
				method->localVariablesArraySize = 0;
				method->operandStackSize = 0;
				method->nativeMethod = (NativeMethodPtr)nativeMethod;

				return method;
			};

			Method* getNativeMethod(const std::string & name, void* nativeMethod)
			{
				return getNativeMethod(name, getMethodDescriptor(), nativeMethod);
			};


			Class* initialize(ClassMap* classMap)
			{
				Class * objectClass = classMap->getClass("java/lang/Object");

				Class * aClass = new Class(0);
				aClass->parentClass = objectClass;
				aClass->classLoader = NULL;
				aClass->fullyQualifiedName = "java/io/PrintStream";

				aClass->methodArea.addMethod(getNativeMethod(std::string("println"), std::string("(D)V"), (void*)&printlnDouble));

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
