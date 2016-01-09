#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"
#include "../JVM/natives/java/lang/Object.h"
#include "../JVM/natives/java/lang/Array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	int finalizationCalled = 0;
	void testFinalizationCalled(ExecutionEngine* engine)
	{
		finalizationCalled++;
	}

	TEST_CLASS(PermSpaceCollection)
	{
		Runtime * prepare(size_t youngSize = 10 * 1024, size_t oldSize = 10 * 1024)
		{
			Runtime* runtime = new Runtime(0, NULL);
			BakerGc * baker = new BakerGc(youngSize, oldSize);
			runtime->objectTable = baker;
			runtime->heap = baker;

			runtime->classTable->addClass(java::lang::Object::initialize());

			return runtime;
		}

		TEST_METHOD(testAllocation)
		{
			BakerGc * baker = (BakerGc*)this->prepare()->heap;
			unsigned char* address = baker->allocate(MethodFrame::getMemorySize(10, 10));
			MethodFrame * frame = new(address) MethodFrame(10, 10, NULL, NULL, NULL, NULL);

			baker->insert((Object*)frame);
		}

		void allocataGarbage(BakerGc * baker, int numAllocations, int arraySize)
		{
			for (int i = 0; i < numAllocations; i++)
			{
				unsigned char* address = baker->allocateOnPermanentSpace(MethodFrame::getMemorySize(10, 10)); // allocate some garbage
				MethodFrame * frame = new(address) MethodFrame(10, 10, NULL, NULL, NULL, NULL);
			}
		}

		void allocateFinalizableGarbage(BakerGc * baker, int numAllocations, int arraySize, Class* aClass)
		{
			for (int i = 0; i < numAllocations; i++)
			{
				unsigned char* address = baker->allocateOnPermanentSpace(ArrayObject<Object*>::getMemorySize(arraySize)); // allocate some garbage
				ArrayObject<Object*> * obj = new(address) ArrayObject<Object*>(arraySize, NULL, aClass, NULL);
			}
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

		Runtime* allocateGarbageOnPermSpace(bool compacting = false)
		{
			// allocate object with 5 fields
			// allocate array -> store into object
			// allocate array, do not store anywher
			// .....
			// ....

			size_t initialMemorySize = 100 * 1024;
			size_t totalMemorySize = initialMemorySize;

			Runtime * runtime = this->prepare();
			BakerGc* baker = (BakerGc*)runtime->heap;

			size_t methodFrameSize = MethodFrame::getMemorySize(1, 1);
			totalMemorySize -= methodFrameSize;
			MethodFrame * frame = new(baker->allocateOnPermanentSpace(methodFrameSize)) MethodFrame(1, 1);
			baker->insert(frame);


			size_t objectSize = Object::getMemorySize(5);
			totalMemorySize -= objectSize;
			Object * object = new (baker->allocateOnPermanentSpace(objectSize)) Object(5, java::lang::Object::initialize());
			frame->localVariables->set(0, baker->insert(object));

			int i = 0;
			int index = 0;
			int countObjectFields = 5;

			size_t arraySize = ArrayObject<double>::getMemorySize(100); // 820 B

			for (int i = 0; i < 10; i++)
			{
				ArrayObject<double> * arrayObject = new(baker->allocateOnPermanentSpace(arraySize)) ArrayObject<double>(100, 0.0, java::lang::Array::initialize(runtime->classTable), nullptr);
				size_t key = baker->insert(arrayObject);

				if (!compacting && i++ % 2 == 0 && index < countObjectFields)
				{
					object->fields->set(index++, key);
				}
			}

			baker->fullCollect();

			// TEST FREE LIST NOW 
			return runtime;
		}
		
		TEST_METHOD(testCompacting)
		{
			Runtime* runtime = this->allocateGarbageOnPermSpace();
			BakerGc* baker = (BakerGc*)runtime->heap;

			baker->fullCollect();
		}

		TEST_METHOD(testNonCompactingCollection)
		{
			// allocate object with 5 fields
			// allocate array -> store into object
			// allocate array, do not store anywher
			// .....
			// ....
			Runtime* runtime = this->allocateGarbageOnPermSpace(true);
			BakerGc* baker = (BakerGc*)runtime->heap;

			baker->fullCollect();

			int expectedFreeListItems = 5;
			int freeListItems = 0;

			
			
		}

	};
}