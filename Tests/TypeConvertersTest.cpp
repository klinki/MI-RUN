#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/types/ConversionFunctions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(TypeConvertersTest)
	{
	public:
		TEST_METHOD(shortConversion)
		{
			Assert::AreEqual(shortFromStack(0x00, 0x00), (short)0); // 0
			Assert::AreEqual(shortFromStack(0xFF, 0xFF), (short)0xFFFF); // -1
			Assert::AreEqual(shortFromStack(0xFF, 0x00), (short)0xFF00); // -256
			Assert::AreEqual(shortFromStack(0x00, 0xFF), (short)0x00FF); // 255
			Assert::AreEqual(shortFromStack(0x7F, 0xFF), (short)0x7FFF); // maximal positive number:
			Assert::AreEqual(shortFromStack(0x80, 0x00), (short)0x8000); // maximal negative number
		}


		TEST_METHOD(intConversion)
		{
			Assert::AreEqual(intFromBytes(0x00, 0x00, 0x00, 0x00), (int)0); // 0
			Assert::AreEqual(intFromBytes(0xFF, 0xFF, 0xFF, 0xFF), (int)0xFFFFFFFF); // -1
			Assert::AreEqual(intFromBytes(0x00, 0x00, 0xFF, 0xFF), (int)0x0000FFFF); // 65535
			Assert::AreEqual(intFromBytes(0xFF, 0xFF, 0x00, 0x00), (int)0xFFFF0000); // 0
			Assert::AreEqual(intFromBytes(0x7F, 0xFF, 0xFF, 0xFF), (int)0x7FFFFFFF); // 0
			Assert::AreEqual(intFromBytes(0x80, 0x00, 0x00, 0x00), (int)0x80000000); // 0
			Assert::AreEqual(intFromBytes(0x00, 0x00, 0x00, 0xFF), (int)0x000000FF); // 0
			Assert::AreEqual(intFromBytes(0x00, 0x00, 0xFF, 0x00), (int)0x0000FF00); // 0
			Assert::AreEqual(intFromBytes(0x00, 0xFF, 0x00, 0x00), (int)0x00FF0000); // 0
			Assert::AreEqual(intFromBytes(0xFF, 0x00, 0x00, 0x00), (int)0xFF0000000); // 0
		}

		TEST_METHOD(longConversion)
		{
			Assert::AreEqual(longFromStack(0x00000000, 0x00000000), (long long)0); // 0
			Assert::AreEqual(longFromStack(0x00000000, 0xFFFFFFFF), (long long)0x00000000FFFFFFFF); // 0
			Assert::AreEqual(longFromStack(0xFFFFFFFF, 0x00000000), (long long)0xFFFFFFFF00000000); // 0
			Assert::AreEqual(longFromStack(0xFFFFFFFF, 0xFFFFFFFF), (long long)0xFFFFFFFFFFFFFFFF); // 0
			Assert::AreEqual(longFromStack(0x7FFFFFFF, 0xFFFFFFFF), (long long)0x7FFFFFFFFFFFFFFF); // 0
			Assert::AreEqual(longFromStack(0x80000000, 0x00000000), (long long)0x8000000000000000); // 0


			Assert::AreEqual(intFromBytes(0xFF, 0xFF, 0xFF, 0xFF), (int)0xFFFFFFFF); // -1
			Assert::AreEqual(intFromBytes(0x00, 0x00, 0xFF, 0xFF), (int)0x0000FFFF); // 65535
			Assert::AreEqual(intFromBytes(0xFF, 0xFF, 0x00, 0x00), (int)0xFFFF0000); // 0
			Assert::AreEqual(intFromBytes(0x7F, 0xFF, 0xFF, 0xFF), (int)0x7FFFFFFF); // 0
			Assert::AreEqual(intFromBytes(0x80, 0x00, 0x00, 0x00), (int)0x80000000); // 0
			Assert::AreEqual(intFromBytes(0x00, 0x00, 0x00, 0xFF), (int)0x000000FF); // 0
			Assert::AreEqual(intFromBytes(0x00, 0x00, 0xFF, 0x00), (int)0x0000FF00); // 0
			Assert::AreEqual(intFromBytes(0x00, 0xFF, 0x00, 0x00), (int)0x00FF0000); // 0
			Assert::AreEqual(intFromBytes(0xFF, 0x00, 0x00, 0x00), (int)0xFF0000000); // 0

		}
	};
}
