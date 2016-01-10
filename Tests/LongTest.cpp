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
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			long long a[] = { 0, 1, -1, LLONG_MAX, -1, LLONG_MIN, INT_MAX, UINT_MAX};
			long long b[] = { 0, 1, -1, LLONG_MAX, LLONG_MAX, LLONG_MIN, INT_MAX, UINT_MAX };

			for (long long i = 0; i < 8; i++)
			{
				long long expected = a[i] * b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::LMUL;
				m.byteCodeLength = 1;

				MethodFrame frm(4, 4);
				frm.operandStack->push2(a[i]);
				frm.operandStack->push2(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				long long result = frm.operandStack->pop2();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testLDivByZero)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::LDIV;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.operandStack->push2(1LL);
			frm.operandStack->push2(0LL);

			frm.pc = 0;
			frm.method = &m;

			auto callback = [&eng, &frm] { eng.execute(&frm); };
			Assert::ExpectException<Exceptions::Runtime::ArithmeticException>(callback);
		}

		TEST_METHOD(testLDIV)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::LDIV;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.operandStack->push2(100LL);
			frm.operandStack->push2(3LL);

			frm.pc = 0;
			frm.method = &m;
			eng.execute(&frm);

			long long expected = 100 / 3;

			long long result = frm.operandStack->pop2();
			Assert::AreEqual(expected, result);
		}


		TEST_METHOD(testLREM)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::LREM;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.operandStack->push2(100LL);
			frm.operandStack->push2(3LL);

			frm.pc = 0;
			frm.method = &m;
			eng.execute(&frm);

			long long expected = 100 % 3;

			long long result = frm.operandStack->pop2();
			Assert::AreEqual(expected, result);
		}


		TEST_METHOD(testLRemByZero)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::LREM;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.operandStack->push2(1LL);
			frm.operandStack->push2(0LL);

			frm.pc = 0;
			frm.method = &m;

			auto callback = [&eng, &frm] { eng.execute(&frm); };
			Assert::ExpectException<Exceptions::Runtime::ArithmeticException>(callback);
		}

		TEST_METHOD(testLADD)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			long long a[] = { 0, 1, -1, INT_MAX, -1, INT_MIN, SHRT_MAX, USHRT_MAX };
			long long b[] = { 0, -1, 1, INT_MIN, INT_MAX, INT_MIN, SHRT_MAX, USHRT_MAX };

			for (long long i = 0; i < 8; i++)
			{
				long long expected = a[i] + b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::LADD;
				m.byteCodeLength = 1;

				MethodFrame frm(4, 4);
				frm.operandStack->push2(a[i]);
				frm.operandStack->push2(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				long long result = frm.operandStack->pop2();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testLSUB)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			long long a[] = { 0, 1, -1, INT_MAX, -1, INT_MIN, SHRT_MAX, USHRT_MAX };
			long long b[] = { 0, -1, 1, INT_MIN, INT_MAX, INT_MIN, SHRT_MAX, USHRT_MAX };

			for (long long i = 0; i < 8; i++)
			{
				long long expected = a[i] - b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::LSUB;
				m.byteCodeLength = 1;

				MethodFrame frm(4, 4);
				frm.operandStack->push2(a[i]);
				frm.operandStack->push2(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				long long result = frm.operandStack->pop2();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testLNEG)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			long long a[] = { 1, -1, INT_MAX, INT_MIN };

			for (long long i = 0; i < 32; i++)
			{
				long long expected = -i;

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::LNEG;
				m.byteCodeLength = 1;

				MethodFrame frm(4, 4);
				frm.operandStack->push2(a[i]);
				frm.operandStack->push2(i);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				long long result = frm.operandStack->pop2();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testLSHL)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			long long a = 1;

			for (long long i = 0; i < 64; i++)
			{
				long long expected = a << i;

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::LSHL;
				m.byteCodeLength = 1;

				MethodFrame frm(4, 4);
				frm.operandStack->push2(a);
				frm.operandStack->push((int)i);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				long long result = frm.operandStack->pop2();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testLSHR)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			long long a = 1 << 64;

			for (long long i = 0; i < 64; i++)
			{
				long long expected = a >> i;

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::LSHR;
				m.byteCodeLength = 1;

				MethodFrame frm(4, 4);
				frm.operandStack->push2(a);
				frm.operandStack->push2(i);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				long long result = frm.operandStack->pop2();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testLUSHR)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			long long a = 1 << 64;

			for (long long i = 0; i < 64; i++)
			{
				long long expected = a >> i;

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::LSHR;
				m.byteCodeLength = 1;

				MethodFrame frm(4, 4);
				frm.operandStack->push2(a);
				frm.operandStack->push2(i);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				long long result = frm.operandStack->pop2();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testLAND)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			long long a = LLONG_MAX;;

			for (long long i = 0; i < 64; i++)
			{
				long long expected = a & (a >> i);

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::LAND;
				m.byteCodeLength = 1;

				MethodFrame frm(4, 4);
				frm.operandStack->push2(a);
				frm.operandStack->push2(a >> i);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				long long result = frm.operandStack->pop2();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testLOR)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			long long a = 0x0BAFBAF;
			long long b = 0xEEAABBEE;

			long long expected = a | b;
			long long index = 0;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::LOR;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.pc = 0;
			frm.operandStack->push2(a);
			frm.operandStack->push2(b);
			frm.method = &m;

			eng.execute(&frm);

			long long result = frm.operandStack->pop2();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testLXOR)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();
			long long a = 0x0BAFBAF;
			long long b = 0xEEAABBEE;

			long long expected = a ^ b;
			long long index = 0;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::LXOR;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.pc = 0;
			frm.operandStack->push2(a);
			frm.operandStack->push2(b);
			frm.method = &m;

			eng.execute(&frm);

			long long result = frm.operandStack->pop2();
			Assert::AreEqual(expected, result);
		}
	};
}
