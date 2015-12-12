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
			template<> std::wstring ToString<long long>(const long long & q);

			template<> std::wstring ToString<long long>(const long long & q)
			{
				std::wstringstream ss;
				ss << q;
				return ss.str();
			}
		}
	}
}
