#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(MulTest)
	{
	public:
		TEST_METHOD(testIMUL)
		{
			ExecutionEngine eng;
			Method m;

			int a[] = { 0, 1, -1, INT_MAX, -1, INT_MIN, SHRT_MAX, USHRT_MAX };
			int b[] = { 0, 1, -1, INT_MAX, INT_MAX, INT_MIN, SHRT_MAX, USHRT_MAX };

			for (int i = 0; i < 8; i++)
			{
				int expected = a[i] * b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::IMUL;
				m.byteCodeLength = 1;

				MethodFrame frm(2, 2);
				frm.operandStack->push(a[i]);
				frm.operandStack->push(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				int result = frm.operandStack->pop();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testIDivByZero)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::IDIV;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.operandStack->push(1);
			frm.operandStack->push(0);

			frm.pc = 0;
			frm.method = &m;

			auto callback = [&eng, &frm] { eng.execute(&frm); };
			Assert::ExpectException<Exceptions::Runtime::ArithmeticException>(callback);
		}

		TEST_METHOD(testIDIV)
		{

		}


		TEST_METHOD(testIREM)
		{

		}


		TEST_METHOD(testIRemByZero)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::IREM;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.operandStack->push(1);
			frm.operandStack->push(0);

			frm.pc = 0;
			frm.method = &m;

			auto callback = [&eng, &frm] { eng.execute(&frm); };
			Assert::ExpectException<Exceptions::Runtime::ArithmeticException>(callback);
		}

		TEST_METHOD(testIADD)
		{
		}

		TEST_METHOD(testISUB)
		{
		}

		TEST_METHOD(testINEG)
		{
		}



		TEST_METHOD(testISHL)
		{}

		TEST_METHOD(testISHR)
		{}

		TEST_METHOD(testIUSHR)
		{}

		TEST_METHOD(testIAND)
		{}

		TEST_METHOD(testIOR)
		{

		}

		TEST_METHOD(testIXOR)
		{}

		TEST_METHOD(testIINC)
		{}

	};
}
