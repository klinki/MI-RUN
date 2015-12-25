#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(IntTest)
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

		TEST_METHOD(testIDivByZero)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::IDIV;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2, true);
			frm.operandStack->push(1);
			frm.operandStack->push(0);

			frm.pc = 0;
			frm.method = &m;

			auto callback = [&eng, &frm] { eng.execute(&frm); };
			Assert::ExpectException<Exceptions::Runtime::ArithmeticException>(callback);
		}

		TEST_METHOD(testIDIV)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::IDIV;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2, true);
			frm.operandStack->push(100);
			frm.operandStack->push(3);

			frm.pc = 0;
			frm.method = &m;
			eng.execute(&frm);

			int expected = 100 / 3;

			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}


		TEST_METHOD(testIREM)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::IREM;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2, true);
			frm.operandStack->push(100);
			frm.operandStack->push(3);

			frm.pc = 0;
			frm.method = &m;
			eng.execute(&frm);

			int expected = 100 % 3;

			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}


		TEST_METHOD(testIRemByZero)
		{
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::IREM;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2, true);
			frm.operandStack->push(1);
			frm.operandStack->push(0);

			frm.pc = 0;
			frm.method = &m;

			auto callback = [&eng, &frm] { eng.execute(&frm); };
			Assert::ExpectException<Exceptions::Runtime::ArithmeticException>(callback);
		}

		TEST_METHOD(testIADD)
		{
			ExecutionEngine eng;
			Method m;

			int a[] = { 0, 1, -1, INT_MAX, -1, INT_MIN, SHRT_MAX, USHRT_MAX };
			int b[] = { 0, -1, 1, INT_MIN, INT_MAX, INT_MIN, SHRT_MAX, USHRT_MAX };

			for (int i = 0; i < 8; i++)
			{
				int expected = a[i] + b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::IADD;
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

		TEST_METHOD(testISUB)
		{
			ExecutionEngine eng;
			Method m;

			int a[] = { 0, 1, -1, INT_MAX, -1, INT_MIN, SHRT_MAX, USHRT_MAX };
			int b[] = { 0, -1, 1, INT_MIN, INT_MAX, INT_MIN, SHRT_MAX, USHRT_MAX };

			for (int i = 0; i < 8; i++)
			{
				int expected = a[i] - b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::ISUB;
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

		TEST_METHOD(testINEG)
		{
			ExecutionEngine eng;
			Method m;

			int a[] = { 1, -1, INT_MAX, INT_MIN };

			for (int i = 0; i < 32; i++)
			{
				int expected = -i;

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::INEG;
				m.byteCodeLength = 1;

				MethodFrame frm(2, 2, true);
				frm.operandStack->push(a[i]);
				frm.operandStack->push(i);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				int result = frm.operandStack->pop();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testISHL)
		{
			ExecutionEngine eng;
			Method m;

			int a = 1;

			for (int i = 0; i < 32; i++)
			{
				int expected = a << i;

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::ISHL;
				m.byteCodeLength = 1;

				MethodFrame frm(2, 2, true);
				frm.operandStack->push(a);
				frm.operandStack->push(i);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				int result = frm.operandStack->pop();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testISHR)
		{
			ExecutionEngine eng;
			Method m;

			int a = 1 << 32;

			for (int i = 0; i < 32; i++)
			{
				int expected = a >> i;

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::ISHR;
				m.byteCodeLength = 1;

				MethodFrame frm(2, 2, true);
				frm.operandStack->push(a);
				frm.operandStack->push(i);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				int result = frm.operandStack->pop();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testIUSHR)
		{
			ExecutionEngine eng;
			Method m;

			int a = 1 << 32;

			for (int i = 0; i < 32; i++)
			{
				int expected = a >> i;

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::ISHR;
				m.byteCodeLength = 1;

				MethodFrame frm(2, 2, true);
				frm.operandStack->push(a);
				frm.operandStack->push(i);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				int result = frm.operandStack->pop();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testIAND)
		{
			ExecutionEngine eng;
			Method m;

			int a = INT_MAX;

			for (int i = 0; i < 32; i++)
			{
				int expected = a & (a >> i);

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::IAND;
				m.byteCodeLength = 1;

				MethodFrame frm(2, 2, true);
				frm.operandStack->push(a);
				frm.operandStack->push(a >> i);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				int result = frm.operandStack->pop();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testIOR)
		{
			ExecutionEngine eng;
			Method m;

			int a = 0x0BAFBAF;
			int b = 0xEEAABBEE;

			int expected = a | b;
			int index = 0;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::IOR;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2, true);
			frm.pc = 0;
			frm.operandStack->push(a);
			frm.operandStack->push(b);
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testIXOR)
		{
			ExecutionEngine eng;
			Method m;
			int a = 0x0BAFBAF;
			int b = 0xEEAABBEE;

			int expected = a ^ b;
			int index = 0;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::IXOR;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2, true);
			frm.pc = 0;
			frm.operandStack->push(a);
			frm.operandStack->push(b);
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testIINC)
		{
			ExecutionEngine eng;
			Method m;

			int expected = 0x0BAFBAF;
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
			(*frm.localVariables)[0] = value;
			frm.method = &m;

			eng.execute(&frm);

			int result = (*frm.localVariables)[index];
			Assert::AreEqual(expected, result);
		}
	};
}
