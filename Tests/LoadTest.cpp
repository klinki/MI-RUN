#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"
#include "../JVM/runtime/ExecutionEngine.h"
#include "../JVM/runtime/MethodFrame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(LoadTest)
	{
	public:

		TEST_METHOD(testILOAD)
		{
			ExecutionEngine eng;
			Method m;
			
			int expected = 0x0BAFBAF;

			m.byteCode = new Instruction[1]; 
			m.byteCode[0] = (Instruction)InstructionSet::ILOAD_0;
			m.byteCodeLength = 1;

			MethodFrame frm(1, 1, true);
			frm.pc = 0;
			(*frm.localVariables)[0] = expected;
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

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::FLOAD_0;
			m.byteCodeLength = 1;

			MethodFrame frm(1, 1, true);
			frm.pc = 0;
			(*frm.localVariables)[0] = expected;
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

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::LLOAD_0;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2, true);
			frm.pc = 0;
			(*frm.localVariables)[0] = highWord(expected);
			(*frm.localVariables)[1] = lowWord(expected);
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

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DLOAD_0;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2, true);
			frm.pc = 0;
			(*frm.localVariables)[0] = highWord(expected);
			(*frm.localVariables)[1] = lowWord(expected);
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

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::ALOAD_0;
			m.byteCodeLength = 1;

			MethodFrame frm(1, 1, true);
			frm.pc = 0;
			(*frm.localVariables)[0] = expected;
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}
	};
}
