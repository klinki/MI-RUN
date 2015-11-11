#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(FunctionCalls)
	{
	public:

		TEST_METHOD(testBIPUSH)
		{
			Instruction instructions[] = {
				BIPUSH,
				125
			};

			int expected = 123;
			// TODO: Add bytecode for function call without argument
			int result = 0;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testSIPUSH)
		{
			Instruction instructions[] = {
				SIPUSH,
				0x0001,
				0x0001
			};

			int arg = 123;
			int expected = 123;
			// TODO: Add bytecode for function call with one argument
			int result = 0;
			Assert::AreEqual(expected, result);
		}
	};
}
