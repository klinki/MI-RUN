#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(FloatTest)
	{
	public:
		TEST_METHOD(testFMUL)
		{
			ExecutionEngine eng;
			Method m;

			float a[] = { 3.14, 0, 1, -1, -1, INT_MAX, ULLONG_MAX,  1.012 };
			float b[] = { INFINITY, 0, INFINITY, INFINITY, -INFINITY, INT_MAX, ULLONG_MAX, 1.012 };

			for (int i = 0; i < 8; i++)
			{
				float expected = a[i] * b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::FMUL;
				m.byteCodeLength = 1;

				MethodFrame frm(2, 2);
				frm.operandStack->push(a[i]);
				frm.operandStack->push(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				float result = frm.operandStack->pop();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testFDivByZeroPositive)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::FDIV;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.operandStack->push(1);
			frm.operandStack->push(0);

			frm.pc = 0;
			frm.method = &m;
			eng.execute(&frm);

			float expected = INFINITY;

			float result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testFDivByZeroNegative)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::FDIV;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.operandStack->push(-1.0f);
			frm.operandStack->push(0.0f);

			frm.pc = 0;
			frm.method = &m;
			eng.execute(&frm);

			float expected = -INFINITY;

			float result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testFDIV)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::FDIV;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.operandStack->push(1.0f);
			frm.operandStack->push(3.0f);

			frm.pc = 0;
			frm.method = &m;
			eng.execute(&frm);

			float expected = 1.0 / 3.0;

			float result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testFREM)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::FREM;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.operandStack->push(10.0f);
			frm.operandStack->push(3.0f);

			frm.pc = 0;
			frm.method = &m;
			eng.execute(&frm);

			float expected = fmodf(10.0, 3.0);

			float result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testFRemByZero)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::FREM;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.operandStack->push(1.0f);
			frm.operandStack->push(0.0f);

			frm.pc = 0;
			frm.method = &m;
			eng.execute(&frm);

			float result = frm.operandStack->pop();
			Assert::IsTrue(isnan(result));
		}

		TEST_METHOD(testFADD)
		{
			ExecutionEngine eng;
			Method m;

			float a[] = { 1, 1, -1, 3.14, 3.14, INT_MAX, INT_MAX,  +0.0, -0.0 };
			float b[] = { -0.0, 1, -1, 3.14, -3.14, -INT_MAX, INT_MAX, -0.0, +0.0 };

			for (int i = 0; i < 9; i++)
			{
				float expected = a[i] + b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::FADD;
				m.byteCodeLength = 1;

				MethodFrame frm(2, 2);
				frm.operandStack->push(a[i]);
				frm.operandStack->push(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				float result = frm.operandStack->pop();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testAddSpecial)
		{
			ExecutionEngine eng;
			Method m;

			float a[] = {  INFINITY, -INFINITY };
			float b[] = { INFINITY, -INFINITY };

			for (int i = 0; i < 3; i++)
			{
				float expected = a[i] + b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::FADD;
				m.byteCodeLength = 1;

				MethodFrame frm(2, 2);
				frm.operandStack->push(a[i]);
				frm.operandStack->push(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				float result = frm.operandStack->pop();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testFSUB)
		{
			ExecutionEngine eng;
			Method m;

			float a[] = { 1, 1, -1, 3.14, 3.14, INT_MAX, INT_MAX, +0.0, -0.0 };
			float b[] = { -0.0, 1, -1, 3.14, -3.14, -INT_MAX, INT_MAX, +0.0, -0.0 };

			for (int i = 0; i < 9; i++)
			{
				float expected = a[i] - b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::FSUB;
				m.byteCodeLength = 1;

				MethodFrame frm(2, 2);
				frm.operandStack->push(a[i]);
				frm.operandStack->push(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				float result = frm.operandStack->pop();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testFSUBInf)
		{
			ExecutionEngine eng;
			Method m;

			float a[] = { INFINITY, -INFINITY };
			float b[] = { -INFINITY, INFINITY };

			for (int i = 0; i < 2; i++)
			{
				float expected = a[i] - b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::FSUB;
				m.byteCodeLength = 1;

				MethodFrame frm(4, 4);
				frm.operandStack->push(a[i]);
				frm.operandStack->push(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				float result = frm.operandStack->pop();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testFNEG)
		{
			ExecutionEngine eng;
			Method m;

			float a[] = { 1, -1, INFINITY, -INFINITY, +0.0, -0.0};
			
			for (int i = 0; i < 6; i++)
			{
				float expected = -a[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::FNEG;
				m.byteCodeLength = 1;

				MethodFrame frm(2, 2);
				frm.operandStack->push(a[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				float result = frm.operandStack->pop();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testFNEGspecial)
		{
			ExecutionEngine eng;
			Method m;

			float a = NAN;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::FNEG;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.operandStack->push(a);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			float result = frm.operandStack->pop();
			Assert::IsTrue(isnan(result));
		}
	};
}
