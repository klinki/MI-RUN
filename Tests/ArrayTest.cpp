#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\JVM\runtime\MethodArea.h"
#include "../JVM/runtime/ExecutionEngine.h"
#include "../JVM/runtime/TypeDescriptors.h"

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

		TEST_METHOD(invalidAllocation)
		{

		}


		TEST_METHOD(arraySize)
		{
		}


		TEST_METHOD(arraySizeNullPtrException)
		{
		}
	};
}
