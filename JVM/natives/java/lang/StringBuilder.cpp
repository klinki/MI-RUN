#include "StringBuilder.h"
#include "../../../runtime/ArrayObject.h"
#include "../../includes.h"
#include "String.h"

using namespace java::lang::String;

namespace java
{
	namespace lang
	{
		StringBuilder::StringBuilder(int size, Class* classPtr) : ArrayObject<char>(size, 0, classPtr, (byte*)(&this->bytesLength + 1))
		{
			this->bytesLength = 0;
		}

		StringBuilder::StringBuilder(Class * classPtr): StringBuilder(StrBuilder::DEFAULT_SIZE, classPtr)
		{
		}

		StringBuilder::~StringBuilder()
		{
		}

		void StringBuilder::copy(const StringBuilder & src)
		{
			this->bytesLength = src.bytesLength;
			memcpy(this->arrayData, src.arrayData, src.bytesLength);
		}

		bool StringBuilder::canAppend(String::String * string) const
		{
			return this->size >= (this->bytesLength + string->bytes());
		}

		void StringBuilder::append(String::String * string)
		{
			int shift = (this->bytesLength > 0) ? (this->bytesLength) : 0;
			memcpy(this->arrayData + shift, string->toAsciiString(), string->bytes());

			this->bytesLength += string->bytes() - 1;
		}

		namespace StrBuilder
		{
			Class* initialize(ClassMap * classMap)
			{
				Class * newClass = new Class(NULL);
				newClass->classLoader = NULL;
				newClass->parentClass = classMap->getClass("java/lang/Object");
				newClass->fullyQualifiedName = Utf8String("java/lang/StringBuilder");
				newClass->countNonStaticFields = 1;

				newClass->methodArea.addMethod(getNativeMethod("<init>", "()V", &init));
				newClass->methodArea.addMethod(getNativeMethod("append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;", &appendString));
				newClass->methodArea.addMethod(getNativeMethod("toString", "()Ljava/lang/String;", &toString));

				return newClass;
			};

			NATIVE_METHOD_HEADER(init)
			{
				// pointer is not object, but ref. to class
				size_t index = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop());
				Class* classPtr = (Class*)engine->objectTable->get(index);

				byte* memory = engine->heap->allocate(StringBuilder::getMemorySize(DEFAULT_SIZE));
				StringBuilder* builder = new(memory) StringBuilder(engine->classMap->getClass("java/lang/StringBuilder"));

				engine->objectTable->updateAddress(index, builder);
			}

			NATIVE_METHOD_HEADER(appendString)
			{
				// pointer is not object, but ref. to class
				size_t strIndex = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop());
				String::String* strPtr = (String::String*) engine->objectTable->get(strIndex);

				size_t builderIndex = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop());
				StringBuilder* builder = (StringBuilder*)engine->objectTable->get(builderIndex);

				if (!builder->canAppend(strPtr))
				{
					size_t newSize = builder->getSize() * 2;
					byte* memory = engine->heap->allocate(StringBuilder::getMemorySize(newSize));
					StringBuilder* newBuilder = new StringBuilder(newSize, builder->objectClass);

					engine->objectTable->updateAddress(builderIndex, newBuilder);

					newBuilder->copy(*builder);
					builder = newBuilder;
				}

				builder->append(strPtr);

				engine->getCurrentMethodFrame()->operandStack->pushReference(builderIndex);
			}

			NATIVE_METHOD_HEADER(toString)
			{
				size_t builderIndex = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop());
				StringBuilder* builder = (StringBuilder*)engine->objectTable->get(builderIndex);

				byte* memory = engine->heap->allocate(String::String::getMemorySize(builder->lengthInBytes()));
				String::String* strPtr = (String::String*) new(memory) String::String(builder->getData(), builder->lengthInBytes(), engine->classMap->getClass("java/lang/String"), true);

				size_t strIndex = engine->objectTable->insert(strPtr);

				engine->getCurrentMethodFrame()->operandStack->push(makeReferenceAddress(strIndex));
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
		}
	}
}
