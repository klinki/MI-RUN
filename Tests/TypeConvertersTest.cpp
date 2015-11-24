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
			Assert::AreEqual((short)0, shortFromStack(0x00, 0x00)); // 0
			Assert::AreEqual((short)0xFFFF, shortFromStack(0xFF, 0xFF)); // -1
			Assert::AreEqual((short)0xFF00, shortFromStack(0xFF, 0x00)); // -256
			Assert::AreEqual((short)0x00FF, shortFromStack(0x00, 0xFF)); // 255
			Assert::AreEqual((short)0x7FFF, shortFromStack(0x7F, 0xFF)); // maximal positive number:
			Assert::AreEqual((short)0x8000, shortFromStack(0x80, 0x00)); // maximal negative number
		}
		

		TEST_METHOD(intConversion)
		{
			Assert::AreEqual((int)0, intFromBytes(0x00, 0x00, 0x00, 0x00)); // 0
			Assert::AreEqual((int)0xFFFFFFFF, intFromBytes(0xFF, 0xFF, 0xFF, 0xFF)); // -1
			Assert::AreEqual((int)0x0000FFFF, intFromBytes(0x00, 0x00, 0xFF, 0xFF)); // 65535
			Assert::AreEqual((int)0xFFFF0000, intFromBytes(0xFF, 0xFF, 0x00, 0x00)); // 0
			Assert::AreEqual((int)0x7FFFFFFF, intFromBytes(0x7F, 0xFF, 0xFF, 0xFF)); // 0
			Assert::AreEqual((int)0x80000000, intFromBytes(0x80, 0x00, 0x00, 0x00)); // 0
			Assert::AreEqual((int)0x000000FF, intFromBytes(0x00, 0x00, 0x00, 0xFF)); // 0
			Assert::AreEqual((int)0x0000FF00, intFromBytes(0x00, 0x00, 0xFF, 0x00)); // 0
			Assert::AreEqual((int)0x00FF0000, intFromBytes(0x00, 0xFF, 0x00, 0x00)); // 0
			Assert::AreEqual((int)0xFF000000, intFromBytes(0xFF, 0x00, 0x00, 0x00)); // 0
		}
		
		TEST_METHOD(longConversion)
		{
			Assert::AreEqual((long long)0, longFromStack(0x00000000, 0x00000000)); // 0
			Assert::AreEqual((long long)0x00000000FFFFFFFF, longFromStack(0x00000000, 0xFFFFFFFF)); // 0
			Assert::AreEqual((long long)0xFFFFFFFF00000000, longFromStack(0xFFFFFFFF, 0x00000000)); // 0
			Assert::AreEqual((long long)0xFFFFFFFFFFFFFFFF, longFromStack(0xFFFFFFFF, 0xFFFFFFFF)); // 0
			Assert::AreEqual((long long)0x7FFFFFFFFFFFFFFF, longFromStack(0x7FFFFFFF, 0xFFFFFFFF)); // 0
			Assert::AreEqual((long long)0x8000000000000000, longFromStack(0x80000000, 0x00000000)); // 0
		}
	};
}
