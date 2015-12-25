#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(FloatTest)
	{
	public:
		TEST_METHOD(testFMUL)
		{
			ExecutionEngine eng;
			Method m;

			float a[] = { 3.14, 0, 1, -1, -1, 0.0/0.0, INT_MAX, ULLONG_MAX,  1.012 };
			float b[] = { 1/0.0, 0, +1/0.0, +1.0/0.0, -1.0/0.0, -1, INT_MAX, ULLONG_MAX, 1.012 };

			for (int i = 0; i < 8; i++)
			{
				float expected = a[i] * b[i];

				m.byteCode = new Instruction[1];
				m.byteCode[0] = (Instruction)InstructionSet::FMUL;
				m.byteCodeLength = 1;

				MethodFrame frm(2, 2, true);
				frm.operandStack->push(a[i]);
				frm.operandStack->push(b[i]);

				frm.pc = 0;
				frm.method = &m;

				eng.execute(&frm);

				float result = frm.operandStack->pop();
				Assert::AreEqual(expected, result);
			}
		}

		TEST_METHOD(testFDivByZero)
		{
			throw NotImplementedException();
		}

		TEST_METHOD(testFDIV)
		{
			throw NotImplementedException();
		}


		TEST_METHOD(testFREM)
		{
			throw NotImplementedException();
		}


		TEST_METHOD(testFRemByZero)
		{
			throw NotImplementedException();
		}

		TEST_METHOD(testFADD)
		{
			throw NotImplementedException();
		}

		TEST_METHOD(testFSUB)
		{
			throw NotImplementedException();
		}

		TEST_METHOD(testFNEG)
		{
			throw NotImplementedException();
		}
	};
}
