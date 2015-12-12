#include "ExecutionEngine.h"
#include "../jvm_structures/JavaConstantPool.h"

ExecutionEngine::ExecutionEngine()
{
}


ExecutionEngine::~ExecutionEngine()
{
}

int ExecutionEngine::execute(MethodFrame * frame)
{
	this->frame = frame;
	Instruction * instructions = (Instruction*)this->frame->method->getBytecode();
	unsigned int length = this->frame->method->getByteCodeLength();

	ProgramCounter & pc = this->frame->pc;
	
	while (pc != length)
	{
		Instruction currentInstruction = instructions[pc++];

		switch (currentInstruction)
		{
		case ACONST_NULL:
			this->frame->operandStack->push(NULL);
			break;

			// FALL THROUGH:
		case ICONST_M1:
		case ICONST_0:
		case ICONST_1:
		case ICONST_2:
		case ICONST_3:
		case ICONST_4:
		case ICONST_5:
			this->frame->operandStack->push(currentInstruction - ICONST_0);
			break;

			// FALL THROUGH:
		case LCONST_0:
		case LCONST_1:
			this->pushLong(currentInstruction - LCONST_0);
			break;

			// FALL THROUGH:
		case FCONST_0:
		case FCONST_1:
		case FCONST_2:
			this->frame->operandStack->push((float)(currentInstruction - FCONST_0));
			break;

			// FALL THROUGH:
		case DCONST_0:
		case DCONST_1:
			this->pushDouble(currentInstruction - DCONST_0);
			break;

		case BIPUSH:
		{
			// push byte
			word byte = instructions[pc++];
			this->frame->operandStack->push(byte);
		}
		break;

		case SIPUSH:
		{
			// push short
			// byte 1
			// byte 2
			unsigned short index = getShort();
			this->frame->operandStack->push(JavaShort(index));
		}
		break;

		case LDC:
		{
			unsigned char index = instructions[pc++];
			this->pushFromConstantPool(index);
		}
		break;

		case LDC_W:
		{
			unsigned short index = getShort();
			this->pushFromConstantPool(index);
		}
		break;

		case LDC2_W:
		{
			// push long/double from constant-pool
			unsigned short index = getShort();
			this->pushFromConstantPool(index);
		}
		break;

		case ILOAD:
		{
			// load from local variable 
			// index
			unsigned char index = instructions[pc++];
			this->singleWordLoad(index);
		}
		break;

		// FALL THROUGH
		case ILOAD_0:
		case ILOAD_1:
		case ILOAD_2:
		case ILOAD_3:
			this->singleWordLoad(currentInstruction - ILOAD_0);
			break;

		case LLOAD:
		{
			unsigned char index = instructions[pc++];
			this->lload(index);
		}
		break;

		// FALL THROUGH:
		case LLOAD_0:
		case LLOAD_1:
		case LLOAD_2:
		case LLOAD_3:
			this->lload(currentInstruction - LLOAD_0);
			break;

		case FLOAD:
		{
			unsigned char index = instructions[pc++];
			this->singleWordLoad(index);
		}
		break;

		// FALL THROUGH:
		case FLOAD_0:
		case FLOAD_1:
		case FLOAD_2:
		case FLOAD_3:
			this->singleWordLoad(currentInstruction - FLOAD_0);
			break;

		case DLOAD:
		{
			unsigned char index = instructions[pc++];
			this->dload(index);
		}
		break;

		// FALL THROUGH:
		case DLOAD_0:
		case DLOAD_1:
		case DLOAD_2:
		case DLOAD_3:
			this->dload(currentInstruction - DLOAD_0);
			break;

		case ALOAD:
		{
			unsigned char index = instructions[pc++];
			this->singleWordLoad(index);
		}
		break;

		// FALL THROUGH:
		case ALOAD_0:
		case ALOAD_1:
		case ALOAD_2:
		case ALOAD_3:
			this->singleWordLoad(currentInstruction - ALOAD_0);
			break;

		case IALOAD:
		case LALOAD:
		case FALOAD:
		case DALOAD:
		case AALOAD:
		case BALOAD:
		case CALOAD:
		case SALOAD:

		case ISTORE:
		{
			unsigned char index = instructions[pc++];
			this->singleWordStore(index);
			// store int into local variable
		}
		break;

		// FALL THROUGH:
		case ISTORE_0:
		case ISTORE_1:
		case ISTORE_2:
		case ISTORE_3:
			this->singleWordStore(currentInstruction - ISTORE_0);
			break;

		case LSTORE:
		{
			unsigned char index = instructions[pc++];
			this->lstore(index);
		}
		break;

		case LSTORE_0:
		case LSTORE_1:
		case LSTORE_2:
		case LSTORE_3:
			this->lstore(currentInstruction - LSTORE_0);
			break;

		case FSTORE:
		{
			unsigned char index = instructions[pc++];
			this->singleWordStore(index);
			break;
		}
		case FSTORE_0:
		case FSTORE_1:
		case FSTORE_2:
		case FSTORE_3:
			this->singleWordStore(currentInstruction - FSTORE_0);
			break;

		case DSTORE:
		{
			unsigned char index = instructions[pc++];
			this->dstore(index);
		}
		break;
		case DSTORE_0:
		case DSTORE_1:
		case DSTORE_2:
		case DSTORE_3:
			this->dstore(currentInstruction - DSTORE_0);
			break;

		case ASTORE:
		{
			unsigned char index = instructions[pc++];
			this->singleWordStore(index);
		}
		break;
		case ASTORE_0:
		case ASTORE_1:
		case ASTORE_2:
		case ASTORE_3:
			this->singleWordStore(currentInstruction - ASTORE_0);
			break;

		case IASTORE:
			this->singleArrayStore();
			break;

		case LASTORE:
			this->longArrayStore();
			break;

		case FASTORE:
			this->singleArrayStore();
			break;

		case DASTORE:
			this->doubleArrayStore();
			break;

		case AASTORE:
			this->singleArrayStore();
			break;

		case BASTORE:
			this->singleArrayStore();
			break;

		case CASTORE:
			this->singleArrayStore();
			break;

		case SASTORE:
			this->singleArrayStore();
			break;

		case POP:
			// pop value from stack
			this->frame->operandStack->pop();
			break;

		case POP2:
			this->frame->operandStack->pop();
			this->frame->operandStack->pop();
			break;

		case DUP:
		{
			// value
			// value, value
			word value = this->frame->operandStack->pop();
			this->frame->operandStack->push(value);
			this->frame->operandStack->push(value);
		}
		break;

		case DUP_X1:
		{
			// value2, value1
			// value1, value2, value1
			word a = this->frame->operandStack->pop();
			word b = this->frame->operandStack->pop();
			this->frame->operandStack->push(a);
			this->frame->operandStack->push(b);
			this->frame->operandStack->push(a);
		}
		break;

		case DUP_X2:
		{
			// value3, value2, value1
			// value1, value3, value2, value1
			word a = this->frame->operandStack->pop();
			word b = this->frame->operandStack->pop();
			word c = this->frame->operandStack->pop();

			this->frame->operandStack->push(a);
			this->frame->operandStack->push(c);
			this->frame->operandStack->push(b);
			this->frame->operandStack->push(a);
		};
		break;

		case DUP2:
		{
			word a = this->frame->operandStack->pop();
			word b = this->frame->operandStack->pop();
			this->frame->operandStack->push(b);
			this->frame->operandStack->push(a);
			this->frame->operandStack->push(b);
			this->frame->operandStack->push(a);
		}
		break;

		case DUP2_X1:
		{
			// value3, value2, value1
			// value2, value1, value3, value2, value1
			word a = this->frame->operandStack->pop();
			word b = this->frame->operandStack->pop();
			word c = this->frame->operandStack->pop();

			this->frame->operandStack->push(b);
			this->frame->operandStack->push(a);
			this->frame->operandStack->push(c);
			this->frame->operandStack->push(b);
			this->frame->operandStack->push(a);
		}
		break;

		case DUP2_X2:
		{
			// value4, value3, value2, value1
			// value2, value1, value4, value3, value2, value1
			word a = this->frame->operandStack->pop();
			word b = this->frame->operandStack->pop();
			word c = this->frame->operandStack->pop();
			word d = this->frame->operandStack->pop();

			this->frame->operandStack->push(b);
			this->frame->operandStack->push(a);
			this->frame->operandStack->push(d);
			this->frame->operandStack->push(c);
			this->frame->operandStack->push(b);
			this->frame->operandStack->push(a);
		}
		break;

		case SWAP:
		{
			// swap operand-stack values
			// category 1
			word low = this->frame->operandStack->pop();
			word high = this->frame->operandStack->pop();
			this->frame->operandStack->push(low);
			this->frame->operandStack->push(high);
		}
		break;

		case IADD:
		{
			SINGLE_WORD_OPERATION(int, +);
		}
		break;

		case LADD:
		{
			LONG_OPERATION(+);
		}
		break;

		case FADD:
		{
			SINGLE_WORD_OPERATION(float, +);
		}
		break;

		case DADD:
		{
			DOUBLE_OPERATION(+);
		}
		break;

		case ISUB:
		{
			SINGLE_WORD_OPERATION(int, -);
		}
		break;

		case LSUB:
		{
			LONG_OPERATION(-);
		}
		break;

		case FSUB:
		{
			SINGLE_WORD_OPERATION(float, +);
		}
		break;

		case DSUB:
		{
			DOUBLE_OPERATION(-);
		}
		break;

		case IMUL:
		{
			SINGLE_WORD_OPERATION(int, *);
		}
		break;


		case LMUL:
		{
			LONG_OPERATION(*);
		}
		break;

		case FMUL:
		{
			SINGLE_WORD_OPERATION(float, *);
		}
		break;

		case DMUL:
		{
			DOUBLE_OPERATION(*);
		}
		break;

		case IDIV:
		{
			int b = this->frame->operandStack->pop();
			int a = this->frame->operandStack->pop();

			if (b == 0)
			{
				// exception! 
				throw Exceptions::Runtime::ArithmeticException();
			}

			this->frame->operandStack->push(JavaInt(a * b));
		}
		break;


		case LDIV:
		{
			long long b = this->getLongFromStack();
			long long a = this->getLongFromStack();

			if (b == 0)
			{
				// exception! 
			}

			this->pushLong(a / b);
		}
		break;

		case FDIV:
		{
			SINGLE_WORD_OPERATION(float, / );
		}
		break;

		case DDIV:
		{
			DOUBLE_OPERATION(/ );
		}
		break;

		case IREM:
		{
			// returns remainder
			int b = this->frame->operandStack->pop();
			int a = this->frame->operandStack->pop();

			if (b == 0)
			{
				// exception!
				throw Exceptions::Runtime::ArithmeticException();
			}

			this->frame->operandStack->push(JavaInt(a % b));
		}
		break;

		case LREM:
		{
			long b = this->getLongFromStack();
			long a = this->getLongFromStack();

			if (b == 0)
			{
				// exception!
				throw Exceptions::Runtime::ArithmeticException();
			}

			this->pushLong(a % b);
		}
		break;

		case FREM:
		{
			float b = this->frame->operandStack->pop();
			float a = this->frame->operandStack->pop();
			this->frame->operandStack->push(fmodf(a, b));
		}
		break;

		case DREM:
		{
			double b = this->getDoubleFromStack();
			double a = this->getDoubleFromStack();
			this->pushDouble(fmod(a, b));
		}
		break;

		case INEG:
		{
			int a = this->frame->operandStack->pop();
			this->frame->operandStack->push(-a);
		}
		break;

		case LNEG:
		{
			long a = this->getLongFromStack();
			this->pushLong(-a);
		}
		break;

		case FNEG:
		{
			float a = this->frame->operandStack->pop();
			this->frame->operandStack->push(-a);
		}
		break;

		case DNEG:
		{
			double a = this->getDoubleFromStack();
			this->pushDouble(-a);
		}
		break;


		case ISHL:
		{
			SINGLE_WORD_OPERATION(int, << );
		}
		// shift left
		break;

		case LSHL:
		{
			long long a = this->getLongFromStack();
			int b = this->frame->operandStack->pop();
			this->pushLong(a << b);
		}
		break;

		case ISHR:
		{
			SINGLE_WORD_OPERATION(int, >> );
		}
		break;

		case LSHR:
		{
			// shift right
			long long a = this->getLongFromStack();
			int b = this->frame->operandStack->pop();
			this->pushLong(a >> b);
		}
		break;

		case IUSHR:
		{
			SINGLE_WORD_OPERATION(unsigned int, >> );
			// shift unsigned right
		}
		break;

		case LUSHR:
		{
			unsigned long long a = this->getLongFromStack();
			unsigned int b = this->frame->operandStack->pop();
			this->pushLong(a >> b);
			break;
		}

		case IAND:
		{
			SINGLE_WORD_OPERATION(int, &);
		}
		break;

		case LAND:
		{
			LONG_OPERATION(&);
		}
		break;

		case IOR:
		{
			SINGLE_WORD_OPERATION(int, | );
		}
		break;

		case LOR:
		{
			LONG_OPERATION(| );
		}
		break;

		case IXOR:
		{
			SINGLE_WORD_OPERATION(int, ^);
		}
		break;

		case LXOR:
		{
			LONG_OPERATION(^);
		}
		break;

		case IINC:
		{
			unsigned char index = instructions[pc++];
			int value = (int)instructions[pc++];
			this->iinc(index, value);
		}
		break;

		case I2L:
		{
			long long val = (long long)(int) this->frame->operandStack->pop();
			this->pushLong(val);
		}
		break;

		case I2F:
		{
			float val = (float)(int) this->frame->operandStack->pop();
			this->frame->operandStack->push(val);
		}
		break;

		case I2D:
		{
			double val = (double)(int) this->frame->operandStack->pop();
			this->pushDouble(val);
		}
		break;

		case L2I:
		{
			int val = (int)this->getLongFromStack();
			this->frame->operandStack->push(val);
		}
		break;

		case L2F:
		{
			float val = (float)this->getLongFromStack();
			this->frame->operandStack->push(val);
		}
		break;

		case L2D:
		{
			double val = (double)this->getLongFromStack();
			this->pushDouble(val);
		}
		break;

		case F2I:
		{
			int val = (int)(float)this->frame->operandStack->pop();
			this->frame->operandStack->push(val);
		}
		break;

		case F2L:
		{
			long long val = (long long)(float)this->frame->operandStack->pop();
			this->pushLong(val);
		}
		break;

		case F2D:
		{
			double val = (double)(float) this->frame->operandStack->pop();
			this->pushDouble(val);
		}
		break;

		case D2I:
		{
			int val = (int)this->getDoubleFromStack();
			this->frame->operandStack->push(val);
		}
		break;

		case D2L:
		{
			long long val = (long long)this->getDoubleFromStack();
			this->pushLong(val);
		}
		break;

		case D2F:
		{
			float val = (float)this->getDoubleFromStack();
			this->frame->operandStack->push(val);
		}
		break;

		case I2B:
		{
			int val = (char)(int)this->frame->operandStack->pop();
			this->frame->operandStack->push(val);
		}
		break;

		case I2C:
		{
			int val = (java_char)(int)this->frame->operandStack->pop();
			this->frame->operandStack->push(val);
		}
		break;

		case I2S:
		{
			int val = (short)(int)this->frame->operandStack->pop();
			this->frame->operandStack->push(val);
		}
		break;


		case LCMP:
		{
			long long a = this->getLongFromStack();
			long long b = this->getLongFromStack();

			int res = 0;

			if (a > b)
			{
				res = 1;
			}
			else if (a == b)
			{
				res = 0;
			}
			else
			{
				res = -1;
			}

			this->frame->operandStack->push(res);
		}
		break;

		case FCMPL:
		case FCMPG:
		{
			float a = this->frame->operandStack->pop();
			float b = this->frame->operandStack->pop();

			this->fdcmp<float>(a, b, currentInstruction);
		}
		break;



		case DCMPL:
		case DCMPG:
		{
			double a = this->getDoubleFromStack();
			double b = this->getDoubleFromStack();

			this->fdcmp<double>(a, b, currentInstruction);
		}
		break;

		// THESE ARE FALL-THROUGH
		case IFEQ:
		case IFNE:
		case IFLT:
		case IFGE:
		case IFGT:
		case IFLE:
		{
			int value = this->frame->operandStack->pop();
			this->jumpIfEq(currentInstruction, value);
		}
		break;

		// THESE ARE FALL-THROUGH
		case IF_ICMPEQ:
		case IF_ICMPNE:
		case IF_ICMPLT:
		case IF_ICMPGE:
		case IF_ICMPGT:
		case IF_ICMPLE:
		{
			int b = this->frame->operandStack->pop();
			int a = this->frame->operandStack->pop();

			int res = a - b;
			this->jumpIfEq(currentInstruction - (IF_ICMPEQ - IFEQ), res);
		}
		break;


		// references eq - FALL-THROUGH
		case IF_ACMPEQ:
		case IF_ACMPNE:
		{
			short offset = this->getShort();
			unsigned short b = this->frame->operandStack->pop();
			unsigned short a = this->frame->operandStack->pop();

			if (a == b && currentInstruction == IF_ACMPEQ || a != b && currentInstruction == IF_ACMPNE)
			{
				this->jumpWithOffset(offset);
			}
		}
		break;

		// fall through
		case IFNULL:
		case IFNONNULL:
		{
			short offset = this->getShort();
			unsigned short ref = this->frame->operandStack->pop();

			if (ref == NULL && currentInstruction == IFNULL || ref != NULL && currentInstruction == IFNONNULL)
			{
				this->jumpWithOffset(offset);
			}
		}
		break;

		case GOTO:
		{
			short offset = this->getShort();
			this->jumpWithOffset(offset);
		}
		break;

		case GOTO_W:
		{
			int offset = (int)this->getInt();
			this->jumpWithOffset(offset);
		}
		break;

		case JSR:
			break;

		case JSR_W:
			break;


		case RET:
		case TABLESWITCH:
		{
			int switchPc = pc;

			// figure out padding
			while (pc % 4 != 0)
			{
				pc++;
			}

			int def = this->getInt();
			int low = this->getInt();
			int high = this->getInt();

			int index = this->frame->operandStack->pop();

			int offset = 0;

			if (index < low || index > high)
			{
				// default
				offset = def;
			}
			else
			{
				pc += (index - low) * 4;
				offset = this->getInt();
			}

			// high - low + 1
			pc = switchPc;
			this->jumpWithOffset(offset);
		}
		break;

		case LOOKUPSWITCH:
		{
			int switchPc = pc;

			// figure out padding
			while (pc % 4 != 0)
			{
				pc++;
			}

			int def = this->getInt();
			int n = this->getInt();

			int key = this->frame->operandStack->pop();
			bool matched = false;

			int offset = 0;

			for (int i = 0; i < n; i++)
			{
				int value = this->getInt();
				int currentOffset = this->getInt();

				if (value == key)
				{
					matched = true;
					offset = currentOffset;
					break;
				}
			}

			if (!matched)
			{
				offset = def;
			}

			pc = switchPc;
			this->jumpWithOffset(offset);
		}
		break;

		case FRETURN:
		case IRETURN:
		case ARETURN:
		{
			word reference = this->frame->operandStack->pop();
			this->frame->parentFrame->operandStack->push(reference);
			return 0;
		}
		break;


		case LRETURN:
		case DRETURN:
		{
			word low = this->frame->operandStack->pop();
			word high = this->frame->operandStack->pop();

			this->frame->parentFrame->operandStack->push(high);
			this->frame->parentFrame->operandStack->push(low);
			return 0;
		};

		case RETURN:
		{
			return 0;
		};

		case GETSTATIC:
		case PUTSTATIC:

		case GETFIELD:
		{
			unsigned short index = this->getShort();
			Object* reference = (Object*)this->frame->operandStack->pop();

			if (reference == NULL)
			{
				throw Exceptions::Runtime::NullPointerException();
			}

			size_t fieldIndex = 0;
			reference->fields[index];

		}
		break;

		case PUTFIELD:
		{
			unsigned short index = this->getShort();
			Object* reference = (Object*)this->frame->operandStack->pop();

			if (reference == NULL)
			{
				throw Exceptions::Runtime::NullPointerException();
			}

			size_t fieldIndex = 0;
			reference->fields[index];
		}
		break;

		case INVOKEVIRTUAL:
		case INVOKESPECIAL:
		case INVOKESTATIC:
		case INVOKEINTERFACE:
		case INVOKEDYNAMIC:

		case NEW:
		case NEWARRAY:
		{
			int size = this->frame->operandStack->pop();

			if (size < 0)
			{
				throw Exceptions::Runtime::NegativeArraySizeException();
			}
		}


		case ANEWARRAY:
		case MULTIANEWARRAY:
		case ARRAYLENGTH:
		case ATHROW:


		case CHECKCAST:
		case INSTANCEOF:
		{
			Object* ref = NULL;
			Object* resolved = NULL;

			if (ref->objectClass == resolved->objectClass)
			{
				// same classes
			}

			// if ref is class
				// if resolved is class -> same or parent of ref
				// resolved is interface -> ref implements resolved
			// if res is interface
				// if resolved is class -> resolved is object
				// if resolved is interface -> ref is same or extends resolved
			// ref is array
				// if resolved is class -> object
				// if resolved is interface -> must be implemented by array
				// if resolved is array -> same primitive array type
				//  ref and resolved are reference arrays - ref item must be castable to resolved item
		}
		break;

		// currently not implemented! 
		case MONITORENTER:
		case MONITOREXIT:
			break;

		case WIDE:
		{
			Instruction modifiedInstruction = instructions[pc++];
			size_t index = this->getShort();

			switch (modifiedInstruction)
			{
			case ILOAD:
			case FLOAD:
			case ALOAD:
				this->singleWordLoad(index);
				break;
			case DLOAD:
			case LLOAD:
				break;
			case ISTORE:
			case FSTORE:
			case ASTORE:
				break;
			case DSTORE:
			case LSTORE:
				break;
			case RET:
				break;
			case IINC:
				word value = this->getShort();
				this->iinc(index, value);
				break;
			}
		}
		break;

		default:
		case NOP:
			break;

		// Reserved: (should not be loaded in classFile)
		case BREAKPOINT:
		//(NO NAME) = 0xCB - 0xFD,
		case IMPDEP1:
		case IMPDEP2:
			break;
		}
	}

	return 0;
}
