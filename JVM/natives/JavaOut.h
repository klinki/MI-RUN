#pragma once
#include <iostream>

namespace Java
{
	namespace Lang
	{
		namespace System
		{
				void initialize(std::ostream & os = std::cout);

				/*
				void close();
				void flush();
				void write();
				void writeWithOffset();
				void writeSingleByte();
				void println();
				*/

				class Out
				{
					std::ostream output;
				public:
					Out(std::ostream & stream);

					void close();
					void flush();
					void write();
					void writeWithOffset();
					void writeSingleByte();
					void println();
				};
		}
	}
}
