#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/MethodArea.h"
#include "../JVM/runtime/ExecutionEngine.h"
#include "../JVM/runtime/TypeDescriptors.h"
#include "../JVM/gc/interfaces/ObjectVisitorInterface.h"
#include "../JVM/gc/Baker/BakerGc.h"
#include "../JVM/utils/Utf8String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	int finalizationCalled = 0;
	void testFinalizationCalled(Object* obj, ExecutionEngine* engine)
	{
		finalizationCalled++;
	}

	TEST_CLASS(BakerTest)
	{
		TEST_METHOD(testAllocation)
		{
			BakerGc * baker = new BakerGc(1 * 1024, 10 * 1024);

			unsigned char* address = baker->allocate(MethodFrame::getMemorySize(10, 10));
			MethodFrame * frame = new(address) MethodFrame(10, 10, NULL, NULL, NULL, NULL);

			baker->insert((Object*)frame);
		}

		void allocataGarbage(BakerGc * baker, int numAllocations, int arraySize)
		{
			for (int i = 0; i < numAllocations; i++)
			{
				unsigned char* address = baker->allocate(MethodFrame::getMemorySize(10, 10)); // allocate some garbage
				MethodFrame * frame = new(address) MethodFrame(10, 10, NULL, NULL, NULL, NULL);
			}
		}

		void allocateFinalizableGarbage(BakerGc * baker, int numAllocations, int arraySize, Class* aClass)
		{
			for (int i = 0; i < numAllocations; i++)
			{
				unsigned char* address = baker->allocate(ArrayObject<Object*>::getMemorySize(arraySize)); // allocate some garbage
				ArrayObject<Object*> * obj = new(address) ArrayObject<Object*>(arraySize, NULL, aClass, NULL);
			}
		}

		BakerGc * testScrub(int numAllocations, int arraySize = 64)
		{
			BakerGc * baker = new BakerGc(1 * 1024, 10 * 1024);

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

			this->allocataGarbage(baker, numAllocations, arraySize);

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

		TEST_METHOD(testFinalizationNative)
		{
			BakerGc * baker = new BakerGc(1 * 1024, 10 * 1024);

			ExecutionEngine * engine = new ExecutionEngine();
			engine->classMap = new ClassMap();
			engine->objectTable = baker;
			engine->heap = baker;

			baker->engine = engine;

			Class* newClass = new Class(0);
			newClass->fullyQualifiedName = "java.lang.Test";
			
			Method* method = new Method();
			method->nativeMethod = testFinalizationCalled;
			method->descriptor = "()V";
			method->name = "finalize";
			method->classPtr = newClass;

			newClass->methodArea.addMethod(method);
			engine->classMap->addClass(newClass);
		
			this->allocateFinalizableGarbage(baker, 3, 64, newClass);

			baker->switchMemorySlot();
			
			Assert::AreEqual(3, finalizationCalled);
		}

		TEST_METHOD(testFinalizationByteCode)
		{
			BakerGc * baker = new BakerGc(1 * 1024, 10 * 1024);

			ExecutionEngine * engine = new ExecutionEngine();
			engine->classMap = new ClassMap();
			engine->objectTable = baker;
			engine->heap = baker;

			baker->engine = engine;

			Class* newClass = new Class(0);
			newClass->fullyQualifiedName = "java.lang.Test";

			Method* method = new Method();
			method->nativeMethod = nullptr;
			method->descriptor = "()V";
			method->name = "finalize";
			method->classPtr = newClass;
			method->byteCodeLength = 2;
			method->byteCode = new Instruction[2];
			method->byteCode[0] = InstructionSet::ICONST_5;
			method->byteCodeLength = 1;
			method->operandStackSize = 1;
		
			newClass->methodArea.addMethod(method);
			engine->classMap->addClass(newClass);

			this->allocateFinalizableGarbage(baker, 3, 64, newClass);

			baker->switchMemorySlot();
		}

		
		TEST_METHOD(testSimpleGc)
		{
			testScrub(47);
		}

		TEST_METHOD(testMovingToPermSpace)
		{
			BakerGc * baker = testScrub(500);

			Assert::AreNotEqual(0, (int)baker->permanentSpace);
		}

	};
}
