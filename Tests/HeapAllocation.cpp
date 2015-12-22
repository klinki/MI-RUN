#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Object.h"
#include "../JVM/runtime/MethodFrame.h"
#include "../JVM/runtime/ArrayObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(HeapAllocation)
	{
	public:
		TEST_METHOD(allocateArrayObject)
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
			intPtr++; // virtual table address
			intPtr++; // for sake of test

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
			intPtr++; // virtual table

			for (int i = 0; i < 10; i++)
			{
				frm->operandStack->allocatedArray[i] = i;
				frm->localVariables->allocatedArray[i] = 10 - i;
			}

			Assert::AreEqual(0, *intPtr); // PC
			Assert::AreEqual(0, intPtr[1]); // SP
			Assert::AreEqual(0, intPtr[2]); // Method* 
			Assert::AreEqual(0, intPtr[3]); // CP*
			Assert::AreEqual(0, intPtr[4]); // parent*
			Assert::AreEqual(0, intPtr[5]); // child* 
			Assert::AreEqual((int)(intPtr + 8), intPtr[6]); // locals* 
			Assert::AreEqual((int)(intPtr + 8 + OperandStack::getMemorySize(10) / 4), intPtr[7]); // stack* 

			Assert::AreEqual(10, intPtr[8]); // locals size
			Assert::AreEqual(0, intPtr[9]); // locals index
			Assert::AreEqual(0xCDCDCD01, (unsigned int)intPtr[10]); // locals preallocated
			Assert::AreEqual((int)(intPtr + 12), intPtr[11]); // locals array ptr

			for (int i = 0; i < 10; i++)
			{
				Assert::AreEqual(10 - i, intPtr[12 + i]); // locals values
			}
			

			Assert::AreEqual(10, intPtr[22]); // stack size
			Assert::AreEqual(0, intPtr[23]); // stack index
			Assert::AreEqual(0xCDCDCD01, (unsigned int)intPtr[24]); // stack preallocated
			Assert::AreEqual((int)(intPtr + 26), intPtr[25]); // stack array ptr

			for (int i = 0; i < 10; i++)
			{
				Assert::AreEqual(i, intPtr[26 + i]); // stack values
			}

			int canaryIndex = MethodFrame::getMemorySize(10, 10) / 4 - 1; // -1 is because of virtual table (we already moved intPtr)

			Assert::AreEqual(0xFDFDFDFD, (unsigned int)intPtr[canaryIndex]); // canary
		}

		TEST_METHOD(allocateArrayObjectInt)
		{
			size_t sizeofArray = sizeof(ArrayObject<int>);
			size_t sizeofItems = 10 * sizeof(int);

			unsigned char * test = (unsigned char*)operator new(sizeofArray + sizeofItems);
			ArrayObject<int> * objectPtr = (ArrayObject<int> *) new(test) ArrayObject<int>(10, 0, NULL, test);

			for (int i = 0; i < 10; i++)
			{
				(*objectPtr)[i] = i;
			}

			int* intPtr = (int*)test;
			intPtr++; // virtual table

			Assert::AreEqual(0, *intPtr);
			Assert::AreEqual(10, intPtr[1]);
			Assert::AreEqual((int)(intPtr + 3), intPtr[2]);

			for (int i = 0; i < 10; i++)
			{
				Assert::AreEqual(i, intPtr[3 + i]);
			}

			Assert::AreEqual(0xFDFDFDFD, (unsigned int)intPtr[13]);

			delete test;
		}
	};
}
