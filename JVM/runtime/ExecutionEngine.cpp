#include "ExecutionEngine.h"

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
			this->frame->stack.push(NULL);
			break;
		
		// FALL THROUGH:
		case ICONST_M1:
		case ICONST_0:
		case ICONST_1:
		case ICONST_2:
		case ICONST_3:
		case ICONST_4:
		case ICONST_5:
			this->frame->stack.push(currentInstruction - ICONST_0);
			break;

		case LCONST_0:
		case LCONST_1:
			this->pushLong(currentInstruction - LCONST_0);
			break;

		case FCONST_0:
		case FCONST_1:
		case FCONST_2:
			this->frame->stack.push(currentInstruction  -  FCONST_0);
			break;

		case DCONST_0:
		case DCONST_1:
			this->pushDouble(currentInstruction - DCONST_0);
			break;

		case BIPUSH:
			{
				// push byte
				java_byte byte = (java_byte)instructions[pc++];
				this->frame->stack.push(JavaByte(byte));
			}
			break;

		case SIPUSH:
			{
				// push short
				// byte 1
				// byte 2
				unsigned short index = getShort();
				this->frame->stack.push(JavaShort(index));
			}
			break;

		case LDC:
			/*
			int or float, or a reference to a string literal, or a symbolic reference to a class, method type, or method handle
			*/
			// push item from constant-pool
			unsigned char index = instructions[pc++];
			// index

		case LDC_W:
			// push item from constant-pool
			unsigned short index = getShort();
			// index 1
			// index 2
			break;

		case LDC2_W:
			// push long/double from constant-pool
			// index 1
			// index 2
			unsigned short index = getShort();
			break;

		case ILOAD:
			// load from local variable 
			// index
			unsigned char index = instructions[pc++];
			this->iload(index);
			break;

		// FALL THROUGH
		case ILOAD_0:
		case ILOAD_1:
		case ILOAD_2:
		case ILOAD_3:
			this->iload(currentInstruction - ILOAD_0);
			break;

		case LLOAD:
			unsigned char index = instructions[pc++];
			this->lload(index);
			break;

		case LLOAD_0:
		case LLOAD_1:
		case LLOAD_2:
		case LLOAD_3:
			this->lload(currentInstruction - LLOAD_0);
			break;

		case FLOAD:
			unsigned char index = instructions[pc++];
			this->fload(index);
			break;

		case FLOAD_0:
		case FLOAD_1:
		case FLOAD_2:
		case FLOAD_3:
			this->fload(currentInstruction - FLOAD_0);
			break;

		case DLOAD:
			unsigned char index = instructions[pc++];
			this->dload(index);
			break;

		case DLOAD_0:
		case DLOAD_1:
		case DLOAD_2:
		case DLOAD_3:
			this->dload(currentInstruction - DLOAD_0);
			break;

		case ALOAD:

		case ALOAD_0:
		case ALOAD_1:
		case ALOAD_2:
		case ALOAD_3:

		case IALOAD:
		case LALOAD:
		case FALOAD:
		case DALOAD:
		case AALOAD:
		case BALOAD:
		case CALOAD:
		case SALOAD:

		case ISTORE:
			unsigned char index = instructions[pc++];
			this->istore(index);
			// store int into local variable
			break;
		case ISTORE_0:
			this->istore(0);
			break;
		case ISTORE_1:
			this->istore(1);
			break;
		case ISTORE_2:
			this->istore(2);
			break;
		case ISTORE_3:
			this->istore(3);
			break;

		case LSTORE:
			unsigned char index = instructions[pc++];
			this->lstore(index);
			break;
		case LSTORE_0:
			this->lstore(0);
			break;
		case LSTORE_1:
			this->lstore(1);
			break;
		case LSTORE_2:
			this->lstore(2);
			break;
		case LSTORE_3:
			this->lstore(3);
			break;

		case FSTORE:
			unsigned char index = instructions[pc++];
			this->fstore(index);
			break;
		case FSTORE_0:
			this->fstore(0);
			break;
		case FSTORE_1:
			this->fstore(1);
			break;
		case FSTORE_2:
			this->fstore(2);
			break;
		case FSTORE_3:
			this->fstore(3);
			break;

		case DSTORE:
			unsigned char index = instructions[pc++];
			this->dstore(index);
			break;
		case DSTORE_0:
			this->dstore(0);
			break;
		case DSTORE_1:
			this->dstore(1);
			break;
		case DSTORE_2:
			this->dstore(2);
			break;
		case DSTORE_3:
			this->dstore(3);
			break;

		case ASTORE:
			unsigned char index = instructions[pc++];
			this->astore(index);
			break;
		case ASTORE_0:
			this->astore(0);
			break;
		case ASTORE_1:
			this->astore(1);
			break;
		case ASTORE_2:
			this->astore(2);
			break;
		case ASTORE_3:
			this->astore(3);
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
			this->frame->operandStack.pop();
			break;
		case POP2:

		case DUP:
			// value
			// value, value
			word value = this->frame->operandStack.pop();
			this->frame->operandStack.push(value);
			this->frame->operandStack.push(value);
			break;
		case DUP_X1:
			// TODO: 
			// value2, value1
			// value1, value2, value1

		case DUP_X2:
		case DUP2:
		case DUP2_X1:
		case DUP2_X2:

		case SWAP:
			{
				// swap operand-stack values
				// category 1
				word low = this->frame->operandStack.pop();
				word high = this->frame->operandStack.pop();
				this->frame->operandStack.push(low);
				this->frame->operandStack.push(high);
			}
			break;

		case IADD:
			{
				int a = this->frame->stack.pop();
				int b = this->frame->stack.pop();
				this->frame->stack.push(JavaInt(a + b));
			}
			break;

		case LADD:
			long long a = this->getLongFromStack();
			long long b = this->getLongFromStack();
			this->pushLong(a + b);
			break;

		case FADD:
			float a = this->frame->stack.pop();
			float b = this->frame->stack.pop();
			this->frame->stack.push(JavaFloat(a + b));
			break;

		case DADD:
			double a = this->getDoubleFromStack();
			double b = this->getDoubleFromStack();
			this->pushDouble(a + b);
			break;

		case ISUB:
			int a = this->frame->stack.pop();
			int b = this->frame->stack.pop();
			this->frame->stack.push(JavaInt(a - b));
			break;

		case LSUB:
			long long a = this->getLongFromStack();
			long long b = this->getLongFromStack();
			this->pushLong(a - b);
			break;

		case FSUB:
			float a = this->frame->stack.pop();
			float b = this->frame->stack.pop();
			this->frame->stack.push(JavaFloat(a - b));
			break;

		case DSUB:
			double a = this->getDoubleFromStack();
			double b = this->getDoubleFromStack();
			this->pushDouble(a - b);
			break;

		case IMUL:
			int a = this->frame->stack.pop();
			int b = this->frame->stack.pop();
			this->frame->stack.push(JavaInt(a * b));
			break;


		case LMUL:
			long long a = this->getLongFromStack();
			long long b = this->getLongFromStack();
			this->pushLong(a * b);
			break;

		case FMUL:
			float a = this->frame->stack.pop();
			float b = this->frame->stack.pop();
			this->frame->stack.push(JavaFloat(a * b));
			break;

		case DMUL:
			double a = this->getDoubleFromStack();
			double b = this->getDoubleFromStack();
			this->pushDouble(a * b);
			break;

		case IDIV:
			int a = this->frame->stack.pop();
			int b = this->frame->stack.pop();

			if (b == 0)
			{
				// exception! 
			}

			this->frame->stack.push(JavaInt(a * b));
			break;


		case LDIV:
			long a = this->getLongFromStack();
			long b = this->getLongFromStack();

			if (b == 0)
			{
				// exception! 
			}

			this->pushLong(a / b);
			break;

		case FDIV:
			float a = this->frame->stack.pop();
			float b = this->frame->stack.pop();
			this->frame->stack.push(JavaFloat(a / b));
			break;

		case DDIV:
			double a = this->getDoubleFromStack();
			double b = this->getDoubleFromStack();
			this->pushDouble(a / b);
			break;

		case IREM:
			// returns remainder
			int a = this->frame->stack.pop();
			int b = this->frame->stack.pop();

			if (b == 0)
			{
				// exception! 
			}

			this->frame->stack.push(JavaInt(a % b));
			break;

		case LREM:
			long a = this->getLongFromStack();
			long b = this->getLongFromStack();

			if (b == 0)
			{
				// exception! 
			}

			this->pushLong(a % b);
			break;

		case FREM:
			float a = this->frame->stack.pop();
			float b = this->frame->stack.pop();
			this->frame->stack.push(fmodf(a, b));
			break;

		case DREM:
			double a = this->getDoubleFromStack();
			double b = this->getDoubleFromStack();
			this->pushDouble(fmod(a, b));
			break;

		case INEG:
			int a = this->frame->stack.pop();
			this->frame->operandStack.push(-a);
			break;

		case LNEG:
			long a = this->getLongFromStack();
			this->pushLong(-a);
			break;

		case FNEG:
			float a = this->frame->stack.pop();
			this->frame->stack.push(-a);
			break;

		case DNEG:
			double a = this->getDoubleFromStack();
			this->pushDouble(-a);
			break;


		case ISHL:
			// shift left
			int a = this->frame->stack.pop();
			int b = this->frame->stack.pop();
			this->frame->operandStack.push(a << b);
			break;

		case LSHL:
			long long a = this->getLongFromStack();
			int b = this->frame->stack.pop();
			this->pushLong(a << b);
			break;

		case ISHR:
			int a = this->frame->stack.pop();
			int b = this->frame->stack.pop();
			this->frame->operandStack.push(a >> b);
			break;

		case LSHR:
			// shift right
			long long a = this->getLongFromStack();
			int b = this->frame->stack.pop();
			this->pushLong(a >> b);
			break;

		case IUSHR:
			// shift unsigned right
			unsigned int a = this->frame->stack.pop();
			unsigned int b = this->frame->stack.pop();
			this->frame->operandStack.push(a >> b);
			break;

		case LUSHR:
			unsigned long long a = this->getLongFromStack();
			unsigned int b = this->frame->stack.pop();
			this->pushLong(a >> b);
			break;

		case IAND:
			int a = this->frame->stack.pop();
			int b = this->frame->stack.pop();
			this->frame->operandStack.push(a & b);
			break;

		case LAND:
			long long a = this->getLongFromStack();
			long long b = this->getLongFromStack();
			this->pushLong(a & b);
			break;

		case IOR:
			int a = this->frame->stack.pop();
			int b = this->frame->stack.pop();
			this->frame->operandStack.push(a | b);
			break;

		case LOR:
			long long a = this->getLongFromStack();
			long long b = this->getLongFromStack();
			this->pushLong(a | b);
			break;

		case IXOR:
			int a = this->frame->stack.pop();
			int b = this->frame->stack.pop();
			this->frame->operandStack.push(a ^ b);
			break;

		case LXOR:
			long long a = this->getLongFromStack();
			long long b = this->getLongFromStack();
			this->pushLong(a ^ b);
			break;

		case IINC:
			unsigned char index = instructions[pc++];
			int value = (int)instructions[pc++];
			this->frame->localVariables[index] += value;
			break;

		case I2L:
		case I2F:
		case I2D:
		case L2I:
		case L2F:
		case L2D:
		case F2I:
		case F2L:
		case F2D:
		case D2I:
		case D2L:
		case D2F:
		case I2B:
		case I2C:
		case I2S:

		case LCMP:
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

			this->frame->operandStack.push(res);
			break;

		case FCMPL:
		case FCMPG:
			float a = this->frame->operandStack.pop();
			float b = this->frame->operandStack.pop();

			int res = 0;

			if (a > b)
			{
				res = 1;
			}
			else if (a == b)
			{
				res = 0;
			}
			else if (a < b)
			{
				res = -1;
			}
			else if ((a == NAN || b == NAN))
			{
				res = pc == FCMPG ? 1 : -1;
			}

			this->frame->operandStack.push(res);
			break;



		case DCMPL:
		case DCMPG:
			double a = this->getDoubleFromStack();
			double b = this->getDoubleFromStack();

			int res = 0;

			if (a > b)
			{
				res = 1;
			}
			else if (a == b)
			{
				res = 0;
			}
			else if (a < b)
			{
				res = -1;
			}
			else if ((a == NAN || b == NAN))
			{
				res = (currentInstruction == DCMPG) ? 1 : -1;
			}

			this->frame->operandStack.push(res);
			break;

		// THESE ARE FALL-THROUGH
		case IFEQ:
		case IFNE:
		case IFLT:
		case IFGE:
		case IFGT:
		case IFLE:
			int value = this->frame->operandStack.pop();
			this->jumpIfEq(currentInstruction, value);
			break;

		// THESE ARE FALL-THROUGH
		case IF_ICMPEQ:
		case IF_ICMPNE:
		case IF_ICMPLT:
		case IF_ICMPGE:
		case IF_ICMPGT:
		case IF_ICMPLE:
			int a = this->frame->operandStack.pop();
			int b = this->frame->operandStack.pop();

			int res = a - b;
			this->jumpIfEq(currentInstruction - (IF_ICMPEQ - IFEQ), res);
			break;


		case IF_ACMPEQ:
			// references eq
		case IF_ACMPNE:
			unsigned short pc = this->getShort();
			unsigned short a = this->frame->operandStack.pop();
			unsigned short b = this->frame->operandStack.pop();

			if (a == b && currentInstruction == IF_ACMPEQ || a != b && currentInstruction == IF_ACMPNE)
			{
				// JUMP
			}
			break;

		case GOTO:
			short offset = this->getShort();
			pc = pc + offset - 1; // check
			break;

		case GOTO_W:
			int offset = (int)this->getInt();
			pc = pc + offset - 1;
			break;

		case JSR:
			break;

		case JSR_W:
			break;


		case RET:
		case TABLESWITCH:
		case LOOKUPSWITCH:
		 
		case IRETURN:
		case LRETURN:
		case FRETURN:
		case DRETURN:
		case ARETURN:
		case RETURN:
		 
		case GETSTATIC:
		case PUTSTATIC:

		case GETFIELD:
			unsigned short index = this->getShort();
			break;

		case PUTFIELD:
			unsigned short index = this->getShort();
			break;

		case INVOKEVIRTUAL:
		case INVOKESPECIAL:
		case INVOKESTATIC:
		case INVOKEINTERFACE:
		case INVOKEDYNAMIC:
		 
		case NEW:
		case NEWARRAY:
		case ANEWARRAY:
		case ARRAYLENGTH:
		case ATHROW:
		case CHECKCAST:
		case INSTANCEOF:
		case MONITORENTER:
		case MONITOREXIT:
		case WIDE:
		case MULTIANEWARRAY:
		case IFNULL:
		case IFNONNULL:


		default:
		// Reserved: (should not be loaded in classFile)
		case BREAKPOINT:
		//(NO NAME) = 0xCB - 0xFD,
		case IMPDEP1:
		case IMPDEP2:
			break;
		case InstructionSet::NOP:
			break;
		}
	}

	return 0;
}
