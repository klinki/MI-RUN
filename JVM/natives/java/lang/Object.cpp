#include "Object.h"
#include "../../includes.h"

namespace java
{
	namespace lang
	{
		namespace Object
		{
			static Class* staticClassPtr = NULL;

			Class* initialize()
			{
				if (staticClassPtr != NULL)
				{
					return staticClassPtr;
				}

				Class * newClass = new Class(NULL);

				staticClassPtr = newClass;

				newClass->classLoader = NULL;
				newClass->parentClass = NULL;
				newClass->fullyQualifiedName = Utf8String("java/lang/Object");
				
				newClass->addMethod(::getNativeMethod("<init>", "()V", &init));
				newClass->addMethod(::getNativeMethod("finalize", "()V", &finalize));

				newClass->addMethod(::getNativeMethod("toString", "()Ljava/lang/String;", &toString));
				newClass->addMethod(::getNativeMethod("clone", "()Ljava/lang/Object;", &clone));
				newClass->addMethod(::getNativeMethod("equals", "(Ljava/lang/Object;)Z", &equals));

				newClass->addMethod(::getNativeMethod("hashCode", "()I", &hashCode));
		
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
				size_t index = engine->getCurrentMethodFrame()->operandStack->popReference();
				Class* classPtr = (Class*)engine->objectTable->get(index);

				size_t fields = classPtr->getHierarchicalCountNonStaticFields();
				size_t size = ::Object::getMemorySize(fields);
				unsigned char* memory = engine->heap->allocate(size);
				::Object* objPtr = new(memory) ::Object(fields, classPtr, NULL);

				engine->objectTable->updateAddress(index, objPtr);
			}

			NATIVE_METHOD_HEADER(clone)
			{
				throw Exceptions::CloneNotSupportedException();
			}

			NATIVE_METHOD_HEADER(equals)
			{
				word objReference = engine->getCurrentMethodFrame()->operandStack->popReference();
				word anotherObjReference = engine->getCurrentMethodFrame()->operandStack->popReference();

				::Object* object = engine->objectTable->get(objReference);
				::Object* anotherObj = engine->objectTable->get(anotherObjReference);

				if (anotherObj == nullptr)
				{
					engine->getCurrentMethodFrame()->operandStack->push(false);
				}
				else
				{
					Method* objectHashCode = object->objectClass->getMethod("hashCode", "()I");
					Method* anotherObjectHashCode = object->objectClass->getMethod("hashCode", "()I");

					MethodFrame* objFrame = engine->createMethodFrame(objectHashCode, object->objectClass, InstructionSet::INVOKEVIRTUAL);
					MethodFrame* anotherObjFrame = engine->createMethodFrame(anotherObjectHashCode, anotherObj->objectClass, InstructionSet::INVOKEVIRTUAL);

					engine->getCurrentMethodFrame()->operandStack->pushReference(objReference);
					engine->execute(objFrame);
					int objHash = engine->getCurrentMethodFrame()->operandStack->pop();

					engine->getCurrentMethodFrame()->operandStack->pushReference(anotherObjReference);
					engine->execute(anotherObjFrame);
					int anotherObjHash = engine->getCurrentMethodFrame()->operandStack->pop();

					engine->getCurrentMethodFrame()->operandStack->push(objHash == anotherObjHash);
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
#ifdef _DEBUG
				std::cerr << "Finalize object" << std::endl;
#endif
			}

			NATIVE_METHOD_HEADER(getClass)
			{
				::Object* object = engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());
				engine->getCurrentMethodFrame()->operandStack->push((int)object->objectClass);
			}

			NATIVE_METHOD_HEADER(hashCode)
			{
				::Object* object = engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());
				engine->getCurrentMethodFrame()->operandStack->push((int)object);
			}
		}
	}
}
