#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(LongTest)
	{
	public:
		TEST_METHOD(testLMUL)
		{
			ExecutionEngine eng;
			Method m;

			int a[] = { 0, 1, -1, INT_MAX, -1, INT_MIN, SHRT_MAX, USHRT_MAX };
			int b[] = { 0, 1, -1, INT_MAX, INT_MAX, INT_MIN, SHRT_MAX, USHRT_MAX };

			for (int i = 0; i < 8; i++)
			{
				int expected = a[i] * b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::LMUL;
				m.byteCodeLength = 1;

				MethodFrame frm(2, 2, true);
				frm.operandStack->push(a[i]);
				frm.operandStack->push(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				int result = frm.operandStack->pop();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testLDivByZero)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::LDIV;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2, true);
			frm.operandStack->push(1);
			frm.operandStack->push(0);

			frm.pc = 0;
			frm.method = &m;

			auto callback = [&eng, &frm] { eng.execute(&frm); };
			Assert::ExpectException<Exceptions::Runtime::ArithmeticException>(callback);
		}

		TEST_METHOD(testLDIV)
		{

		}


		TEST_METHOD(testLREM)
		{

		}


		TEST_METHOD(testLRemByZero)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::LREM;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2, true);
			frm.operandStack->push(1);
			frm.operandStack->push(0);

			frm.pc = 0;
			frm.method = &m;

			auto callback = [&eng, &frm] { eng.execute(&frm); };
			Assert::ExpectException<Exceptions::Runtime::ArithmeticException>(callback);
		}

		TEST_METHOD(testLADD)
		{
		}

		TEST_METHOD(testLSUB)
		{
		}

		TEST_METHOD(testLNEG)
		{
		}

		TEST_METHOD(testLSHL)
		{
		}

		TEST_METHOD(testLSHR)
		{
		}

		TEST_METHOD(testLUSHR)
		{
		}

		TEST_METHOD(testLAND)
		{
		}

		TEST_METHOD(testLOR)
		{
		}

		TEST_METHOD(testLXOR)
		{
		}

		TEST_METHOD(testLINC)
		{
			ExecutionEngine eng;
			Method m;

			long long expected = UINT_MAX + 255LL;
			int increment = 255;
			int value = expected - increment;
			int index = 0;

			m.byteCode = new Instruction[3];
			m.byteCode[0] = (Instruction)InstructionSet::IINC;
			m.byteCode[1] = index;
			m.byteCode[2] = increment;
			m.byteCodeLength = 3;

			MethodFrame frm(1, 1, true);
			frm.pc = 0;
			(*frm.localVariables)[0] = highWord(expected);
			(*frm.localVariables)[1] = lowWord(expected);

			frm.method = &m;

			eng.execute(&frm);

			unsigned int high = (*frm.localVariables)[0];
			unsigned int low = (*frm.localVariables)[1]; 

			long long result = longFromStack(high, low);
			Assert::AreEqual(expected, result);
		}

	};
}
