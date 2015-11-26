#pragma once
namespace Exceptions
{
	class Exception {};
	
	namespace Runtime
	{
		class RuntimeException : public Exception {};
		class NullPointerException : public RuntimeException {};
		class ArrayIndexOutOfBoundsException : public RuntimeException {};
		class ArithmeticException : public RuntimeException {};
	}
}
