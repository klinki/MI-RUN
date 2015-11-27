#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\JVM\runtime\OperandStack.h"
#include "..\JVM\runtime\ExecutionEngine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{


	TEST_CLASS(DupTest)
	{
	public:

		TEST_METHOD(DUP)
		{
			// val
			// val, val
			ExecutionEngine eng;
			Method m;

			int expected = 0x0BAFBAF;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DUP;
			m.byteCodeLength = 1;

			MethodFrame frm(2, 2);
			frm.pc = 0;
			frm.operandStack->push(expected);
			frm.method = &m;

			eng.execute(&frm);

			Assert::AreEqual(expected, (int)frm.operandStack->allocatedArray[0]);
			Assert::AreEqual(expected, (int)frm.operandStack->allocatedArray[1]);
		}

		TEST_METHOD(DUP_X1)
		{
			// val2, val1
			// val1, val2, val1
			ExecutionEngine eng;
			Method m;

			int a = 0xBEBEBEB;
			int b = 0x0BAFBAF;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DUP_X1;
			m.byteCodeLength = 1;

			MethodFrame frm(3, 3);
			frm.pc = 0;
			frm.operandStack->push(b);
			frm.operandStack->push(a);
			frm.method = &m;

			eng.execute(&frm);

			Assert::AreEqual(a, (int)frm.operandStack->allocatedArray[0]);
			Assert::AreEqual(b, (int)frm.operandStack->allocatedArray[1]);
			Assert::AreEqual(a, (int)frm.operandStack->allocatedArray[2]);
		}

		TEST_METHOD(DUP_X2)
		{
			// value3, value2, value1
			// value1, value3, value2, value1
			ExecutionEngine eng;
			Method m;

			int a = 0xBEBEBEB;
			int b = 0x0BAFBAF;
			int c = 0xCAFEBABE;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DUP_X2;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.pc = 0;
			frm.operandStack->push(c);
			frm.operandStack->push(b);
			frm.operandStack->push(a);
			frm.method = &m;

			eng.execute(&frm);

			Assert::AreEqual(a, (int)frm.operandStack->allocatedArray[0]);
			Assert::AreEqual(c, (int)frm.operandStack->allocatedArray[1]);
			Assert::AreEqual(b, (int)frm.operandStack->allocatedArray[2]);
			Assert::AreEqual(a, (int)frm.operandStack->allocatedArray[3]);
		}

		TEST_METHOD(DUP2)
		{
			// value2, value1
			// value2, value1, value2, value1
			ExecutionEngine eng;
			Method m;

			int a = 0xBEBEBEB;
			int b = 0x0BAFBAF;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DUP2;
			m.byteCodeLength = 1;

			MethodFrame frm(4, 4);
			frm.pc = 0;
			frm.operandStack->push(b);
			frm.operandStack->push(a);
			frm.method = &m;

			eng.execute(&frm);

			Assert::AreEqual(b, (int)frm.operandStack->allocatedArray[0]);
			Assert::AreEqual(a, (int)frm.operandStack->allocatedArray[1]);
			Assert::AreEqual(b, (int)frm.operandStack->allocatedArray[2]);
			Assert::AreEqual(a, (int)frm.operandStack->allocatedArray[3]);
		}

		TEST_METHOD(DUP2_X1)
		{
			// value3, value2, value1
			// value2, value1, value3, value2, value1
			ExecutionEngine eng;
			Method m;

			int a = 0xBEBEBEB;
			int b = 0x0BAFBAF;
			int c = 0xCAFEBABE;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DUP2_X1;
			m.byteCodeLength = 1;

			MethodFrame frm(5, 5);
			frm.pc = 0;
			frm.operandStack->push(c);
			frm.operandStack->push(b);
			frm.operandStack->push(a);
			frm.method = &m;

			eng.execute(&frm);

			Assert::AreEqual(b, (int)frm.operandStack->allocatedArray[0]);
			Assert::AreEqual(a, (int)frm.operandStack->allocatedArray[1]);
			Assert::AreEqual(c, (int)frm.operandStack->allocatedArray[2]);
			Assert::AreEqual(b, (int)frm.operandStack->allocatedArray[3]);
			Assert::AreEqual(a, (int)frm.operandStack->allocatedArray[4]);
		}

		TEST_METHOD(DUP2_X2)
		{
			// value4, value3, value2, value1
			// value2, value1, value4, value3, value2, value1
			ExecutionEngine eng;
			Method m;

			int a = 0xBEBEBEB;
			int b = 0x0BAFBAF;
			int c = 0xCAFEBABE;
			int d = 0x1EEE1EEE;

			m.byteCode = new Instruction[1];
			m.byteCode[0] = (Instruction)InstructionSet::DUP2_X2;
			m.byteCodeLength = 1;

			MethodFrame frm(6, 6);
			frm.pc = 0;
			frm.operandStack->push(d);
			frm.operandStack->push(c);
			frm.operandStack->push(b);
			frm.operandStack->push(a);
			frm.method = &m;

			eng.execute(&frm);

			Assert::AreEqual(b, (int)frm.operandStack->allocatedArray[0]);
			Assert::AreEqual(a, (int)frm.operandStack->allocatedArray[1]);
			Assert::AreEqual(d, (int)frm.operandStack->allocatedArray[2]);
			Assert::AreEqual(c, (int)frm.operandStack->allocatedArray[3]);
			Assert::AreEqual(b, (int)frm.operandStack->allocatedArray[4]);
			Assert::AreEqual(a, (int)frm.operandStack->allocatedArray[5]);
		}
	};
}
