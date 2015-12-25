#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"
#include "../JVM/runtime/ExecutionEngine.h"
#include "../JVM/runtime/MethodFrame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(StoreTest)
	{
	public:

		TEST_METHOD(testISTORE)
		{
			ExecutionEngine eng;
			Method m;

			int expected = 0x0BAFBAF;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::ISTORE_0;
			m.byteCodeLength = 1;

			MethodFrame frm(1, 1, true);
			frm.pc = 0;
			frm.operandStack->push(expected);
			frm.method = &m;

			eng.execute(&frm);

			int result = (*frm.localVariables)[0];
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testFSTORE)
		{
			ExecutionEngine eng;
			Method m;

			float expected = (float)3.14159265359;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::FSTORE_0;
			m.byteCodeLength = 1;

			MethodFrame frm(1, 1, true);
			frm.pc = 0;
			frm.operandStack->push(expected);
			frm.method = &m;

			eng.execute(&frm);

			float result = (*frm.localVariables)[0];
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testLSTORE)
		{
			ExecutionEngine eng;
			Method m;

			long long expected = 0xBAFFEEDBEEF;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::LSTORE_0;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2, true);;
			frm.pc = 0;
			frm.operandStack->push(highWord(expected));
			frm.operandStack->push(lowWord(expected));
			frm.method = &m;

			eng.execute(&frm);

			unsigned int low = (*frm.localVariables)[1];
			unsigned int high = (*frm.localVariables)[0];

			long long result = longFromStack(high, low);

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testDSTORE)
		{
			ExecutionEngine eng;
			Method m;

			double expected = (double)3.14159265359;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DSTORE_0;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2, true);;
			frm.pc = 0;
			frm.operandStack->push(highWord(expected));
			frm.operandStack->push(lowWord(expected));
			frm.method = &m;

			eng.execute(&frm);

			unsigned int low = (*frm.localVariables)[1];
			unsigned int high = (*frm.localVariables)[0];

			double result = doubleFromStack(high, low);

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testASTORE)
		{
			ExecutionEngine eng;
			Method m;

			int expected = (int)&m;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::ASTORE_0;
			m.byteCodeLength = 1;

			MethodFrame frm(1, 1, true);
			frm.pc = 0;
			frm.operandStack->push(expected);
			frm.method = &m;

			eng.execute(&frm);

			int result = (*frm.localVariables)[0];
			Assert::AreEqual(expected, result);
		}
	};
}
