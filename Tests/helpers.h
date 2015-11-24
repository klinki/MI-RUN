#pragma once
#include <string>
#include "CppUnitTest.h"
#include "../JVM/types/types.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft 
{
	namespace VisualStudio 
	{
		namespace CppUnitTestFramework 
		{
			template<> std::wstring ToString<JavaType>(const JavaType & q);
			bool operator==(const JavaType & A, const JavaType & B);
			template<> std::wstring ToString<long long>(const long long & q);


			template<> std::wstring ToString<JavaType>(const JavaType & q)
			{
				std::wstringstream ss;
				ss << L"Tag: " << (unsigned short)q.tag << L"\r\n";
				ss << L"Flags: " << (unsigned short)q.flags << L"\r\n";
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

			template<> std::wstring ToString<long long>(const long long & q)
			{
				std::wstringstream ss;
				ss << q;
				return ss.str();
			}
		}
	}
}
