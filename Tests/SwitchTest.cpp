#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/Runtime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(SwitchTest)
	{
	public:
		TEST_METHOD(LOOKUPSWITCH_DEFAULT)
		{
			for (int alignment = 0; alignment < 3; alignment++)
			{
				this->switchTestStub((Instruction)LOOKUPSWITCH, alignment, 6, -1);
			}
		}

		TEST_METHOD(LOOKUPSWITCH_CORRECT)
		{
			for (int alignment = 0; alignment < 3; alignment++)
			{
				this->switchTestStub((Instruction)LOOKUPSWITCH, alignment, 0, 5);
				this->switchTestStub((Instruction)LOOKUPSWITCH, alignment, 1, 4);
				this->switchTestStub((Instruction)LOOKUPSWITCH, alignment, 2, 3);
				this->switchTestStub((Instruction)LOOKUPSWITCH, alignment, 3, 2);
				this->switchTestStub((Instruction)LOOKUPSWITCH, alignment, 4, 1);
				this->switchTestStub((Instruction)LOOKUPSWITCH, alignment, 5, 0);
			}
		}

		TEST_METHOD(TABLESWITCH_DEFAULT)
		{
			for (int alignment = 0; alignment < 3; alignment++)
			{
				this->switchTestStub((Instruction)TABLESWITCH, alignment, 6, -1);
			}
		}

		TEST_METHOD(TABLESWITCH_CORRECT)
		{
			for (int alignment = 0; alignment < 3; alignment++)
			{
				this->switchTestStub((Instruction)TABLESWITCH, alignment, 0, 5);
				this->switchTestStub((Instruction)TABLESWITCH, alignment, 1, 4);
				this->switchTestStub((Instruction)TABLESWITCH, alignment, 2, 3);
				this->switchTestStub((Instruction)TABLESWITCH, alignment, 3, 2);
				this->switchTestStub((Instruction)TABLESWITCH, alignment, 4, 1);
				this->switchTestStub((Instruction)TABLESWITCH, alignment, 5, 0);
			}
		}

		
		inline void addNumber(Method & m, int & i, int value)
		{
			m.byteCode[i++] = highByte(highShort(value));
			m.byteCode[i++] = lowByte(highShort(value));
			m.byteCode[i++] = highByte(lowShort(value));
			m.byteCode[i++] = lowByte(lowShort(value));
		}


		inline void switchTestStub(Instruction instruction, int alignment, int stack, int expected)
		{
			//  instruction + alignment + instructions after table 
			int byteCodeLength = 1 + 3 + 6 * 4 + 2;

			if (instruction == TABLESWITCH)
			{
				// (default + low + high) + (table * 6)  
				byteCodeLength += 3 * 4 + 6 * 4;

			}
			else if (instruction == LOOKUPSWITCH)
			{
				// (default + n) + (key + offset) * 6 
				byteCodeLength += 2 * 4 + 6 * 8;
			}
			
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			int nopsBefore = 4 - alignment - 1;
			int i = 0;

			int tableSize = 6;
			int indices[] = { 0, 1, 2, 3, 4, 5 };

			m.byteCode = new Instruction[byteCodeLength];

			for (int j = 0; j < nopsBefore; j++)
			{
				m.byteCode[i++] = NOP;
			}

			m.byteCode[i++] = instruction;

			for (int j = 0; j < alignment; j++)
			{
				m.byteCode[i++] = 0;
			}

			// default
			int defaultAddress = byteCodeLength - 2 - nopsBefore;
			this->addNumber(m, i, defaultAddress);

			if (instruction == TABLESWITCH) 
			{
				// low
				this->addNumber(m, i, 0);

				// high
				this->addNumber(m, i, 5);

				// offsets
				for (int j = 0; j < tableSize; j++)
				{
					int offset = defaultAddress - (j + 1) * 4;
					this->addNumber(m, i, offset);

				}
			}
			else if (instruction == LOOKUPSWITCH) 
			{
				// count
				this->addNumber(m, i, tableSize);

				// key-offset pairs
				for (int j = 0; j < tableSize; j++)
				{
					int offset = defaultAddress - (j + 1) * 4;
					this->addNumber(m, i, indices[j]);
					this->addNumber(m, i, offset);
				}
			}

			for (int j = tableSize - 1; j >= 0; j--)
			{
				m.byteCode[i++] = (Instruction)InstructionSet::ICONST_5 - j;
				m.byteCode[i++] = (Instruction)InstructionSet::GOTO;

				int offset = byteCodeLength - 1 - i - 1;
				m.byteCode[i++] = highByte(offset);
				m.byteCode[i++] = lowByte(offset);
			}

			m.byteCode[i++] = (Instruction)InstructionSet::ICONST_M1;
			m.byteCode[i++] = NOP;

			m.byteCodeLength = byteCodeLength;

			MethodFrame frm(1, 1);
			frm.operandStack->push(stack);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		inline void tableSwitchTestStub(Instruction instruction, int alignment, int stack, int expected)
		{
			// instruction + alignment + (default + low + high) + (table * 6)  
			const int byteCodeLength = 1 + 3 + 3 * 4 + 8 * 6  + 6 * 4 + 2;
			ExecutionEngine eng = getEngine();
			Method m = getMethod();

			int i = 1;

			int indices[] = { -1, 0, 1, 2, 3, 4, 5 };


			m.byteCode = new Instruction[byteCodeLength];

			for (int j = 0; j < 4 - alignment; j++)
			{
				m.byteCode[i++] = NOP;
			}

			m.byteCode[i++] = instruction;

			for (int j = 0; j < alignment; j++)
			{
				m.byteCode[i++] = 0;
			}

			// default
			m.byteCode[i++] = highByte(highShort(indices[i]));
			m.byteCode[i++] = lowByte(highShort(indices[i]));
			m.byteCode[i++] = highByte(lowShort(indices[i]));
			m.byteCode[i++] = lowByte(lowShort(indices[i]));
			
			// low
			m.byteCode[i++] = 0;
			m.byteCode[i++] = 0;
			m.byteCode[i++] = 0;
			m.byteCode[i++] = 0;

			// high
			m.byteCode[i++] = 0;
			m.byteCode[i++] = 0;
			m.byteCode[i++] = 0;
			m.byteCode[i++] = 5;


			for (int j = 0; j < 7; j++)
			{
				m.byteCode[i++] = highByte(highShort(indices[i]));
				m.byteCode[i++] = lowByte(highShort(indices[i]));
				m.byteCode[i++] = highByte(lowShort(indices[i]));
				m.byteCode[i++] = lowByte(lowShort(indices[i]));
/*
				m.byteCode[i++] = highByte(highShort(indices[i]));
				m.byteCode[i++] = lowByte(highShort(indices[i]));
				m.byteCode[i++] = highByte(lowShort(indices[i]));
				m.byteCode[i++] = lowByte(lowShort(indices[i]));
*/
			}

			for (int j = 0; j < 6; j++)
			{

				m.byteCode[i++] = (Instruction)InstructionSet::ICONST_0 + j;
				m.byteCode[i++] = (Instruction)InstructionSet::GOTO;
				m.byteCode[i++] = 0;
				m.byteCode[i++] = 0;
			}

			m.byteCode[i++] = (Instruction)InstructionSet::ICONST_M1;
			m.byteCode[i++] = NOP;

			m.byteCodeLength = byteCodeLength;

			MethodFrame frm(4, 4);
			frm.operandStack->push(stack);

			frm.pc = 0;
			frm.method = &m;

			eng.execute(&frm);

			int result = frm.operandStack->pop();
			Assert::AreEqual(expected, result);
		}
	};
}
