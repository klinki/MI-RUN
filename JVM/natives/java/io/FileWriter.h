#pragma once
#include <iostream>
#include <fstream>
#include "../../../runtime/Class.h"
#include "../../../runtime/MethodFrame.h"
#include "../../../runtime/ArrayObject.h"
#include "../lang/String.h"

class ClassMap;

namespace java
{
	namespace io
	{
		class FileWriter : public ObjectHeader
		{
			std::ofstream * writer;
		public:
			FileWriter(std::ofstream * stream);
			~FileWriter();

			void close(); //Closes the stream and releases any system resources associated with it.
			void write(int c); //Writes a single character.
			void write(String::String* string)const;//Writes a string.


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

		namespace FileWrt
		{
			Class* initialize(ClassMap* classMap);
			NATIVE_METHOD_HEADER(writeInt);
			NATIVE_METHOD_HEADER(writeString);
		}
	}
}
