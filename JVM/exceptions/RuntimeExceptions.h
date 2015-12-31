#pragma once
#include <exception>
#include <string>

namespace Exceptions
{
#define ExceptionClass(name, parent, javaException) \
	class name : public parent \
	{\
		public:\
		name(): name(NULL, javaException) {}; \
		name(const char* message): name(message, javaException) {}; \
		name(const char* message, const char* exception): parent(message, exception) {}; \
	};

	class Throwable : public std::exception
	{
	protected:
		std::string message;
                std::string exceptionName;
	public:
		Throwable(): Throwable(NULL) {};
		Throwable(const char* message) : Throwable(message, "java/lang/Throwable") {}
		Throwable(const char* message, const char* parent): exceptionName(parent), message(message) {};

		const char* getMessage() 
		{
			return message.c_str();
		}
                
                const char* what()
                {
                    return exceptionName.c_str();
                }
	};

	ExceptionClass(Exception, Throwable, "java/lang/Throwable");
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
	ExceptionClass(Error, Exceptions::Throwable, "java/lang/Error");
	ExceptionClass(AbstractMethodError, Error, "java/lang/AbstractMethodError");
	ExceptionClass(IncompatibleClassChangeError, Error, "java/lang/IncompatibleClassChangeError");
	ExceptionClass(NoSuchMethodError, Error, "java/lang/NoSuchMethodError");
	ExceptionClass(IllegalAccessError, Error, "java/lang/IllegalAccessError");
	ExceptionClass(UnsatisfiedLinkError, Error, "java/lang/UnsatisfiedLinkError");
	ExceptionClass(LinkageError, Error, "java/lang/LinkageError");
	ExceptionClass(NoClassDefFoundError, LinkageError, "java/lang/NoClassDefFoundError");
	ExceptionClass(OutOfMemoryError, Error, "java/lang/OutOfMemoryError");
}
