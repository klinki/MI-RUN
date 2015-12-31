#include "FileReader.h"
#include "../../Declarations.h"
#include "../../includes.h"
#include "../lang/String.h"

using namespace TypeDescriptors;
namespace java
{
	namespace io
	{
		FileReader::FileReader(std::ifstream * stream)
		{
			this->input = stream;
		}

		FileReader::~FileReader()
		{
		}

		void FileReader::close()
		{
			delete this->input;
		}

		Utf8String * FileReader::println()
		{
			char* line;
			getline(this->input,line);
			return new Utf8String(line,strlen(line));
		}

		Utf8String * FileReader::Utf8String* Read(java_byte)
		{
		
		
		}
		
		namespace PrintStr
		{
			Class* initialize(ClassMap* classMap)
			{
				Class * objectClass = classMap->getClass("java/lang/Object");

				Class * aClass = new Class(0);
				aClass->parentClass = objectClass;
				aClass->classLoader = NULL;
				aClass->fullyQualifiedName = "java/io/FileReader";

				aClass->methodArea.addMethod(getNativeMethod("println", "(D)V", &printlnDouble));
				aClass->methodArea.addMethod(getNativeMethod("println", "(Ljava/lang/String;)V", &printlnString));

				Class * filterOutputStream = new Class(0);
				filterOutputStream->fullyQualifiedName = "java.io.FilterOutputStream";

				Class * outputStream = new Class(0);
				outputStream->fullyQualifiedName = "java/io/OutputStream";
				outputStream->parentClass = objectClass;

				return aClass;
			};
			/*
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
				java::lang::String::String * string = (java::lang::String::String *)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());

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
			*/
		}
	}
}
