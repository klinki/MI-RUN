#include <iostream>
#include "JavaOut.h"
#include "PrintStream.h"

namespace Java
{
	namespace Lang
	{
		namespace System
		{
			void initialize(std::ostream & os)
			{
				PrintStream* out = new PrintStream(os);
			}



			/*
			void close();
			void flush();
			void write();
			void writeWithOffset();
			void writeSingleByte();
			void println();
			*/
		}
	}
}
