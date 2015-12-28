#include "String.h"
#include "../../../runtime/Runtime.h"
#include "../../../runtime/Object.h"

namespace java
{
	namespace lang
	{
		namespace String
		{
			Class* initialize(Runtime * runtime)
			{
				Class * newClass = new Class(NULL);
				newClass->classLoader = NULL;
				newClass->parentClass = runtime->classTable->getClass("java/lang/Object");
				newClass->fullyQualifiedName = Utf8String("java/lang/System");

				newClass->methodArea.addMethod(getNativeMethod("<init>", "()V", &init));

				newClass->methodArea.addMethod(getNativeMethod("toString", "()Ljava/lang/String;", &toString));
				newClass->methodArea.addMethod(getNativeMethod("clone", "()Ljava/lang/Object;", &clone));

				return newClass;
			}

			NATIVE_METHOD_HEADER(init)
			{

			}

			NATIVE_METHOD_HEADER(initFromArray)
			{
				// pointer is not object, but ref. to class
				size_t arrayIndex = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop()); // char array index
				Array<char>* charArray = (Array<char>*)engine->objectTable->get(arrayIndex);

				size_t index = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop());
				Class* classPtr = (Class*)engine->objectTable->get(index);

				size_t fields = classPtr->getHierarchicalCountNonStaticFields();
				size_t size = ::Object::getMemorySize(fields);
				unsigned char* memory = engine->heap->allocate(size);
				::Object* objPtr = new(memory) ::Object(fields, classPtr);

				engine->objectTable->updateAddress(index, objPtr);
			}

			NATIVE_METHOD_HEADER(length)
			{}

			NATIVE_METHOD_HEADER(hashCode)
			{}

			NATIVE_METHOD_HEADER(toString)
			{}

			NATIVE_METHOD_HEADER(clone)
			{}
		}
	}
}
