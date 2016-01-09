#pragma once
#include <iostream>
#include "../../Declarations.h"
#include "../../includes.h"

class Class;
class ClassMap;

namespace java
{
	namespace io
	{
		namespace FileOutputStream
		{
			class FileOutputStream : ObjectHeader
			{
			public:
				std::ofstream * stream;
			public:
				FileOutputStream(std::ofstream * stream);
				FileOutputStream(const FileOutputStream & copy);
				~FileOutputStream();


				virtual void copyTo(byte* address)
				{
					new(address) FileOutputStream(*this);
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

			NATIVE_METHOD_HEADER(initFromString);
		};
	}
}
