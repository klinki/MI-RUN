#pragma once
namespace Exceptions
{
	class Exception {};
	class CloneNotSupportedException {};

	namespace Runtime
	{
		class RuntimeException : public Exception {};
		class NullPointerException : public RuntimeException {};
		class ArrayIndexOutOfBoundsException : public RuntimeException {};
		class ArithmeticException : public RuntimeException {};
		class NegativeArraySizeException : public RuntimeException {};
		class ArrayStoreException : public RuntimeException {};
		class ClassCastException : public RuntimeException {};

	};
};

namespace Errors
{
	class Error {};
	class AbstractMethodError : public Error {};
	class IncompatibleClassChangeError : public Error {};
	class NoSuchMethodError : public Error {};
	class IllegalAccessError : public Error {};
	class UnsatisfiedLinkError : public Error {};
};
