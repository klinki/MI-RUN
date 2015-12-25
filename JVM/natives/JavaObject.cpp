#include "JavaObject.h"
#include "../runtime/Class.h"
#include "../runtime/MethodFrame.h"
#include "../runtime/Method.h"
#include "../runtime/MethodArea.h"
#include "../types/Descriptors.h"
#include "../runtime/Object.h"
#include "Declarations.h"

using namespace TypeDescriptors;

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
				newClass->type = Class::Type::CLASS;
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
				newClass->methodArea.addMethod(getNativeMethod("wait", getMethodDescriptor(TypeTag::JAVA_VOID, TypeTag::LONG, TypeTag::INT), (void*) &waitTimeoutNanos));
			*/
				return newClass;
			}


			void clone(::Object* object, MethodFrame * frame)
			{
				throw Exceptions::CloneNotSupportedException();
			}

			void equals(::Object* object, MethodFrame * frame)
			{
				::Object* anotherObj = frame->operandStack->pop();

				if (anotherObj == nullptr)
				{
					frame->operandStack->push(false);
				}
				else
				{
					hashCode(object, frame);
					hashCode(anotherObj, frame);

					int secondHash = frame->operandStack->pop();
					int firstHash = frame->operandStack->pop();

					frame->operandStack->push(firstHash == secondHash);
				}
			}

			void toString(::Object* object, MethodFrame * frame)
			{
				// return JavaString(); // TODO
			}

			void finalize(::Object* object, MethodFrame * frame)
			{

			}

			void getClass(::Object* object, MethodFrame * frame)
			{
				frame->operandStack->push((int)object->objectClass);
			}

			void hashCode(::Object* object, MethodFrame * frame)
			{
				frame->operandStack->push((int)object);
			}

			void notify(::Object* object, MethodFrame * frame)
			{
			}

			void notifyAll(::Object* object, MethodFrame * frame)
			{
			}

			void waitEmpty(::Object* object, MethodFrame * frame)
			{
			}

			void waitTimeout(::Object* object, MethodFrame * frame)
			{
				long long timeout = frame->operandStack->pop2();
			}

			void waitTimeoutNanos(::Object* object, MethodFrame * frame)
			{
				long long timeout = frame->operandStack->pop2();
				int nanos = frame->operandStack->pop();
			}
		}
	}
}
