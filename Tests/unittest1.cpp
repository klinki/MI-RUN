#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Java Virtual Machine\declarations.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int expected = 2;
			int result = sum(1, 1);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(mul)
		{
			int expected = 1;
			int result = mult(1, 1);
			Assert::AreEqual(expected, result);
		}
	};
}
