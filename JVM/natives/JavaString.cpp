#include "JavaString.h"
#include "../runtime/Object.h"

namespace Java
{
	namespace Lang
	{
		namespace String
		{
			Class* initialize()
			{
				Class * newClass = new Class(NULL);
/*				newClass->classLoader = NULL;
				newClass->parentClass = NULL;
				newClass->fullyQualifiedName = Utf8String("java/lang/System");
				newClass->type = Class::Type::CLASS;

				newClass->methodArea.addMethod(getNativeMethod(std::string("<init>"), (void*)&toString));
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
			
				newClass->methodArea.addMethod(getNativeMethod(std::string("finalize"), (void*)&toString));
*/
				return newClass;
			}

			void String(::Object * obj, MethodFrame * frm)
			{}

			void StringFromCharArray();
			void StringCopy();
			void length();
			void equals();
			void format();
			void hashCode();
			void toString();
			void clone();
		}
	}
}
