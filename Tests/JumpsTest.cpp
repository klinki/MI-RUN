#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(JumpsTest)
	{
	public:
		TEST_METHOD(GOTO)
		{
			const int byteCodeLength = 5;
			ExecutionEngine eng;
			Method m;

			int a = 0xCAFEBABD;
			int b = 1;

			m.byteCode = new Instruction[byteCodeLength];
			m.byteCode[0] = (Instruction)InstructionSet::GOTO;
			m.byteCode[1] = 0;
			m.byteCode[2] = 2; // end of goto
			m.byteCode[3] = (Instruction)InstructionSet::ISUB;
			m.byteCode[4] = (Instruction)InstructionSet::IADD;

			m.byteCodeLength = byteCodeLength;

			MethodFrame frm(2, 2);
			frm.operandStack->push(a);
			frm.operandStack->push(b);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int expected = a + b;
			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(GOTO_W)
		{
			const int byteCodeLength = 70000;
			ExecutionEngine eng;
			Method m;

			int a = 0xCAFEBABD;
			int b = 1;

			int address = byteCodeLength - 5;

			m.byteCode = new Instruction[byteCodeLength];
			m.byteCode[0] = (Instruction)InstructionSet::GOTO_W;
			m.byteCode[1] = highByte(highShort(address));
			m.byteCode[2] = lowByte(highShort(address));
			m.byteCode[3] = highByte(lowShort(address));
			m.byteCode[4] = lowByte(lowShort(address));

			for (int i = 5; i < byteCodeLength; i++)
			{
				m.byteCode[i] = (Instruction)InstructionSet::ISUB;
			}

			m.byteCode[byteCodeLength - 1] = (Instruction)InstructionSet::IADD;
			
			m.byteCodeLength = byteCodeLength;

			MethodFrame frm(2, 2);
			frm.operandStack->push(a);
			frm.operandStack->push(b);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int expected = a + b;
			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(IFEQ_TRUE)
		{
			const int byteCodeLength = 5;
			ExecutionEngine eng;
			Method m;

			int a = 0xCAFEBABD;
			int b = 1;

			m.byteCode = new Instruction[byteCodeLength];
			m.byteCode[0] = (Instruction)InstructionSet::IFEQ;
			m.byteCode[1] = 0;
			m.byteCode[2] = 2; 
			m.byteCode[3] = (Instruction)InstructionSet::ISUB;
			m.byteCode[4] = (Instruction)InstructionSet::IADD;

			m.byteCodeLength = byteCodeLength;

			MethodFrame frm(3, 3);
			frm.operandStack->push(a);
			frm.operandStack->push(b);
			frm.operandStack->push(0);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int expected = a + b;
			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(IFEQ_FALSE)
		{
			const int byteCodeLength = 5;
			ExecutionEngine eng;
			Method m;

			int a = 0xCAFEBABD;
			int b = 1;

			m.byteCode = new Instruction[byteCodeLength];
			m.byteCode[0] = (Instruction)InstructionSet::IFEQ;
			m.byteCode[1] = 0;
			m.byteCode[2] = 2;
			m.byteCode[3] = (Instruction)InstructionSet::ISUB;
			m.byteCode[4] = (Instruction)InstructionSet::IADD;

			m.byteCodeLength = byteCodeLength;

			MethodFrame frm(4, 4);
			frm.operandStack->push(0);
			frm.operandStack->push(a);
			frm.operandStack->push(b);
			frm.operandStack->push(1);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int expected = a - b;
			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(IFNE_FALSE)
		{
			const int byteCodeLength = 5;
			ExecutionEngine eng;
			Method m;

			int a = 0xCAFEBABD;
			int b = 1;

			m.byteCode = new Instruction[byteCodeLength];
			m.byteCode[0] = (Instruction)InstructionSet::IFNE;
			m.byteCode[1] = 0;
			m.byteCode[2] = 2;
			m.byteCode[3] = (Instruction)InstructionSet::ISUB;
			m.byteCode[4] = (Instruction)InstructionSet::IADD;

			m.byteCodeLength = byteCodeLength;

			MethodFrame frm(3, 3);
			frm.operandStack->push(a);
			frm.operandStack->push(b);
			frm.operandStack->push(0);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int expected = a + b;
			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(IFNE_TRUE)
		{
			const int byteCodeLength = 5;
			ExecutionEngine eng;
			Method m;

			int a = 0xCAFEBABD;
			int b = 1;

			m.byteCode = new Instruction[byteCodeLength];
			m.byteCode[0] = (Instruction)InstructionSet::IFEQ;
			m.byteCode[1] = 0;
			m.byteCode[2] = 2;
			m.byteCode[3] = (Instruction)InstructionSet::ISUB;
			m.byteCode[4] = (Instruction)InstructionSet::IADD;

			m.byteCodeLength = byteCodeLength;

			MethodFrame frm(4, 4);
			frm.operandStack->push(0);
			frm.operandStack->push(a);
			frm.operandStack->push(b);
			frm.operandStack->push(1);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int expected = a - b;
			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(IFLT_TRUE)
		{
			const int byteCodeLength = 5;
			ExecutionEngine eng;
			Method m;

			int a = 0xCAFEBABD;
			int b = 1;

			m.byteCode = new Instruction[byteCodeLength];
			m.byteCode[0] = (Instruction)InstructionSet::IFNE;
			m.byteCode[1] = 0;
			m.byteCode[2] = 2;
			m.byteCode[3] = (Instruction)InstructionSet::ISUB;
			m.byteCode[4] = (Instruction)InstructionSet::IADD;

			m.byteCodeLength = byteCodeLength;

			MethodFrame frm(3, 3);
			frm.operandStack->push(a);
			frm.operandStack->push(b);
			frm.operandStack->push(-1);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int expected = a + b;
			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(IFLT_FALSE)
		{
			const int byteCodeLength = 5;
			ExecutionEngine eng;
			Method m;

			int a = 0xCAFEBABD;
			int b = 1;

			m.byteCode = new Instruction[byteCodeLength];
			m.byteCode[0] = (Instruction)InstructionSet::IFEQ;
			m.byteCode[1] = 0;
			m.byteCode[2] = 2;
			m.byteCode[3] = (Instruction)InstructionSet::ISUB;
			m.byteCode[4] = (Instruction)InstructionSet::IADD;

			m.byteCodeLength = byteCodeLength;

			MethodFrame frm(4, 4);
			frm.operandStack->push(0);
			frm.operandStack->push(a);
			frm.operandStack->push(b);
			frm.operandStack->push(1);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int expected = a - b;
			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(IFGT_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFGT, 1, a, b, a + b);
		}

		TEST_METHOD(IFGT_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFGT, -1, a, b, a - b);
		}

		TEST_METHOD(IFGT_FALSE_2)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFGT, 0, a, b, a - b);
		}

		TEST_METHOD(IFLE_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFLE, 0, a, b, a + b);
		}

		TEST_METHOD(IFLE_TRUE_2)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFLE, -1, a, b, a + b);
		}

		TEST_METHOD(IFLE_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFLE, 1, a, b, a - b);
		}

		TEST_METHOD(IFGE_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFGE, 0, a, b, a + b);
		}

		TEST_METHOD(IFGE_TRUE_2)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFGE, 1, a, b, a + b);
		}

		TEST_METHOD(IFGE_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFGE, -1, a, b, a - b);
		}

		inline void ifTestStub(Instruction instruction, int stack, int a, int b, int expected)
		{
			const int byteCodeLength = 5;
			ExecutionEngine eng;
			Method m;

			m.byteCode = new Instruction[byteCodeLength];
			m.byteCode[0] = instruction;
			m.byteCode[1] = 0;
			m.byteCode[2] = 2;
			m.byteCode[3] = (Instruction)InstructionSet::ISUB;
			m.byteCode[4] = (Instruction)InstructionSet::IADD;

			m.byteCodeLength = byteCodeLength;

			MethodFrame frm(4, 4);
			frm.operandStack->push(0);
			frm.operandStack->push(a);
			frm.operandStack->push(b);
			frm.operandStack->push(stack);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}
	};
}
