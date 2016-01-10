#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(PushTest)
	{
	public:

		TEST_METHOD(testBIPUSH)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			int expected = 125;

			m.byteCode = new Instruction[2];
			m.byteCode[0] = (Instruction)InstructionSet::BIPUSH;
			m.byteCode[1] = (Instruction)expected;
			m.byteCodeLength = 2;

			MethodFrame frm(1, 1);
			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(testSIPUSH)
		{
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			int expected = 256;

			m.byteCode = new Instruction[3];
			m.byteCode[0] = (Instruction)InstructionSet::SIPUSH;
			m.byteCode[1] = (Instruction)highByte(expected);
			m.byteCode[2] = (Instruction)lowByte(expected);
			m.byteCodeLength = 3;

			MethodFrame frm(1, 1);
			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}
	};
}
