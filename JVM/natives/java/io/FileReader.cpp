#include "FileReader.h"
#include "../../Declarations.h"
#include "../../includes.h"
#include "../lang/String.h"

using namespace TypeDescriptors;
namespace java
{
	namespace io
	{
		static Class* fileRdClassPtr;

		FileReader::FileReader(std::ifstream * stream) : ObjectHeader(fileRdClassPtr)
		{
			this->reader = stream;
		}
		FileReader::~FileReader()
		{
		}
		void FileReader::close()//Closes the stream and releases any system resources associated with it.
		{
			delete this->reader;
		}
		void FileReader::mark(int readAheadLimit)//Marks the present position in the stream.
		{
		
		}
		bool FileReader::markSupported() //Tells whether this stream supports the mark() operation.
		{
		
		}
		int FileReader::read() //Reads a single character.
		{
			if (reader->is_open())
			{
				reader->read(NULL, 1);
				return true;
			}
			return false;
		}
		int FileReader::read(char* cbuf) //Reads characters into an array.
		{
			if (reader->is_open())
			{
				reader->read(cbuf,1);
				return true;
			}
			return false;
		}
		int FileReader::read(char* cbuf, int off, int len)//Reads characters into a portion of an array.
		{
			if (reader->is_open())
			{
				reader->read(cbuf+off, len);
				return true;
			}
			return false;
		}
		bool FileReader::ready()//Tells whether this stream is ready to be read.
		{
			
			return reader->is_open();
			
		}
		void FileReader::reset()//Resets the stream.
		{
		
		}
		long FileReader::skip(long n)//Skips characters.
		{
			if (reader->is_open())
			{
				reader->read(NULL, n);
				return true;
			}
			return false;
		}
		namespace FileRdr
		{
			Class* initialize(ClassMap* classMap)
			{
				Class * objectClass = classMap->getClass("java/lang/Object");

				Class * aClass = new Class(0);
				aClass->parentClass = objectClass;
				aClass->classLoader = NULL;
				aClass->fullyQualifiedName = "java/io/FileReader";

				//aClass->methodArea.addMethod(getNativeMethod("", "(D)V", &printlnDouble));
				//aClass->methodArea.addMethod(getNativeMethod("println", "(Ljava/lang/String;)V", &printlnString));

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
