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
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

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
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

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

		TEST_METHOD(RET)
		{
			const int byteCodeLength = 5;
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			int a = 0xCAFEBABD;
			int b = 1;

			int index = 1;
			int address = 3;

			m.byteCode = new Instruction[byteCodeLength];
			m.byteCode[0] = (Instruction)InstructionSet::RET;
			m.byteCode[1] = index;
			m.byteCode[2] = (Instruction)InstructionSet::ISUB;
			m.byteCode[3] = (Instruction)InstructionSet::IADD;

			m.byteCodeLength = byteCodeLength;

			MethodFrame frm(3, 3);
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

		TEST_METHOD(IFEQ_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFEQ, 0, a, b, a + b);
		}

		TEST_METHOD(IFEQ_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFEQ, 1, a, b, a - b);
		}

		TEST_METHOD(IFNE_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFNE, 0, a, b, a - b);
		}

		TEST_METHOD(IFNE_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFNE, 1, a, b, a + b);
		}

		TEST_METHOD(IFLT_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFLT, -1, a, b, a + b);
		}

		TEST_METHOD(IFLT_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFLT, 1, a, b, a - b);
		}

		TEST_METHOD(IFLT_FALSE_2)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFLT, 0, a, b, a - b);
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

		/////// int compare
		TEST_METHOD(ICMPEQ_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPEQ, 0, 0, a, b, a + b);
		}

		TEST_METHOD(ICMPEQ_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPEQ, 0, 1, a, b, a - b);
		}

		TEST_METHOD(ICMPNE_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPNE, 0, 0, a, b, a - b);
		}

		TEST_METHOD(ICMPNE_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPNE, 0, 1, a, b, a + b);
		}

		TEST_METHOD(ICMPLT_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPLT, 0, 1, a, b, a + b);
		}

		TEST_METHOD(ICMPLT_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPLT, 1, 0, a, b, a - b);
		}

		TEST_METHOD(ICMPLT_FALSE_2)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPLT, 0, 0, a, b, a - b);
		}

		TEST_METHOD(ICMPGT_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPGT, 1, 0, a, b, a + b);
		}

		TEST_METHOD(ICMPGT_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPGT, 0, 1, a, b, a - b);
		}

		TEST_METHOD(ICMPGT_FALSE_2)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPGT, 0, 0, a, b, a - b);
		}

		TEST_METHOD(ICMPLE_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPLE, 0, 1, a, b, a + b);
		}

		TEST_METHOD(ICMPLE_TRUE_2)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPLE, 0, 0, a, b, a + b);
		}

		TEST_METHOD(ICMPLE_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPLE, 1, 0, a, b, a - b);
		}

		TEST_METHOD(ICMPGE_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPGE, 1, 0, a, b, a + b);
		}

		TEST_METHOD(ICMPGE_TRUE_2)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPGE, 0, 0, a, b, a + b);
		}

		TEST_METHOD(ICMPGE_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ICMPGE, 0, 1, a, b, a - b);
		}

		// reference compare
		TEST_METHOD(IF_ACMPEQ_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ACMPEQ, 0, 0, a, b, a + b);
		}

		TEST_METHOD(IF_ACMPEQ_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ACMPEQ, 0, 1, a, b, a - b);
		}

		TEST_METHOD(IF_ACMPNE_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ACMPNE, 1, 0, a, b, a + b);
		}

		TEST_METHOD(IF_ACMPNE_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			icmpTestStub(IF_ACMPNE, 0, 0, a, b, a - b);
		}


		TEST_METHOD(IFNULL_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFNULL, 0, a, b, a + b);
		}

		TEST_METHOD(IFNULL_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFNULL, 1, a, b, a - b);
		}

		TEST_METHOD(IFNONNULL_TRUE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFNONNULL, 1, a, b, a + b);
		}

		TEST_METHOD(IFNONNULL_FALSE)
		{
			int a = 0xCAFEBABD;
			int b = 1;
			ifTestStub(IFNONNULL, 0, a, b, a - b);
		}


		inline void ifTestStub(Instruction instruction, int stack, int a, int b, int expected)
		{
			const int byteCodeLength = 5;
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

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

		inline void icmpTestStub(Instruction instruction, int stackA, int stackB, int a, int b, int expected)
		{
			const int byteCodeLength = 5;
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			m.byteCode = new Instruction[byteCodeLength];
			m.byteCode[0] = instruction;
			m.byteCode[1] = 0;
			m.byteCode[2] = 2;
			m.byteCode[3] = (Instruction)InstructionSet::ISUB;
			m.byteCode[4] = (Instruction)InstructionSet::IADD;

			m.byteCodeLength = byteCodeLength;

			MethodFrame frm(5, 5);
			frm.operandStack->push(0);
			frm.operandStack->push(a);
			frm.operandStack->push(b);
			frm.operandStack->push(stackA);
			frm.operandStack->push(stackB);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}
	};
}
