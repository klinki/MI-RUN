#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"
#include "../JVM/runtime/ExecutionEngine.h"
#include "../JVM/runtime/MethodFrame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(ConstTest)
	{
	public:

		TEST_METHOD(testACONST_NULL)
		{
			ExecutionEngine eng;
			Method m;
			m.byteCode = new Instruction[1];
			MethodFrame frm(1, 1);
			frm.method = &m;

			frm.pc = 0;
			int expected = 0;

			m.byteCode[0] = ACONST_NULL;
			m.byteCodeLength = 1;

			eng.execute(&frm);

			int result = frm.operandStack.pop();
			Assert::AreEqual(expected, result);

		}


		TEST_METHOD(testICONST)
		{
			ExecutionEngine eng;
			Method m;
			m.byteCode = new Instruction[1];
			MethodFrame frm(1, 1);
			frm.method = &m;

			Instruction instructions[] = { ICONST_M1, ICONST_0, ICONST_1, ICONST_2, ICONST_3, ICONST_4, ICONST_5 };
			int values[] = { -1, 0, 1, 2, 3, 4, 5 };

			for (int i = 0; i < 7; i++) 
			{
				frm.pc = 0;
				int expected = values[i];

				m.byteCode[0] = instructions[i];
				m.byteCodeLength = 1;

				eng.execute(&frm);

				int result = frm.operandStack.pop();
				Assert::AreEqual(expected, result);
			}
		}


		TEST_METHOD(testFCONST)
		{
			ExecutionEngine eng;
			Method m;
			m.byteCode = new Instruction[1];
			MethodFrame frm(1, 1);
			frm.method = &m;

			Instruction instructions[] = { FCONST_0, FCONST_1, FCONST_2 };
			int values[] = { 0, 1, 2 };

			for (int i = 0; i < 3; i++)
			{
				frm.pc = 0;
				float expected = values[i];

				m.byteCode[0] = instructions[i];
				m.byteCodeLength = 1;

				eng.execute(&frm);

				float result = frm.operandStack.pop();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testLCONST)
		{
			ExecutionEngine eng;
			Method m;
			m.byteCode = new Instruction[1];
			MethodFrame frm(2, 2);
			frm.method = &m;

			Instruction instructions[] = { LCONST_0, LCONST_1 };
			long long values[] = { 0, 1 };

			for (int i = 0; i < 2; i++)
			{
				frm.pc = 0;
				long long expected = values[i];

				m.byteCode[0] = instructions[i];
				m.byteCodeLength = 1;

				eng.execute(&frm);

				unsigned int low = frm.operandStack.pop();
				unsigned int high = frm.operandStack.pop();

				long long result = longFromStack(high, low);

				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testDCONST)
		{
			ExecutionEngine eng;
			Method m;
			m.byteCode = new Instruction[1];
			MethodFrame frm(2, 2);
			frm.method = &m;

			Instruction instructions[] = { DCONST_0, DCONST_1 };
			double values[] = { 0, 1 };

			for (int i = 0; i < 2; i++)
			{
				frm.pc = 0;
				double expected = values[i];

				m.byteCode[0] = instructions[i];
				m.byteCodeLength = 1;

				eng.execute(&frm);

				unsigned int low = frm.operandStack.pop();
				unsigned int high = frm.operandStack.pop();

				double result = doubleFromStack(high, low);

				Assert::AreEqual(expected, result);
			}
		}
	};
}
