#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"
#include "../JVM/runtime/ExecutionEngine.h"
#include "../JVM/runtime/MethodFrame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(WideTest)
	{
	public:

		TEST_METHOD(testWideILOAD)
		{
			ExecutionEngine eng(new Runtime());
			Method m = getMethod();

			int expected = 0x0BAFBAF;
			int index = 1024;

			m.byteCode = new Instruction[4];
			m.byteCode[0] = (Instruction)InstructionSet::WIDE;
			m.byteCode[1] = (Instruction)InstructionSet::ILOAD;
			m.byteCode[2] = highByte(index);
			m.byteCode[3] = lowByte(index);
			m.byteCodeLength = 4;

			MethodFrame frm(1025, 1025);
			frm.pc = 0;
			(*frm.localVariables)[1024] = expected;
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testWideFLOAD)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			float expected = (float)3.14159265359;

			int index = 1024;

			m.byteCode = new Instruction[4];
			m.byteCode[0] = (Instruction)InstructionSet::WIDE;
			m.byteCode[1] = (Instruction)InstructionSet::FLOAD;
			m.byteCode[2] = highByte(index);
			m.byteCode[3] = lowByte(index);
			m.byteCodeLength = 4;

			MethodFrame frm(1025, 1025);
			frm.pc = 0;
			(*frm.localVariables)[1024] = expected;
			frm.method = &m;

			eng.execute(&frm);

			float result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testWideLLOAD)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			long long expected = 0xBAFFEEDBEEF;
			int index = 1024;

			m.byteCode = new Instruction[4];
			m.byteCode[0] = (Instruction)InstructionSet::WIDE;
			m.byteCode[1] = (Instruction)InstructionSet::LLOAD;
			m.byteCode[2] = highByte(index);
			m.byteCode[3] = lowByte(index);
			m.byteCodeLength = 4;

			MethodFrame frm(1026, 1026);
			frm.pc = 0;
			(*frm.localVariables)[1024] = highWord(expected);
			(*frm.localVariables)[1025] = lowWord(expected);
			frm.method = &m;

			eng.execute(&frm);

			unsigned int low = frm.operandStack->pop();
			unsigned int high = frm.operandStack->pop();

			long long result = longFromStack(high, low);

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testWideDLOAD)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			double expected = (double)3.14159265359;

			int index = 1024;

			m.byteCode = new Instruction[4];
			m.byteCode[0] = (Instruction)InstructionSet::WIDE;
			m.byteCode[1] = (Instruction)InstructionSet::DLOAD;
			m.byteCode[2] = highByte(index);
			m.byteCode[3] = lowByte(index);
			m.byteCodeLength = 4;

			MethodFrame frm(1026, 1026);
			frm.pc = 0;
			(*frm.localVariables)[1024] = highWord(expected);
			(*frm.localVariables)[1025] = lowWord(expected);
			frm.method = &m;

			eng.execute(&frm);

			unsigned int low = frm.operandStack->pop();
			unsigned int high = frm.operandStack->pop();

			double result = doubleFromStack(high, low);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testWideALOAD)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			int expected = (int)&m;

			int index = 1024;

			m.byteCode = new Instruction[4];
			m.byteCode[0] = (Instruction)InstructionSet::WIDE;
			m.byteCode[1] = (Instruction)InstructionSet::ALOAD;
			m.byteCode[2] = highByte(index);
			m.byteCode[3] = lowByte(index);
			m.byteCodeLength = 4;

			MethodFrame frm(1025, 1025);
			frm.pc = 0;
			(*frm.localVariables)[1024] = expected;
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}


		TEST_METHOD(testWideISTORE)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			int expected = 0x0BAFBAF;
			int index = 1024;

			m.byteCode = new Instruction[4];
			m.byteCode[0] = (Instruction)InstructionSet::WIDE;
			m.byteCode[1] = (Instruction)InstructionSet::ISTORE;
			m.byteCode[2] = highByte(index);
			m.byteCode[3] = lowByte(index);
			m.byteCodeLength = 4;

			MethodFrame frm(1025, 1025);
			frm.pc = 0;
			frm.method = &m;
			frm.operandStack->push(expected);

			eng.execute(&frm);

			int result = (*frm.localVariables)[1024];
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testWideFSTORE)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			float expected = (float)3.14159265359;

			int index = 1024;

			m.byteCode = new Instruction[4];
			m.byteCode[0] = (Instruction)InstructionSet::WIDE;
			m.byteCode[1] = (Instruction)InstructionSet::FSTORE;
			m.byteCode[2] = highByte(index);
			m.byteCode[3] = lowByte(index);
			m.byteCodeLength = 4;

			MethodFrame frm(1025, 1025);
			frm.pc = 0;
			frm.method = &m;
			frm.operandStack->push(expected);

			eng.execute(&frm);

			float result = (*frm.localVariables)[1024];
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testWideLSTORE)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			long long expected = 0xBAFFEEDBEEF;
			int index = 1024;

			m.byteCode = new Instruction[4];
			m.byteCode[0] = (Instruction)InstructionSet::WIDE;
			m.byteCode[1] = (Instruction)InstructionSet::LSTORE;
			m.byteCode[2] = highByte(index);
			m.byteCode[3] = lowByte(index);
			m.byteCodeLength = 4;

			MethodFrame frm(1026, 1026);
			frm.pc = 0;
			frm.method = &m;
			frm.operandStack->push2(expected);

			eng.execute(&frm);

			unsigned int high  = (*frm.localVariables)[1024];
			unsigned int low = (*frm.localVariables)[1025];

			long long result = longFromStack(high, low);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testWideDSTORE)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			double expected = (double)3.14159265359;

			int index = 1024;

			m.byteCode = new Instruction[4];
			m.byteCode[0] = (Instruction)InstructionSet::WIDE;
			m.byteCode[1] = (Instruction)InstructionSet::DSTORE;
			m.byteCode[2] = highByte(index);
			m.byteCode[3] = lowByte(index);
			m.byteCodeLength = 4;

			MethodFrame frm(1026, 1026);
			frm.pc = 0;
			frm.method = &m;
			frm.operandStack->push2(expected);

			eng.execute(&frm);

			unsigned int high = (*frm.localVariables)[1024];
			unsigned int low = (*frm.localVariables)[1025];

			double result = doubleFromStack(high, low);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testWideASTORE)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			int expected = (int)&m;

			int index = 1024;

			m.byteCode = new Instruction[4];
			m.byteCode[0] = (Instruction)InstructionSet::WIDE;
			m.byteCode[1] = (Instruction)InstructionSet::ASTORE;
			m.byteCode[2] = highByte(index);
			m.byteCode[3] = lowByte(index);
			m.byteCodeLength = 4;

			MethodFrame frm(1025, 1025);
			frm.pc = 0;
			frm.method = &m;
			frm.operandStack->push(expected);

			eng.execute(&frm);

			int result = (*frm.localVariables)[1024];
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testIINCWideIndexAndValue)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			int expected = 0x0BAFBAF;
			int increment = 1024;
			int value = expected - increment;
			int index = 1024;

			m.byteCode = new Instruction[6];
			m.byteCode[0] = (Instruction)InstructionSet::WIDE;
			m.byteCode[1] = (Instruction)InstructionSet::IINC;
			m.byteCode[2] = highByte(index);
			m.byteCode[3] = lowByte(index);
			m.byteCode[4] = highByte(increment);
			m.byteCode[5] = lowByte(increment);
			m.byteCodeLength = 6;

			MethodFrame frm(index + 1, index + 1);
			frm.pc = 0;
			(*frm.localVariables)[index] = value;
			frm.method = &m;

			eng.execute(&frm);

			int result = (*frm.localVariables)[index];
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testWideRET)
		{
			const int byteCodeLength = 70000;
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			int a = 0xCAFEBABD;
			int b = 1;

			int index = 1024;
			int address = byteCodeLength - 1;

			m.byteCode = new Instruction[byteCodeLength];
			m.byteCode[0] = (Instruction)InstructionSet::WIDE;
			m.byteCode[1] = (Instruction)InstructionSet::RET;
			m.byteCode[2] = highByte(index);
			m.byteCode[3] = lowByte(index);

			for (int i = 4; i < byteCodeLength; i++)
			{
				m.byteCode[i] = (Instruction)InstructionSet::ISUB;
			}

			m.byteCode[byteCodeLength - 1] = (Instruction)InstructionSet::IADD;

			m.byteCodeLength = byteCodeLength;

			MethodFrame frm(index + 1, index + 1);
			frm.operandStack->push(a);
			frm.operandStack->push(b);
			
			frm.localVariables->operator[](index) = address;

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int expected = a + b;
			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}
	};
}
