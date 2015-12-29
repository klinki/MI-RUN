#include "Object.h"
#include "../../includes.h"

namespace Java
{
	namespace Lang
	{
		namespace Object
		{
			Class* initialize()
			{
				Class * newClass = new Class(NULL);
				newClass->classLoader = NULL;
				newClass->parentClass = NULL;
				newClass->fullyQualifiedName = Utf8String("java/lang/Object");
				
				newClass->methodArea.addMethod(::getNativeMethod("<init>", "()V", &init));
				newClass->methodArea.addMethod(::getNativeMethod("finalize", "()V", &finalize));

				newClass->methodArea.addMethod(::getNativeMethod("toString", "()Ljava/lang/String;", &toString));
				newClass->methodArea.addMethod(::getNativeMethod("clone", "()Ljava/lang/Object;", &clone));
				newClass->methodArea.addMethod(::getNativeMethod("equals", "(Ljava/lang/Object;)B", &equals));

				newClass->methodArea.addMethod(::getNativeMethod("hashCode", "()I", &hashCode));
		
			/*
				newClass->methodArea.addMethod(getNativeMethod("getClass", getMethodDescriptor(JavaType(TypeTag::REFERENCE, "java/lang/Class;")), (void*)&getClass));
				newClass->methodArea.addMethod(getNativeMethod("notify", getMethodDescriptor(), (void*)&notify));
				newClass->methodArea.addMethod(getNativeMethod("notifyAll", getMethodDescriptor(), (void*)&notifyAll));
				newClass->methodArea.addMethod(getNativeMethod("wait", getMethodDescriptor(), (void*)&waitEmpty));
				newClass->methodArea.addMethod(getNativeMethod("wait", getMethodDescriptor(TypeTag::JAVA_VOID, TypeTag::LONG), (void*)&waitTimeout));
				newClass->methodArea.addMethod(getNativeMethod("wait", getMethodDescriptor(TypeTag::JAVA_VOID, TypeTag::LONG, TypeTag::INT), (void*) &waitTimeoutNanos));
			*/

				return newClass;
			}

			NATIVE_METHOD_HEADER(init)
			{
				// pointer is not object, but ref. to class
				size_t index = getReferenceAddress(engine->getCurrentMethodFrame()->operandStack->pop());
				Class* classPtr = (Class*)engine->objectTable->get(index);

				size_t fields = classPtr->getHierarchicalCountNonStaticFields();
				size_t size = ::Object::getMemorySize(fields);
				unsigned char* memory = engine->heap->allocate(size);
				::Object* objPtr = new(memory) ::Object(fields, classPtr);

				engine->objectTable->updateAddress(index, objPtr);
			}

			NATIVE_METHOD_HEADER(clone)
			{
				throw Exceptions::CloneNotSupportedException();
			}

			NATIVE_METHOD_HEADER(equals)
			{
				::Object* anotherObj = engine->getCurrentMethodFrame()->operandStack->pop();

				if (anotherObj == nullptr)
				{
					engine->getCurrentMethodFrame()->operandStack->push(false);
				}
				else
				{
					hashCode(object, engine);
					hashCode(anotherObj, engine);

					int secondHash = engine->getCurrentMethodFrame()->operandStack->pop();
					int firstHash = engine->getCurrentMethodFrame()->operandStack->pop();

					engine->getCurrentMethodFrame()->operandStack->push(firstHash == secondHash);
				}
			}

			NATIVE_METHOD_HEADER(toString)
			{
				// return JavaString(); // TODO
				size_t index = engine->getCurrentMethodFrame()->operandStack->popReference();
				Utf8String* classPtr = (Utf8String*)engine->objectTable->get(index);

				if (classPtr == NULL)
				{
					throw Exceptions::Runtime::NullPointerException();
				}
			}

			NATIVE_METHOD_HEADER(finalize)
			{

			}

			NATIVE_METHOD_HEADER(getClass)
			{
				engine->getCurrentMethodFrame()->operandStack->push((int)object->objectClass);
			}

			NATIVE_METHOD_HEADER(hashCode)
			{
				engine->getCurrentMethodFrame()->operandStack->push((int)object);
			}
		}
	}
}
