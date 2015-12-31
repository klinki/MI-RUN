#pragma once
#include <iostream>
#include <fstream>
#include "../../../runtime/Class.h"
#include "../../../runtime/MethodFrame.h"
#include "../../../runtime/ArrayObject.h"

class ClassMap;

namespace java
{
	namespace io
	{
		class FileReader
		{
			std::ifstream * input;
		public:
			FileReader(std::ifstream * stream);
			~FileReader();


			void close();
			Utf8String* Readln();
			Utf8String* Read(java_byte);
			//void write(ArrayObject<java_byte> * arr);
			//void write(ArrayObject<java_byte> * arr, size_t offset, size_t length);
		};

		namespace FileReader
		{
			Class* initialize(ClassMap* map);

			//NATIVE_METHOD_HEADER(printlnEmpty);
			//NATIVE_METHOD_HEADER(printlnString);
			//NATIVE_METHOD_HEADER(printlnDouble);
		}
	}
}
