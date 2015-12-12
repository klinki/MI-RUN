#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\JVM\runtime\Class.h"
#include "..\JVM\runtime\OperandStack.h"
#include "..\JVM\runtime\ExecutionEngine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(InvokeTest)
	{
	public:
		Class* getClass()
		{
			Class * A = new Class((FLAG)ClassAccessFlags::PUBLIC);
			A->fullyQualifiedName = Utf8String("A");
			A->parentClass = NULL; // object... 

			Class * B = new Class((FLAG)ClassAccessFlags::PUBLIC);
			B->fullyQualifiedName = Utf8String("B");
			B->parentClass = A;

			Method * aGetFoo = new Method(Utf8String("foo"), Utf8String("()V"));
			aGetFoo->byteCode = new Instruction[2];
			aGetFoo->byteCode[0] = ICONST_0;
			aGetFoo->byteCode[1] = IRETURN;
	
			Method * bGetFoo = new Method(Utf8String("foo"), Utf8String("()V"));
			aGetFoo->byteCode = new Instruction[2];
			aGetFoo->byteCode[0] = ICONST_1;
			aGetFoo->byteCode[1] = IRETURN;

			A->methodArea.addMethod(aGetFoo);
			B->methodArea.addMethod(bGetFoo);

			return B;
		}

		TEST_METHOD(INVOKEVIRTUAL)
		{
			ExecutionEngine eng;
			Method m;

			Object * obj = new Object();
			obj->objectClass = this->getClass();



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

		TEST_METHOD(INVOKESPECIAL)
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

		TEST_METHOD(INVOKESTATIC)
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

		TEST_METHOD(INVOKEDYNAMIC)
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

		TEST_METHOD(INVOKEINTERFACE)
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
	};
}
