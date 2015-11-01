#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Java Virtual Machine\declarations.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(FunctionCalls)
	{
	public:

		TEST_METHOD(constReturningFunction)
		{
			int expected = 123;
			// TODO: Add bytecode for function call without argument
			int result = 0;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(argReturningFunction)
		{
			int arg = 123;
			int expected = 123;
			// TODO: Add bytecode for function call with one argument
			int result = 0;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(argSumReturningFunction)
		{
			int a = 100;
			int b = 100;
			int expected = 200;
			// TODO: Add bytecode for function call with one argument
			int result = 0;
			Assert::AreEqual(expected, result);
		}

	};
}
