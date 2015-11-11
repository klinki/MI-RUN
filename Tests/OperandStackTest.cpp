#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\JVM\runtime\OperandStack.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<> std::wstring ToString<JavaType>(const JavaType & q)
			{ 
				std::wstringstream ss;
				ss << L"Tag: "  << (unsigned short)q.tag << L"\r\n";
				ss << L"Flags: " << (unsigned short)q.flags <<  L"\r\n";
				ss << L"Long value: " << q.longValue << L"\r\n";

				return ss.str();
			}

			bool operator==(const JavaType & A, const JavaType & B)
			{
				if (A.tag != B.tag)
				{
					return false;
				}

				return A.flags == B.flags && A.longValue == B.longValue;
			}
		}
	}
}


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
			stack.push(JavaType());
			auto callback = [&stack] { stack.push(JavaType()); };
			Assert::ExpectException<StackOverflowException>(callback);
		}

		TEST_METHOD(pushAndPopTest)
		{
			OperandStack stack(1);
			JavaType header;
			header.tag = TypeTag::LONG;
			header.flags = 0;
			header.longValue = UINT64_MAX;
			stack.push(header);
			JavaType poppedHeader = stack.pop();
			Assert::AreEqual(header, poppedHeader);
		}

		TEST_METHOD(fullStack)
		{
			OperandStack stack(1);
			stack.push(JavaType());
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
