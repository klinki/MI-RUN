#pragma once
#include <iostream>
#include "../../../runtime/Class.h"
#include "../../../runtime/MethodFrame.h"
#include "../../../runtime/ArrayObject.h"
#include "../../../types/types.h"

class ClassMap;
class Class;
class Runtime;

namespace java
{
	namespace utils
	{
		namespace Scanner
		{
			class Scanner : ObjectHeader
			{
			public:
				std::istream * stream;
			public:
				Scanner(std::istream * stream);
				Scanner(const Scanner & copy);
				~Scanner();


				virtual void copyTo(byte* address)
				{
					new(address) Scanner(*this);
				}

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

			Class* initialize(ClassMap* classMap);

			NATIVE_METHOD_HEADER(initFromInputStream);
			NATIVE_METHOD_HEADER(nextInt);
		}
	}
}

