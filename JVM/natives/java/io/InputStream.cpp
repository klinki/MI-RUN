#include <iostream>
#include "InputStream.h"
#include "../lang/String.h"

namespace java
{
	namespace io
	{
		namespace InputStream
		{
			static Class* staticClassPtr = nullptr;

			InputStream::InputStream(std::istream * stream) : ObjectHeader(staticClassPtr) 
			{
				this->stream = stream;
			}

			InputStream::InputStream(const InputStream & copy) : InputStream(copy.stream) 
			{
			}
			
			InputStream::~InputStream() 
			{
				delete this->stream;
				this->stream = nullptr;
			}	

			Class* initialize(ClassMap* classMap)
			{
				if (staticClassPtr != nullptr)
				{
					return staticClassPtr;
				}

				Class * objectClass = classMap->getClass("java/lang/Object");
				Class * aClass = new Class(0);
				aClass->parentClass = objectClass;
				aClass->classLoader = NULL;
				aClass->fullyQualifiedName = "java/io/InputStream";

				staticClassPtr = aClass;

				return aClass;
			};


			NATIVE_METHOD_HEADER(finalize)
			{
				InputStream * stream = (InputStream *)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());

				if (stream == NULL)
				{
					throw Exceptions::Runtime::NullPointerException();
				}

				stream->~InputStream();
			}
		}
	}
}
