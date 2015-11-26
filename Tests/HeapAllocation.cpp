#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Object.h"
#include "../JVM/runtime/MethodFrame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(HeapAllocation)
	{
	public:
		TEST_METHOD(allocateArray)
		{
			size_t sizeofArray = sizeof(Array<Object*>);
			size_t sizeofItems = 10 * sizeof(Object*);

			unsigned char * test = (unsigned char*)operator new(sizeofArray + sizeofItems);
			Array<Object*> * arrayPtr = (Array<Object*> *) new(test) Array<Object*>(10, test);

			for (int i = 0; i < 10; i++)
			{
				(*arrayPtr)[i] = (Object*)i;
			}

			int* intPtr = (int*)test;

			Assert::AreEqual(10, *intPtr);
			Assert::AreEqual(0, intPtr[1]);
			Assert::AreEqual(0xCDCDCD01, (unsigned int)intPtr[2]);
			Assert::AreEqual((int)(intPtr + 4), intPtr[3]);

			for (int i = 0; i < 10; i++)
			{
				Assert::AreEqual(i, intPtr[4 + i]);
			}

			Assert::AreEqual(0xFDFDFDFD, (unsigned int)intPtr[14]);

			delete test;
		}

		TEST_METHOD(allocateObject)
		{
			unsigned char * objPtr = (unsigned char*)operator new(Object::getMemorySize(10));
			Object * obj = (Object*) new(objPtr) Object(10, NULL, objPtr);

			for (int i = 0; i < 10; i++)
			{
				obj->fields[i] = i;
			}

			for (int i = 0; i < 10; i++)
			{
				int field = obj->fields[i];
				std::cout << field << std::endl;
			}

			int* intPtr = (int*)obj;
			intPtr++;

			Assert::AreEqual(NULL, * (intPtr - 1));
			Assert::AreEqual(10, *intPtr);
			Assert::AreEqual(0, intPtr[1]);
			Assert::AreEqual(0xCDCDCD01, (unsigned int)intPtr[2]);
			Assert::AreEqual((int)(intPtr + 4), intPtr[3]);

			for (int i = 0; i < 10; i++)
			{
				Assert::AreEqual(i, intPtr[4 + i]);
			}

			Assert::AreEqual(0xFDFDFDFD, (unsigned int)intPtr[14]);

			delete obj;
		}

		TEST_METHOD(allocateMethodFrame)
		{
			unsigned char * objPtr = (unsigned char*)operator new(MethodFrame::getMemorySize(10, 10));

			MethodFrame * frm = (MethodFrame*) new(objPtr) MethodFrame(10, 10, NULL, NULL, NULL, objPtr);

			int* intPtr = (int*)frm;

			for (int i = 0; i < 10; i++)
			{
				frm->operandStack->allocatedArray[i] = i;
				frm->localVariables->allocatedArray[i] = 10 - i;
			}

			Assert::AreEqual(0, *intPtr);
			Assert::AreEqual(0, intPtr[1]);
			Assert::AreEqual(0, intPtr[2]);
			Assert::AreEqual(0, intPtr[3]);
			Assert::AreEqual(0, intPtr[4]);
			Assert::AreEqual(0, intPtr[5]);
			Assert::AreEqual((int)(intPtr + 8), intPtr[6]);
			Assert::AreEqual((int)(intPtr + 8 + OperandStack::getMemorySize(10) / 4), intPtr[7]);

			Assert::AreEqual(10, intPtr[8]);
			Assert::AreEqual(0, intPtr[9]);
			Assert::AreEqual(0xCDCDCD01, (unsigned int)intPtr[10]);
			Assert::AreEqual((int)(intPtr + 12), intPtr[11]);

			for (int i = 0; i < 10; i++)
			{
				Assert::AreEqual(10 - i, intPtr[12 + i]);
			}
			

			Assert::AreEqual(10, intPtr[22]);
			Assert::AreEqual(0, intPtr[23]);
			Assert::AreEqual(0xCDCDCD01, (unsigned int)intPtr[24]);
			Assert::AreEqual((int)(intPtr + 26), intPtr[25]);

			for (int i = 0; i < 10; i++)
			{
				Assert::AreEqual(i, intPtr[26 + i]);
			}

			Assert::AreEqual(0xFDFDFDFD, (unsigned int)intPtr[MethodFrame::getMemorySize(10, 10) / 4]);
		}
	};
}
