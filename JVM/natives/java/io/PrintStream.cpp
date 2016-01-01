#include "PrintStream.h"
#include "../../Declarations.h"
#include "../../includes.h"
#include "../lang/String.h"

#define PRINT_METHOD_HEADER(name, method, type) NATIVE_METHOD_HEADER(name) \
{ \
	type value = engine->getCurrentMethodFrame()->operandStack->pop(); \
	PrintStream * printStream = (PrintStream*)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference()); \
\
	if (printStream == NULL)\
	{\
		throw Exceptions::Runtime::NullPointerException();\
	}\
\
	printStream->method(value);\
}

using namespace TypeDescriptors;

namespace java
{
	namespace io
	{
		static Class* printstClassPtr;

		PrintStream::PrintStream(::word streamIndex, FileOutputStream::FileOutputStream * stream): 
			PrintStream::PrintStream(stream->stream)
		{
			this->outputStreamIndex = streamIndex;
		}

		PrintStream::PrintStream(std::ostream * stream): ObjectHeader(printstClassPtr)
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

		void PrintStream::println(double type)
		{
			this->print(type) << std::endl;
		}

		void PrintStream::println(int type)
		{
			this->print(type) << std::endl;
		}

		std::ostream & PrintStream::print(const Utf8String & ref)
		{
			return *this->output << ref.toAsciiString();
		}

		std::ostream & PrintStream::print(int value)
		{
			return *this->output << value;
		}

		std::ostream & PrintStream::print(double type)
		{
			return *this->output << type;
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

				aClass->addMethod(getNativeMethod("<init>", "(Ljava/io/OutputStream;)V", &initFromFileOutputStream));
				aClass->addMethod(getNativeMethod("println", "()V", &printlnEmpty));
				aClass->addMethod(getNativeMethod("println", "(D)V", &printlnDouble));
				aClass->addMethod(getNativeMethod("println", "(Ljava/lang/String;)V", &printlnString));

//				aClass->addMethod(getNativeMethod("print", "(D)V", &printDouble));
				aClass->addMethod(getNativeMethod("print", "(I)V", &printInt));
				aClass->addMethod(getNativeMethod("print", "(Ljava/lang/String;)V", &printString));


				Class * filterOutputStream = new Class(0);
				filterOutputStream->fullyQualifiedName = "java.io.FilterOutputStream";

				Class * outputStream = new Class(0);
				outputStream->fullyQualifiedName = "java/io/OutputStream";
				outputStream->parentClass = objectClass;

				printstClassPtr = aClass;

				return aClass;
			};

			NATIVE_METHOD_HEADER(initFromFileOutputStream)
			{
				size_t outputStreamIndex = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop());
				FileOutputStream::FileOutputStream* outputStr = (FileOutputStream::FileOutputStream*)engine->objectTable->get(outputStreamIndex);

				size_t index = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop());
				Class* classPtr = (Class*)engine->objectTable->get(index);

				byte* memory = engine->heap->allocate(sizeof(FileOutputStream::FileOutputStream));
				PrintStream* printStr = new(memory) PrintStream(outputStreamIndex, outputStr);

				engine->objectTable->updateAddress(index, printStr);
			}

			NATIVE_METHOD_HEADER(printlnEmpty)
			{
				PrintStream * printStream = (PrintStream*)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());
				printStream->println();
			}
			
			NATIVE_METHOD_HEADER(printlnDouble)
			{
				double value = engine->getCurrentMethodFrame()->operandStack->pop2();
				PrintStream * printStream = (PrintStream*)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());
				printStream->println(value);
			}

			NATIVE_METHOD_HEADER(printlnInt)
			{
				int value = engine->getCurrentMethodFrame()->operandStack->pop();
				PrintStream * printStream = (PrintStream*)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());
				printStream->println(value);
			}


			NATIVE_METHOD_HEADER(printlnString)
			{
				java::lang::String::String * string = (java::lang::String::String *)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());

				//Utf8String
				PrintStream * printStream = (PrintStream*)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());

				if (string == NULL || printStream == NULL)
				{
					throw Exceptions::Runtime::NullPointerException();
				}

				printStream->println(*string);
			}

			NATIVE_METHOD_HEADER(printString)
			{
				java::lang::String::String * string = (java::lang::String::String *)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());

				//Utf8String
				PrintStream * printStream = (PrintStream*)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());

				if (string == NULL || printStream == NULL)
				{
					throw Exceptions::Runtime::NullPointerException();
				}

				printStream->print(*string);

			}

			PRINT_METHOD_HEADER(printInt, print, int)
//			PRINT_METHOD_HEADER(printDouble, print, double)
		}
	}
}
