#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\JVM\runtime\OperandStack.h"
#include "..\JVM\runtime\ExecutionEngine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(TestConverions)
	{
	public:
		TEST_METHOD(I2L)
		{
			ExecutionEngine eng;
			Method m;

			int value = 0x0BAFBAF;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::I2L;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(value);
			frm.method = &m;

			eng.execute(&frm);

			int low = frm.operandStack->pop();
			int high = frm.operandStack->pop();
			long long result = longFromStack(high, low);

			long long expected = value;

			Assert::AreEqual(expected, result);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(I2B)
		{
			ExecutionEngine eng;
			Method m;

			int value = 0x0BAFBAF;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::I2B;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(value);
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			int expected = (java_byte)value;

			Assert::AreEqual(expected, result);
			Assert::AreEqual(expected, result);
		}


		TEST_METHOD(I2C)
		{
			ExecutionEngine eng;
			Method m;

			int value = 0x0BAFBAF;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::I2C;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(value);
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			int expected = (java_char)value;

			Assert::AreEqual(expected, result);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(I2S)
		{
			ExecutionEngine eng;
			Method m;

			int value = 0x0BAFBAF;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::I2S;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(value);
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			int expected = (java_short)value;

			Assert::AreEqual(expected, result);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(I2F)
		{
			ExecutionEngine eng;
			Method m;

			int value = 0x0BAFBAF;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::I2F;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(value);
			frm.method = &m;

			eng.execute(&frm);

			float result = frm.operandStack->pop();
			float expected = (float)value;

			Assert::AreEqual(expected, result);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(I2D)
		{
			ExecutionEngine eng;
			Method m;

			int value = 0x0BAFBAF;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::I2D;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(value);
			frm.method = &m;

			eng.execute(&frm);

			int low = frm.operandStack->pop();
			int high = frm.operandStack->pop();
			double result = doubleFromStack(high, low);
			double expected = (double)value;

			Assert::AreEqual(expected, result);
			Assert::AreEqual(expected, result);
		}
	

		TEST_METHOD(F2D)
		{
			ExecutionEngine eng;
			Method m;

			float value = 3.14159265359F;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::F2D;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(value);
			frm.method = &m;

			eng.execute(&frm);

			int low = frm.operandStack->pop();
			int high = frm.operandStack->pop();
			double result = doubleFromStack(high, low);

			double expected = value;

			Assert::AreEqual(expected, result);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(F2I)
		{
			ExecutionEngine eng;
			Method m;

			float value = 3.14159265359F;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::F2I;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(value);
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			int expected = (int)value;

			Assert::AreEqual(expected, result);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(F2L)
		{
			ExecutionEngine eng;
			Method m;

			float value = (float)(INT_MAX) + 1;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::F2L;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(value);
			frm.method = &m;

			eng.execute(&frm);

			int low = frm.operandStack->pop();
			int high = frm.operandStack->pop();
			long long result = longFromStack(high, low);

			long long expected = (long long)value;

			Assert::AreEqual(expected, result);
			Assert::AreEqual(expected, result);
		}


		TEST_METHOD(D2I)
		{
			ExecutionEngine eng;
			Method m;

			double value = 3.14159265359;
			int high = highWord(value);
			int low = lowWord(value);

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::D2I;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(high);
			frm.operandStack->push(low);
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			int expected = (int)value;

			Assert::AreEqual(expected, result);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(D2L)
		{
			ExecutionEngine eng;
			Method m;

			double value = (double)INT_MAX + 3.14159265359;
			int high = highWord(value);
			int low = lowWord(value);

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::D2L;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(high);
			frm.operandStack->push(low);
			frm.method = &m;

			eng.execute(&frm);

			int resultLow = frm.operandStack->pop();
			int resultHigh = frm.operandStack->pop();
			long long result = longFromStack(resultHigh, resultLow);

			long long expected = (long long)value;

			Assert::AreEqual(expected, result);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(D2F)
		{
			ExecutionEngine eng;
			Method m;

			double value = 3.14159265359;
			int high = highWord(value);
			int low = lowWord(value);

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::D2F;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(high);
			frm.operandStack->push(low);
			frm.method = &m;

			eng.execute(&frm);

			float result = frm.operandStack->pop();
			float expected = (float)value;

			Assert::AreEqual(expected, result);
			Assert::AreEqual(expected, result);
		}


		TEST_METHOD(L2I)
		{
			ExecutionEngine eng;
			Method m;

			long long value = (long long)INT_MAX + 1;
			int high = highWord(value);
			int low = lowWord(value);

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::L2I;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(high);
			frm.operandStack->push(low);
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			int expected = (int)value;

			Assert::AreEqual(expected, result);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(L2D)
		{
			ExecutionEngine eng;
			Method m;

			long long value = (long long)INT_MAX + 1;
			int high = highWord(value);
			int low = lowWord(value);

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::L2D;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(high);
			frm.operandStack->push(low);
			frm.method = &m;

			eng.execute(&frm);

			int resultLow = frm.operandStack->pop();
			int resultHigh = frm.operandStack->pop();
			double result = doubleFromStack(resultHigh, resultLow);

			double expected = (double)value;

			Assert::AreEqual(expected, result);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(L2F)
		{
			ExecutionEngine eng;
			Method m;

			long long value = (long long)INT_MAX + 1;
			int high = highWord(value);
			int low = lowWord(value);

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::L2F;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(high);
			frm.operandStack->push(low);
			frm.method = &m;

			eng.execute(&frm);

			float result = frm.operandStack->pop();
			float expected = (float)value;

			Assert::AreEqual(expected, result);
			Assert::AreEqual(expected, result);
		}
	};
}
