#pragma once
namespace Exceptions
{
	class Exception {};
	
	namespace Runtime
	{
		class RuntimeException : Exception {};
		class NullPointerException : RuntimeException {};
		class ArrayIndexOutOfBoundsException : RuntimeException {};
		class ArithmeticException : RuntimeException {};
	}
}
