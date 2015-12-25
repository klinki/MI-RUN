#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/utils/HashMap.h"
#include "../JVM/utils/Utf8String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Utf8StringTest)
	{
	public:

		TEST_METHOD(testHash)
		{
			Utf8String a("This should get converted to UTF8 string");
			Utf8String b = "This should get converted to UTF8 string";

			Assert::IsTrue(a == b);
		}

		TEST_METHOD(testCreateFromStringLiteral)
		{
			char charArr[] = "This should get converted to UTF8 string";
			Utf8String string = charArr;

			Assert::AreEqual(strlen(charArr), string.length());
			Assert::IsTrue(string.equals(charArr));
		}

	};
}
