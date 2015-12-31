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
		class FileReader : public ObjectHeader
		{
			std::ifstream * reader;
		public:
			FileReader(std::ifstream * stream);
			~FileReader();


			
			void close(); //Closes the stream and releases any system resources associated with it.
			int read(); //Reads a single character.
			int read(char* cbuf); //Reads characters into an array.
			int read(char* cbuf, int off, int len);//Reads characters into a portion of an array.
			//int read(CharBuffer target);//Attempts to read characters into the specified character buffer.
			bool ready();//Tells whether this stream is ready to be read.
			void reset();//Resets the stream.
			long skip(long n);//Skips characters.

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

		namespace FileRdr
		{
			Class* initialize(ClassMap* map);

			NATIVE_METHOD_HEADER(readEmpty);
			NATIVE_METHOD_HEADER(readString);
			NATIVE_METHOD_HEADER(readStrinIntInt);
		}
	}
}
