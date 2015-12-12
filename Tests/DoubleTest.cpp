#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(DoubleTest)
	{
	public:
		TEST_METHOD(testDMUL)
		{
			ExecutionEngine eng;
			Method m;

			int a[] = { 0, 1, -1, INT_MAX, -1, INT_MIN, SHRT_MAX, USHRT_MAX };
			int b[] = { 0, 1, -1, INT_MAX, INT_MAX, INT_MIN, SHRT_MAX, USHRT_MAX };

			for (int i = 0; i < 8; i++)
			{
				int expected = a[i] * b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::DMUL;
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

		TEST_METHOD(testDDivByZero)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DDIV;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.operandStack->push(1);
			frm.operandStack->push(0);

			frm.pc = 0;
			frm.method = &m;

			auto callback = [&eng, &frm] { eng.execute(&frm); };
			Assert::ExpectException<Exceptions::Runtime::ArithmeticException>(callback);
		}

		TEST_METHOD(testDDIV)
		{

		}


		TEST_METHOD(testDREM)
		{

		}


		TEST_METHOD(testDRemByZero)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DREM;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.operandStack->push(1);
			frm.operandStack->push(0);

			frm.pc = 0;
			frm.method = &m;

			auto callback = [&eng, &frm] { eng.execute(&frm); };
			Assert::ExpectException<Exceptions::Runtime::ArithmeticException>(callback);
		}

		TEST_METHOD(testDADD)
		{
		}

		TEST_METHOD(testDSUB)
		{
		}

		TEST_METHOD(testDNEG)
		{
			
		}
	};
}
