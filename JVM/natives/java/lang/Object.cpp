#include "Object.h"
#include "../../includes.h"

using namespace TypeDescriptors;

namespace Java
{
	namespace Lang
	{
		namespace Object
		{
			Method* getNativeMethod(const std::string & name, const std::string & descriptor, void* nativeMethod)
			{
				Method * method = new Method();
				method->name = Utf8String(name);
				method->descriptor = Utf8String(descriptor);
				method->byteCode = NULL;
				method->byteCodeLength = 0;
				method->localVariablesArraySize = 0;
				method->operandStackSize = 0;
				method->nativeMethod = (NativeMethodPtr)nativeMethod;

				return method;
			}

			Method* getNativeMethod(const std::string & name, void* nativeMethod)
			{
				return getNativeMethod(name, getMethodDescriptor(), nativeMethod);
			}

			Class* initialize()
			{
				Class * newClass = new Class(NULL);
				newClass->classLoader = NULL;
				newClass->parentClass = NULL;
				newClass->fullyQualifiedName = Utf8String("java/lang/Object");
				
				newClass->methodArea.addMethod(getNativeMethod(std::string("<init>"),  &init));
/*
				newClass->methodArea.addMethod(getNativeMethod("toString", getMethodDescriptor(JavaType(TypeTag::REFERENCE, "java/lang/String;")), (void*)&toString));
				newClass->methodArea.addMethod(getNativeMethod("clone", getMethodDescriptor(JavaType(TypeTag::REFERENCE, "java/lang/Object;")), (void*)&clone));
				newClass->methodArea.addMethod(getNativeMethod("equals", getMethodDescriptor(TypeTag::BOOL, JavaType(TypeTag::REFERENCE, "java/lang/Object;")), (void*)&equals));
				newClass->methodArea.addMethod(getNativeMethod("finalize", getMethodDescriptor(), (void*)&finalize));
				newClass->methodArea.addMethod(getNativeMethod("getClass", getMethodDescriptor(JavaType(TypeTag::REFERENCE, "java/lang/Class;")), (void*)&getClass));
				newClass->methodArea.addMethod(getNativeMethod("hashCode", getMethodDescriptor(TypeTag::JAVA_VOID, TypeTag::INT), (void*)&hashCode));
				newClass->methodArea.addMethod(getNativeMethod("notify", getMethodDescriptor(), (void*)&notify));
				newClass->methodArea.addMethod(getNativeMethod("notifyAll", getMethodDescriptor(), (void*)&notifyAll));
				newClass->methodArea.addMethod(getNativeMethod("wait", getMethodDescriptor(), (void*)&waitEmpty));
				newClass->methodArea.addMethod(getNativeMethod("wait", getMethodDescriptor(TypeTag::JAVA_VOID, TypeTag::LONG), (void*)&waitTimeout));
			//	newClass->methodArea.addMethod(getNativeMethod("wait", getMethodDescriptor(TypeTag::JAVA_VOID, TypeTag::LONG, TypeTag::INT), (void*) &waitTimeoutNanos));
			*/
				newClass->methodArea.addMethod(getNativeMethod(std::string("finalize"), (void*)&finalize));

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

			NATIVE_METHOD_HEADER(notify)
			{
			}

			NATIVE_METHOD_HEADER(notifyAll)
			{
			}

			NATIVE_METHOD_HEADER(waitEmpty)
			{
			}

			NATIVE_METHOD_HEADER(waitTimeout)
			{
				long long timeout = engine->getCurrentMethodFrame()->operandStack->pop2();
			}

			NATIVE_METHOD_HEADER(waitTimeoutNanos)
			{
				long long timeout = engine->getCurrentMethodFrame()->operandStack->pop2();
				int nanos = engine->getCurrentMethodFrame()->operandStack->pop();
			}
		}
	}
}
