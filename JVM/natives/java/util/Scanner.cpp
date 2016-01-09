#pragma once
#include "Scanner.h"
#include "../../includes.h"
#include "../io/InputStream.h"

class ClassMap;
class Class;
class Runtime;

namespace java
{
	namespace utils
	{
		namespace Scanner
		{
			static Class* staticClassPtr;

			Scanner::Scanner(std::istream * stream) : ObjectHeader(staticClassPtr)
			{
				this->stream = stream;
			}

			Scanner::Scanner(const Scanner & copy) : Scanner(copy.stream) {}

			Scanner::~Scanner()
			{
			}

			Class* initialize(ClassMap* classMap)
			{
				if (staticClassPtr != NULL)
				{
					return staticClassPtr;
				}

				Class * objectClass = classMap->getClass("java/lang/Object");
				Class * aClass = new Class(0);
				aClass->parentClass = objectClass;
				aClass->classLoader = NULL;
				aClass->fullyQualifiedName = "java/util/Scanner";

				aClass->addMethod(getNativeMethod("<init>", "(Ljava/io/InputStream;)V", &initFromInputStream));
				aClass->addMethod(getNativeMethod("nextInt", "()I", &nextInt));

				staticClassPtr = aClass;

				return aClass;

			}


			NATIVE_METHOD_HEADER(initFromInputStream)
			{
				java::io::InputStream::InputStream * stream = (java::io::InputStream::InputStream *)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());

				if (stream == NULL)
				{
					throw Exceptions::Runtime::NullPointerException();
				}


				size_t index = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop());
				Class* classPtr = (Class*)engine->objectTable->get(index);

				byte* memory = engine->heap->allocate(sizeof(Scanner));

				Scanner* scanner = new(memory) Scanner(stream->stream);

				engine->objectTable->updateAddress(index, scanner);
			}

			NATIVE_METHOD_HEADER(nextInt)
			{
				Scanner * scanner = (Scanner *)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());

				if (scanner == NULL)
				{
					throw Exceptions::Runtime::NullPointerException();
				}

				int value = 0;
				(*scanner->stream) >> value;

				engine->getCurrentMethodFrame()->operandStack->push(value);
			}
		}
	}
}

