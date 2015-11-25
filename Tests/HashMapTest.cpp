#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/utils/HashMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(HashMapTest)
	{
	public:

		TEST_METHOD(testGetIterator)
		{
			HashMap<std::string, int> map;

			int expected = 150;
			std::string key = "hello";

			map.insert(key, expected);

			auto iterator = map.getIterator(key);

			Assert::AreEqual(expected, iterator->second);
		}

		TEST_METHOD(testGetIteratorMultipleItems)
		{
			HashMap<std::string, int> map;

			int expected = 150;
			int second = 200;
			std::string key = "hello";

			map.insert(key, expected);
			map.insert(key, second);

			for (auto iterator = map.getIterator(key); iterator != map.endIterator(); ++iterator)
			{
				Assert::IsTrue(iterator->second == 150 || iterator->second == 200);
			}
		}

		TEST_METHOD(testThrowException)
		{
			HashMap<std::string, int> map;
			
			auto callback = [&map] { map.getIterator(std::string("empty")); };
			Assert::ExpectException<ItemNotFoundException>(callback);			
		}
	};
}
