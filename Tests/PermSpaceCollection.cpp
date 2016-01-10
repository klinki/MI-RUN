#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"
#include "../JVM/natives/java/lang/Object.h"
#include "../JVM/natives/java/lang/Array.h"
#include "../JVM/gc/PermSpaceHeap.h"

namespace Tests
{
	int finalizationCalled = 0;
	void testFinalizationCalled(Object* obj, ExecutionEngine* engine)
	{
		finalizationCalled++;
	}

	TEST_CLASS(PermSpaceCollection)
	{
	public:
		Runtime * prepare(size_t youngSize = 10 * 1024, size_t oldSize = 10 * 1024)
		{
			Runtime* runtime = new Runtime();
			runtime->executionEngine = new ExecutionEngine();
			BakerGc * baker = new BakerGc(youngSize, oldSize);
			baker->runtime = runtime;
			runtime->objectTable = baker;
			runtime->heap = baker;
			runtime->classTable = new ClassMap();
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

			//Assert::AreEqual(3, finalizationCalled);
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
			size_t methodFrameRef = baker->insert(frame);

			runtime->executionEngine->callStack->pushReference(methodFrameRef);

			size_t objectSize = Object::getMemorySize(5);
			totalMemorySize -= objectSize;
			Object * object = new (baker->allocateOnPermanentSpace(objectSize)) Object(5, java::lang::Object::initialize());
			frame->localVariables->set(0, makeReferenceAddress(baker->insert(object)));

			int i = 0;
			int index = 0;
			int countObjectFields = 5;

			size_t arraySize = ArrayObject<double>::getMemorySize(100); // 820 B

			for (int i = 0; i < 10; i++)
			{
				ArrayObject<double> * arrayObject = new(baker->allocateOnPermanentSpace(arraySize)) ArrayObject<double>(100, 0.0, java::lang::Array::initialize(runtime->classTable), nullptr);
				size_t key = baker->insert(arrayObject);
				totalMemorySize -= arraySize;


				if (!compacting && i % 2 == 0 && index < countObjectFields)
				{
					object->fields->set(index++, makeReferenceAddress(key));
				}
			}

			return runtime;
		}
		
		TEST_METHOD(testCompacting)
		{
			Runtime* runtime = this->allocateGarbageOnPermSpace(true);
			BakerGc* baker = (BakerGc*)runtime->heap;

			baker->fullCollect();

			int expectedSize = 10 * 1024 - MethodFrame::getMemorySize(1, 1) - Object::getMemorySize(5) - 2 * sizeof(MemoryHeader) - 12; // padding for object 
			int result = baker->permanentSpace->freeList->size;

//			Assert::AreEqual(expectedSize, result);
		}

		TEST_METHOD(testNonCompactingCollection)
		{
			// allocate object with 5 fields
			// allocate array -> store into object
			// allocate array, do not store anywher
			// .....
			// ....
			Runtime* runtime = this->allocateGarbageOnPermSpace(false);
			BakerGc* baker = (BakerGc*)runtime->heap;

			baker->fullCollect();

			int expectedFreeListItems = 5;
			int freeListItems = 0;
			int freeSpace = 0;

			PermSpaceHeap::FreeListHeader * freeList = baker->permanentSpace->freeList;


			do
			{
				freeListItems++;
				freeSpace += freeList->size;

				freeList = freeList->right;
			} while (freeList != baker->permanentSpace->freeList);

			//			Assert::AreEqual(6, freeListItems);
			//			Assert::AreEqual(6 * 848, freeSpace);
			//			Assert::AreEqual(baker->permanentSpace->allocatedBytes - baker->permanentSpace->usedBytes, freeSpace);

		}
	};
}
