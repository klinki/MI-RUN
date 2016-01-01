#pragma once
#include <iostream>
#include "../../../runtime/Class.h"
#include "../../../runtime/MethodFrame.h"
#include "../../../runtime/ArrayObject.h"
#include "../../../types/types.h"

class Class;
class ClassMap;

namespace java
{
	namespace io
	{
		namespace InputStream
		{
			class InputStream : ObjectHeader
			{
			public:
				std::istream * stream;
			public:
				InputStream(std::istream * stream);
				InputStream(const InputStream & copy);
				~InputStream();


				virtual void copyTo(byte* address)
				{
					new(address) InputStream(*this);
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


			Class* initialize(ClassMap* map);

			NATIVE_METHOD_HEADER(finalize);
		}
	}
}
