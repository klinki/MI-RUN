#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\JVM\runtime\OperandStack.h"
#include "..\JVM\runtime\ExecutionEngine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{


	TEST_CLASS(OperandStackTest)
	{
	public:

		TEST_METHOD(popEmptyStack)
		{
			OperandStack stack;
			auto callback = [&stack] { stack.pop(); };
			Assert::ExpectException<StackEmtpyException>(callback);
		}

		TEST_METHOD(pushFullStack)
		{
			OperandStack stack(1);
			stack.push(0);
			auto callback = [&stack] { stack.push(0); };
			Assert::ExpectException<StackOverflowException>(callback);
		}

		TEST_METHOD(pushAndPopTest)
		{
			OperandStack stack(1);
			int input = 42;
			stack.push(input);
			int poppedWord = stack.pop();
			Assert::AreEqual(input, poppedWord);
		}

		TEST_METHOD(fullStack)
		{
			OperandStack stack(1);
			stack.push(0);
			bool result = stack.isFull();
			bool expected = true;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(emptyStack)
		{
			OperandStack stack(1);
			bool result = stack.isEmpty();
			bool expected = true;
			Assert::AreEqual(expected, result);
		}

	};
}
