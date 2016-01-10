#include "String.h"
#include <cstring>
#include "../../../runtime/Runtime.h"
#include "../../../runtime/Object.h"
#include "../../../utils/Utf8String.h"
#include "../../../runtime/Class.h"

namespace java
{
	namespace lang
	{
		namespace String
		{
			static Class* staticClassPtr;

			String::String(const char* str, bool preallocated) : String(str, strlen(str), staticClassPtr, preallocated) {};

			String::String(const char* str, size_t length, Class* classPtr, bool preallocated): ObjectHeader(classPtr), Utf8String(str, length, preallocated)
			{
			}

			String::String(Utf8String & str, Class * classPtr): ObjectHeader(classPtr)
			{
				this->dataLength = str.bytes();
				this->hash = str.getHash();
				this->stringLength = str.length();

				memcpy(this->data, str.toAsciiString(), str.bytes());
			}

			Class* initialize(ClassMap * classMap)
			{
				Class * newClass = new Class(NULL);
				staticClassPtr = newClass;
				newClass->classLoader = NULL;
				newClass->parentClass = classMap->getClass("java/lang/Object");
				newClass->fullyQualifiedName = Utf8String("java/lang/String");

				newClass->addMethod(getNativeMethod("<init>", "()V", &init));

				newClass->addMethod(getNativeMethod("toString", "()Ljava/lang/String;", &toString));
				newClass->addMethod(getNativeMethod("clone", "()Ljava/lang/Object;", &clone));
				newClass->addMethod(getNativeMethod("hashCode", "()I", &hashCode));
				newClass->addMethod(getNativeMethod("length", "()I", &length));
				newClass->addMethod(getNativeMethod("equals", "(Ljava/lang/Object;)Z", &equals));

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
				java::lang::String::String* strPtr = (java::lang::String::String*)engine->objectTable->get(index);

				engine->getCurrentMethodFrame()->operandStack->push(strPtr->length());
			}

			NATIVE_METHOD_HEADER(hashCode)
			{
				size_t index = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop());
				java::lang::String::String* strPtr = (java::lang::String::String*)engine->objectTable->get(index);

				engine->getCurrentMethodFrame()->operandStack->push(strPtr->getHash());
			}

			NATIVE_METHOD_HEADER(toString)
			{
				// do nothing, string is already string (do not even modify operand stack)
			}


			NATIVE_METHOD_HEADER(clone)
			{
				size_t index = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop());
				java::lang::String::String* strPtr = (java::lang::String::String*)engine->objectTable->get(index);

				byte* data = engine->heap->allocate(strPtr->getMemorySize(strPtr->bytes()));
				java::lang::String::String* clone = new(data) java::lang::String::String(strPtr->toAsciiString(), strPtr->bytes());

				size_t cloneIndex = engine->objectTable->insert(clone);

				engine->getCurrentMethodFrame()->operandStack->push(makeReferenceAddress(cloneIndex));
			}

			NATIVE_METHOD_HEADER(equals)
			{
				word objReference = engine->getCurrentMethodFrame()->operandStack->popReference();
				word anotherObjReference = engine->getCurrentMethodFrame()->operandStack->popReference();

				java::lang::String::String * object = (java::lang::String::String*)engine->objectTable->get(objReference);
				java::lang::String::String * anotherObj = (java::lang::String::String*)engine->objectTable->get(anotherObjReference);

				if (object == nullptr)
				{
					throw Exceptions::Runtime::NullPointerException();
				}

				if (anotherObj == nullptr)
				{
					engine->getCurrentMethodFrame()->operandStack->push(false);
				}
				else
				{
					bool equal = false;

					if (object->bytes() == anotherObj->bytes() && object->getHash() == anotherObj->getHash())
					{
						int result = strcmp(object->toAsciiString(), anotherObj->toAsciiString());
						equal = result == 0;
					}

					engine->getCurrentMethodFrame()->operandStack->push(equal);
				}
			}
		}
	}
}
