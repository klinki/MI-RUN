#include "FileInputStream.h"
#include "../lang/String.h"
#include "InputStream.h"

namespace java
{
	namespace io
	{
		namespace FileInputStream
		{
			Class* initialize(ClassMap* classMap)
			{
				if (staticClassPtr != NULL)
				{
					return staticClassPtr;
				}

				Class * objectClass = classMap->getClass("java/io/InputStream");
				Class * aClass = new Class(0);
				aClass->parentClass = objectClass;
				aClass->classLoader = NULL;
				aClass->fullyQualifiedName = "java/io/FileInputStream";

				aClass->methodArea.addMethod(getNativeMethod("<init>", "(Ljava/lang/String;)V", &initFromString));

				staticClassPtr = aClass;

				return aClass;

			}


			NATIVE_METHOD_HEADER(initFromString)
			{
				java::lang::String::String * string = (java::lang::String::String *)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());

				if (string == NULL)
				{
					throw Exceptions::Runtime::NullPointerException();
				}


				size_t index = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop());
				Class* classPtr = (Class*)engine->objectTable->get(index);

				byte* memory = engine->heap->allocate(sizeof(InputStream::InputStream));

				std::ifstream * inputStream = new std::ifstream(string->toAsciiString(), std::ios_base::in);

				if (!inputStream->good()) {
					throw Exceptions::Runtime::FileNotFoundException(("File: " + std::string(string->toAsciiString()) + " was not found").c_str());
				}

				InputStream::InputStream* builder = new(memory) InputStream::InputStream(inputStream);

				engine->objectTable->updateAddress(index, builder);
			}
		}				
	}
}
