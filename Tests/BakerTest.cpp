#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/MethodArea.h"
#include "../JVM/runtime/ExecutionEngine.h"
#include "../JVM/runtime/TypeDescriptors.h"
#include "../JVM/gc/ObjectVisitorInterface.h"
#include "../JVM/gc/Baker/BakerObjectTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(BakerTest)
	{
		TEST_METHOD(testAllocation)
		{
			BakerObjectTable * baker = new BakerObjectTable(1 * 1024, 10 * 1024);

			unsigned char* address = baker->allocate(MethodFrame::getMemorySize(10, 10));
			MethodFrame * frame = new(address) MethodFrame(10, 10, NULL, NULL, NULL, NULL);

			baker->insert((Object*)frame);
		}

		BakerObjectTable * testScrub(int numAllocations, int arraySize = 64)
		{
			BakerObjectTable * baker = new BakerObjectTable(1 * 1024, 10 * 1024);

			unsigned char* address = baker->allocate(MethodFrame::getMemorySize(10, 10));
			MethodFrame * frame = new(address) MethodFrame(10, 10, NULL, NULL, NULL, NULL);

			unsigned char* arrayPtr = baker->allocate(ArrayObject<int>::getMemorySize(arraySize));
			ArrayObject<int> * arrayObj = new(arrayPtr) ArrayObject<int>(arraySize, 0, NULL, NULL);

			for (int i = 0; i < arraySize; i++)
			{
				arrayObj->operator[](i) = i;
			}

			int methodFrameIndex = baker->insert((Object*)frame);
			int arrayIndex = baker->insert((Object*)arrayObj);

			(*frame->localVariables)[0] = getReferenceAddress(arrayIndex);

			baker->setGCRoot(getReferenceAddress(methodFrameIndex));

			for (int i = 0; i < numAllocations; i++)
			{
				baker->allocate(MethodFrame::getMemorySize(10, 10)); // allocate some garbage
			}

			MethodFrame* newMethodFrameAddress = (MethodFrame*)baker->get(methodFrameIndex);
			ArrayObject<int>* newArrayObj = (ArrayObject<int>*)baker->get(arrayIndex);

			Assert::AreNotEqual(0, (int)baker->getAccessCounter(newMethodFrameAddress));
			Assert::AreNotEqual(0, (int)baker->getAccessCounter(newArrayObj));

			Assert::AreNotEqual((unsigned int)frame, (unsigned int)newMethodFrameAddress);
			Assert::AreNotEqual((unsigned int)arrayObj, (unsigned int)newArrayObj);

			Assert::AreEqual(arraySize, (int)newArrayObj->getSize());

			for (int i = 0; i < arraySize; i++)
			{
				Assert::AreEqual(i, (int)newArrayObj->operator[](i));
			}

			return baker;
		}

		TEST_METHOD(testSimpleGc)
		{
			testScrub(47);
		}

		TEST_METHOD(testMovingToPermSpace)
		{
			BakerObjectTable * baker = testScrub(500);

			Assert::AreNotEqual(0, (int)baker->permanentSpace);
		}

	};
}
