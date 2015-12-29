#pragma once
#include <exception>

namespace Exceptions
{
#define ExceptionClass(name, parent, javaException) \
	class name : public parent \
	{\
		public:\
		name(): parent(javaException) {}; \
		name(const char* excName): parent(excName) {}; \
	};

	ExceptionClass(Exception, std::exception, "java/lang/Throwable");
	ExceptionClass(CloneNotSupportedException, Exception, "java/lang/CloneNotSupportedException");

	namespace Runtime
	{
		ExceptionClass(RuntimeException, Exception, "java/lang/RuntimeException");
		
		ExceptionClass(NullPointerException, RuntimeException, "java/lang/NullPointerException");
		ExceptionClass(ArrayIndexOutOfBoundsException, RuntimeException, "java/lang/ArrayIndexOutOfBoundsException");
		ExceptionClass(ArithmeticException, RuntimeException, "java/lang/ArithmeticException");
		ExceptionClass(NegativeArraySizeException, RuntimeException, "java/lang/NegativeArraySizeException");
		ExceptionClass(ArrayStoreException, RuntimeException, "java/lang/ArrayStoreException");
		ExceptionClass(ClassCastException, RuntimeException, "java/lang/ClassCastException");
	}
}

namespace Errors
{
	ExceptionClass(Error, std::exception, "java/lang/Throwable");
	ExceptionClass(AbstractMethodError, Error, "java/lang/AbstractMethodError");
	ExceptionClass(IncompatibleClassChangeError, Error, "java/lang/IncompatibleClassChangeError");
	ExceptionClass(NoSuchMethodError, Error, "java/lang/NoSuchMethodError");
	ExceptionClass(IllegalAccessError, Error, "java/lang/IllegalAccessError");
	ExceptionClass(UnsatisfiedLinkError, Error, "java/lang/UnsatisfiedLinkError");
}
