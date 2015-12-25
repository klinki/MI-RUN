#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/MethodArea.h"
#include "../JVM/runtime/ExecutionEngine.h"
#include "../JVM/runtime/TypeDescriptors.h"
#include "../JVM/gc/interfaces/ObjectVisitorInterface.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(ArrayTest)
	{
	public:
		template <class T>
		ArrayObject<T>* allocateArray(ArrayType type, size_t arraySize)
		{
			ExecutionEngine * eng = new ExecutionEngine();
			eng->heap = new Heap();
			eng->objectTable = new ObjectTable();
			Method m;

			m.byteCode = new Instruction[2];
			m.byteCode[0] = (Instruction)InstructionSet::NEWARRAY;
			m.byteCode[1] = (Instruction)type;
			m.byteCodeLength = 2;

			MethodFrame frm(2, 2);
			frm.operandStack->push(arraySize);

			frm.pc = 0;
			frm.method = &m;

			eng->execute(&frm);

			int result = frm.operandStack->pop();

			Assert::AreNotEqual(0, result);
			Assert::AreEqual(1, result);

			ArrayObject<T> * objectPtr = (ArrayObject<T> *) eng->objectTable->get(result);

			return objectPtr;
		}

		template <class T>
		void checkAllocatedValues(ArrayObject<T> * objectPtr, size_t arraySize, T expectedValue)
		{
			int* intPtr = (int*)objectPtr;
			intPtr += 2; // virtual table
			T* typePtr = (T*)(intPtr + 3);
			

			for (int i = 0; i < arraySize; i++)
			{
				Assert::AreEqual(expectedValue, typePtr[i]);
			}
		}

		template <class T>
		void checkProperties(ArrayObject<T> * objectPtr, int size, Class* expClass)
		{
			int* intPtr = (int*)objectPtr;
			intPtr += 2; // virtual table

			Assert::AreEqual((int)expClass, (int)*intPtr);
			Assert::AreEqual(size, intPtr[1]);
			Assert::AreEqual((int)(intPtr + 3), intPtr[2]);
		}

		template <class T>
		void testArrayType(ArrayType type, size_t arraySize, T defaultValue)
		{
			ArrayObject<T>* objPtr = this->allocateArray<T>(type, arraySize);
			this->checkProperties(objPtr, arraySize, NULL);
			this->checkAllocatedValues(objPtr, arraySize, defaultValue);
		}


		TEST_METHOD(allocateArray)
		{
			int arraySize = 10;
			this->testArrayType<bool>(ArrayType::T_BOOLEAN, 10, false);
			this->testArrayType<java_byte>(ArrayType::T_BYTE, 10, 0);
			this->testArrayType<java_char>(ArrayType::T_CHAR, 10, '\u0000');
			this->testArrayType<java_double>(ArrayType::T_DOUBLE, 10, +0.0);
			this->testArrayType<java_float>(ArrayType::T_FLOAT, 10, +0.0);
			this->testArrayType<java_int>(ArrayType::T_INT, 10, 0);
			this->testArrayType<java_long>(ArrayType::T_LONG, 10, 0);
			this->testArrayType<java_short>(ArrayType::T_SHORT, 10, 0);
		}

		TEST_METHOD(invalidArrayAllocation)
		{
			ExecutionEngine * eng = new ExecutionEngine();
			eng->heap = new Heap();
			eng->objectTable = new ObjectTable();
			Method m;

			m.byteCode = new Instruction[2];
			m.byteCode[0] = (Instruction)InstructionSet::NEWARRAY;
			m.byteCode[1] = (Instruction)ArrayType::T_INT;
			m.byteCodeLength = 2;

			MethodFrame frm(2, 2);
			frm.operandStack->push(-1);

			frm.pc = 0;
			frm.method = &m;

			auto callback = [&eng, &frm] { eng->execute(&frm); };
			Assert::ExpectException<Exceptions::Runtime::NegativeArraySizeException>(callback);
		}


		template <class T>
		ObjectTable * getObjectTableWithArray(int size, T defaultValue, HeapInterface * heap)
		{
			unsigned char* address = heap->allocate(ArrayObject<T>::getMemorySize(size));
			ArrayObject<T> * arrayObject = new(address) ArrayObject<T>(size, defaultValue, NULL, NULL);
			ObjectTable * table = new ObjectTable();
			table->insert((Object*)arrayObject);

			return table;
		}
		
		TEST_METHOD(arraySize)
		{
			int arraySize = 10;

			ExecutionEngine eng;
			eng.heap = new Heap();
			eng.objectTable = this->getObjectTableWithArray<int>(arraySize, 0, eng.heap);
			Method m;

			int arrayIndex = 1;

			m.byteCode = new Instruction[2];
			m.byteCode[0] = (Instruction)InstructionSet::ARRAYLENGTH;
			m.byteCodeLength = 1;

			MethodFrame frm(1, 1);
			frm.operandStack->push(arrayIndex);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();

			Assert::AreEqual(arraySize, result);
		}


		TEST_METHOD(arraySizeNullPtrException)
		{
			int arraySize = 10;

			ExecutionEngine eng;
			eng.heap = new Heap();
			eng.objectTable = this->getObjectTableWithArray<int>(arraySize, 0, eng.heap);
			Method m;

			int arrayIndex = 1;

			m.byteCode = new Instruction[2];
			m.byteCode[0] = (Instruction)InstructionSet::ARRAYLENGTH;
			m.byteCodeLength = 1;

			MethodFrame frm(1, 1);
			frm.operandStack->push(0);

			frm.pc = 0;
			frm.method = &m;

			auto callback = [&eng, &frm] { eng.execute(&frm); };

			Assert::ExpectException<Exceptions::Runtime::NullPointerException>(callback);
		}

		TEST_METHOD(arrayStore)
		{
			long long value = UINT_MAX + 1024;
			int arraySize = 10;

			ExecutionEngine eng;
			eng.heap = new Heap();
			eng.objectTable = this->getObjectTableWithArray<long long>(arraySize, 0, eng.heap);
			Method m;

			int arrayIndex = 9;
			int arrPtr = 1;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::LASTORE;
			m.byteCodeLength = 1;

			MethodFrame frm(6, 6);
			frm.operandStack->push(arrPtr);
			frm.operandStack->push(arrayIndex);
			frm.operandStack->push2(value);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			ArrayObject<long long> * ptr = (ArrayObject<long long>*) eng.objectTable->get(1);
			long long result = ptr->operator[](arrayIndex);

			Assert::AreEqual(value, result);
		}

		TEST_METHOD(arrayLoad)
		{
			double value = 3.14;
			int arraySize = 10;

			ExecutionEngine eng;
			eng.heap = new Heap();
			eng.objectTable = this->getObjectTableWithArray<double>(arraySize, value, eng.heap);
			Method m;

			int arrayIndex = 1;

			m.byteCode = new Instruction[2];
			m.byteCode[0] = (Instruction)InstructionSet::DALOAD;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.operandStack->push(arrayIndex);
			frm.operandStack->push(9);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			double result = frm.operandStack->pop2();

			Assert::AreEqual(value, result);
		}

		TEST_METHOD(allocateMultiDimensionalArray)
		{
			ExecutionEngine * eng = new ExecutionEngine();
			eng->heap = new Heap();
			eng->objectTable = new ObjectTable();
			Method m;

			m.byteCode = new Instruction[4];
			m.byteCode[0] = (Instruction)InstructionSet::MULTIANEWARRAY;
			m.byteCode[1] = 0;
			m.byteCode[2] = 0;
			m.byteCode[3] = 3;
			m.byteCodeLength = 4;

			MethodFrame frm(3, 3);
			frm.operandStack->push(2);
			frm.operandStack->push(3);
			frm.operandStack->push(4);


			frm.pc = 0;
			frm.method = &m;

			eng->execute(&frm);

			int result = frm.operandStack->pop();

			ArrayObject<Object*> * objectPtr = (ArrayObject<Object*> *) eng->objectTable->get(result);

			Assert::AreEqual(4, (int)objectPtr->getSize());

			for (int i = 0; i < 4; i++)
			{
				int index = (int)(*objectPtr)[i];
				ArrayObject<Object*> * innerPtr = (ArrayObject<Object*> *) eng->objectTable->get(index);

				for (int j = 0; j < 3; j++)
				{
					int index2 = (int)(*innerPtr)[j];
					ArrayObject<Object*> * inner2Ptr = (ArrayObject<Object*> *) eng->objectTable->get(index2);

					Assert::AreEqual(2, (int)inner2Ptr->getSize());
				}

				Assert::AreEqual(3, (int)innerPtr->getSize());
			}
		}
	};
}
