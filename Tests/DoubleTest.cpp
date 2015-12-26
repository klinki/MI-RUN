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

			double a[] = { 3.14, 0, 1, -1, -1, NAN, INT_MAX, ULLONG_MAX,  1.012, 2 };
			double b[] = { INFINITY, 0, INFINITY, INFINITY, -INFINITY, -1, INT_MAX, ULLONG_MAX, 1.012, NAN };

			for (int i = 0; i < 10; i++)
			{
				double expected = a[i] * b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::DMUL;
				m.byteCodeLength = 1;

				MethodFrame frm(4, 4);
				frm.operandStack->push2(a[i]);
				frm.operandStack->push2(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				double result = frm.operandStack->pop2();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testDDivByZeroPositive)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DDIV;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.operandStack->push2(1.0);
			frm.operandStack->push2(0.0);

			frm.pc = 0;
			frm.method = &m;
			eng.execute(&frm);

			double expected = INFINITY;

			double result = frm.operandStack->pop2();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testDDivByZeroNegative)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DDIV;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.operandStack->push2(-1.0);
			frm.operandStack->push2(0.0);

			frm.pc = 0;
			frm.method = &m;
			eng.execute(&frm);

			double expected = -INFINITY;

			double result = frm.operandStack->pop2();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testDDIV)
		{

			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DDIV;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.operandStack->push2(1.0);
			frm.operandStack->push2(3.0);

			frm.pc = 0;
			frm.method = &m;
			eng.execute(&frm);

			double expected = 1.0 / 3.0;

			double result = frm.operandStack->pop2();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testDREM)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DDIV;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.operandStack->push2(10.0);
			frm.operandStack->push2(3.0);

			frm.pc = 0;
			frm.method = &m;
			eng.execute(&frm);

			double expected = 10 / 3;

			double result = frm.operandStack->pop2();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testDRemByZero)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DREM;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.operandStack->push2(1.0);
			frm.operandStack->push2(0.0);

			frm.pc = 0;
			frm.method = &m;
			eng.execute(&frm);

			double expected = INFINITY;

			double result = frm.operandStack->pop2();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testDADD)
		{
			ExecutionEngine eng;
			Method m;

			double a[] = { 1, 1, -1, 3.14, 3.14, INT_MAX, INT_MAX,  +0.0, -0.0 };
			double b[] = { -0.0, 1, -1, 3.14, -3.14, -INT_MAX, INT_MAX, -0.0, +0.0 };

			for (int i = 0; i < 9; i++)
			{
				double expected = a[i] + b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::DADD;
				m.byteCodeLength = 1;

				MethodFrame frm(4, 4);
				frm.operandStack->push2(a[i]);
				frm.operandStack->push2(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				double result = frm.operandStack->pop2();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testAddSpecial)
		{
			ExecutionEngine eng;
			Method m;

			double a[] = { INFINITY, -INFINITY, INFINITY, NAN };
			double b[] = { INFINITY, -INFINITY, -INFINITY, NAN };

			for (int i = 0; i < 4; i++)
			{
				double expected = a[i] + b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::DADD;
				m.byteCodeLength = 1;

				MethodFrame frm(4, 4);
				frm.operandStack->push2(a[i]);
				frm.operandStack->push2(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				double result = frm.operandStack->pop2();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testDSUB)
		{
			ExecutionEngine eng;
			Method m;

			double a[] = { 1, 1, -1, 3.14, 3.14, INT_MAX, INT_MAX, +0.0, -0.0 };
			double b[] = { -0.0, 1, -1, 3.14, -3.14, -INT_MAX, INT_MAX, +0.0, -0.0 };

			for (int i = 0; i < 9; i++)
			{
				double expected = a[i] - b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::DSUB;
				m.byteCodeLength = 1;

				MethodFrame frm(4, 4);
				frm.operandStack->push2(a[i]);
				frm.operandStack->push2(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				double result = frm.operandStack->pop2();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testDSUBNaN)
		{
			ExecutionEngine eng;
			Method m;

			double a[] = { INFINITY, -INFINITY, INFINITY,  NAN };
			double b[] = { INFINITY, -INFINITY, -INFINITY, NAN };

			for (int i = 0; i < 13; i++)
			{
				double expected = a[i] - b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::DSUB;
				m.byteCodeLength = 1;

				MethodFrame frm(4, 4);
				frm.operandStack->push2(a[i]);
				frm.operandStack->push2(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				double result = frm.operandStack->pop2();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testDNEG)
		{
			ExecutionEngine eng;
			Method m;

			double a[] = { 1, -1, INFINITY, -INFINITY, +0.0, -0.0 };

			for (int i = 0; i < 6; i++)
			{
				double expected = -a[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::DNEG;
				m.byteCodeLength = 1;

				MethodFrame frm(4, 4);
				frm.operandStack->push2(a[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				double result = frm.operandStack->pop2();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testDNEGspecial)
		{
			ExecutionEngine eng;
			Method m;

			double a = NAN;

			double expected = -NAN;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DNEG;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.operandStack->push2(a);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			double result = frm.operandStack->pop2();
			Assert::AreEqual(expected, result);
		}
	};
}
