#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"
#include "../JVM/runtime/ExecutionEngine.h"
#include "../JVM/runtime/MethodFrame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(FunctionCalls)
	{
	public:

		TEST_METHOD(testILOAD)
		{
			ExecutionEngine eng;
			Method m;

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

		TEST_METHOD(testFLOAD)
		{
			ExecutionEngine eng;
			Method m;

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

		TEST_METHOD(testLLOAD)
		{
			ExecutionEngine eng;
			Method m;

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

		TEST_METHOD(testDLOAD)
		{
			ExecutionEngine eng;
			Method m;

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

		TEST_METHOD(testALOAD)
		{
			ExecutionEngine eng;
			Method m;

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

		TEST_METHOD(testIINCWideIndex)
		{
			ExecutionEngine eng;
			Method m;

			int expected = 0x0BAFBAF;
			int increment = 1024;
			int value = expected - increment;
			int index = 1024;

			m.byteCode = new Instruction[4];
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
	};
}
