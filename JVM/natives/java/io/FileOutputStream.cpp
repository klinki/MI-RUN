#pragma once
#include <iostream>
#include "FileOutputStream.h"
#include "../lang/String.h"

namespace java
{
	namespace io
	{
		namespace FileOutputStream
		{
			static Class* staticClassPtr = nullptr;

			FileOutputStream::FileOutputStream(std::ofstream * stream) : ObjectHeader(staticClassPtr)
			{
				this->stream = stream;
			}

			FileOutputStream::FileOutputStream(const FileOutputStream & copy): ObjectHeader(copy.objectClass)
			{
				this->stream = copy.stream;
			}

			FileOutputStream::~FileOutputStream() {}

			Class* initialize(ClassMap* classMap)
			{
				if (staticClassPtr != NULL)
				{
					return staticClassPtr;
				}

				Class * objectClass = classMap->getClass("java/io/OutputStream");
				Class * aClass = new Class(0);
				aClass->parentClass = objectClass;
				aClass->classLoader = NULL;
				aClass->fullyQualifiedName = "java/io/FileOutputStream";

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

				byte* memory = engine->heap->allocate(sizeof(FileOutputStream));

				std::ofstream * outputStream = new std::ofstream(string->toAsciiString(), std::ios_base::out);
				FileOutputStream* builder = new(memory) FileOutputStream(outputStream);

				engine->objectTable->updateAddress(index, builder);
			}

		};
	}
}
