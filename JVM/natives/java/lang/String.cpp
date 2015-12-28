#include "String.h"
#include "../../../runtime/Runtime.h"
#include "../../../runtime/Object.h"
#include "../../../utils/Utf8String.h"

namespace java
{
	namespace lang
	{
		namespace String
		{
			String::String(Utf8String & str, Class * classPtr): ObjectHeader(classPtr)
			{
				this->dataLength = str.bytes();
				this->hash = str.getHash();
				this->stringLength = str.length();

				strncpy_s(this->data, this->dataLength, str.toAsciiString(), this->dataLength);
			}

			Class* initialize(Runtime * runtime)
			{
				Class * newClass = new Class(NULL);
				newClass->classLoader = NULL;
				newClass->parentClass = runtime->classTable->getClass("java/lang/Object");
				newClass->fullyQualifiedName = Utf8String("java/lang/String");

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
			{
				size_t index = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop());
				Utf8String* strPtr = (Utf8String*)engine->objectTable->get(index);

				engine->getCurrentMethodFrame()->operandStack->push(strPtr->length());
			}

			NATIVE_METHOD_HEADER(hashCode)
			{
				size_t index = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop());
				Utf8String* strPtr = (Utf8String*)engine->objectTable->get(index);

				engine->getCurrentMethodFrame()->operandStack->push(strPtr->getHash());
			}

			NATIVE_METHOD_HEADER(toString)
			{
				// do nothing, string is already string (do not even modify operand stack)
			}


			NATIVE_METHOD_HEADER(clone)
			{
				size_t index = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop());
				Utf8String* strPtr = (Utf8String*)engine->objectTable->get(index);

				byte* data = engine->heap->allocate(strPtr->getMemorySize());
				Utf8String * clone = new(data) Utf8String(strPtr->toAsciiString(), strPtr->bytes());

				size_t cloneIndex = engine->objectTable->insert(clone);

				engine->getCurrentMethodFrame()->operandStack->push(makeReferenceAddress(cloneIndex));
			}
		}
	}
}
