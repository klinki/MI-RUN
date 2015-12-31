#include "FileWriter.h"
#include "../../Declarations.h"
#include "../../includes.h"
#include "../lang/String.h"

using namespace TypeDescriptors;
namespace java
{
	namespace io
	{
		static Class* fileWrtClassPtr;

		FileWriter::FileWriter(std::ofstream * stream) : ObjectHeader(fileWrtClassPtr)
		{
			this->writer = stream;
		}
		FileWriter::~FileWriter()
		{
		}
		void FileWriter::close()//Closes the stream and releases any system resources associated with it.
		{
			this->writer->close();
			delete this->writer;
		}

		void FileWriter::write(int c) 
		{
			char * a = new char [1];
			a[0] = (char)c;
			writer->write(a,1);
		}
		void FileWriter::write(String::String* string) const//Reads characters into an array.
		{
			writer->write(string->bytes(), strlen(string->bytes()));
		}
	
	
	}
	
	namespace FileWrt
	{
		Class* initialize(ClassMap* classMap)
		{
			Class * objectClass = classMap->getClass("java/lang/Object");

			Class * aClass = new Class(0);
			aClass->parentClass = objectClass;
			aClass->classLoader = NULL;
			aClass->fullyQualifiedName = "java/io/FileWriter";


			//aClass->methodArea.addMethod(getNativeMethod("write", "()V", &init));
			//aClass->methodArea.addMethod(getNativeMethod("write", "(Ljava/lang/String;)Ljava/lang/StringBuilder;", &appendString));

		}
		NATIVE_METHOD_HEADER(writeInt)
		{

		}

		NATIVE_METHOD_HEADER(writeString)
		{
		}
	}