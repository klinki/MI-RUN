#include "ExecutionEngine.h"



ExecutionEngine::ExecutionEngine()
{
}


ExecutionEngine::~ExecutionEngine()
{
}

int ExecutionEngine::execute(Instruction instructions[], unsigned int length)
{
	ProgramCounter pc = 0;
	

	while (pc != length)
	{
		Instruction currentInstruction = instructions[pc++];

		switch (currentInstruction)
		{
		default:
			break;
		case InstructionSet::NOP:
			break;
		case InstructionSet::ACONST_NULL:
			// push null to operand stack
			break;
		case InstructionSet::ICONST_M1:
			// push integer to operand stack
			break;
		case InstructionSet::ICONST_0:
			break;
		case ICONST_1:
			break;
		case ICONST_2:
			break;
		case ICONST_3:
		case ICONST_4:
		case ICONST_5:
		case LCONST_0:
		case LCONST_1:
		case FCONST_0:
		case FCONST_1:
		case FCONST_2:
		case DCONST_0:
		case DCONST_1:
			break;

		case BIPUSH:
			// push byte
			// byte
		case SIPUSH:
			// push short
			// byte 1
			// byte 2

		case LDC:
			// push item from constant-pool
			// index
		case LDC_W:
			// push item from constant-pool
			// index 1
			// index 2
		case LDC2_W:
			// push long/double from constant-pool
			// index 1
			// index 2

		case ILOAD:
			// load from local variable 
			// index
		case LLOAD:
		case FLOAD:
		case DLOAD:
		case ALOAD:

		case ILOAD_0:
		case ILOAD_1:
		case ILOAD_2:
		case ILOAD_3:
		case LLOAD_0:
		case LLOAD_1:
		case LLOAD_2:
		case LLOAD_3:
		case FLOAD_0:
		case FLOAD_1:
		case FLOAD_2:
		case FLOAD_3:
		case DLOAD_0:
		case DLOAD_1:
		case DLOAD_2:
		case DLOAD_3:
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
			// store int into local variable
		case LSTORE:
		case FSTORE:
		case DSTORE:
		case ASTORE:
		case ISTORE_0:
		case ISTORE_1:
		case ISTORE_2:
		case ISTORE_3:
		case LSTORE_0:
		case LSTORE_1:
		case LSTORE_2:
		case LSTORE_3:
		case FSTORE_0:
		case FSTORE_1:
		case FSTORE_2:
		case FSTORE_3:
		case DSTORE_0:
		case DSTORE_1:
		case DSTORE_2:
		case DSTORE_3:

		case ASTORE_0:
		case ASTORE_1:
		case ASTORE_2:
		case ASTORE_3:
		case IASTORE:
		case LASTORE:
		case FASTORE:
		case DASTORE:
		case AASTORE:
		case BASTORE:
		case CASTORE:
		case SASTORE:

		case POP:
			// pop value from stack
		case POP2:

		case DUP:
		case DUP_X1:
		case DUP_X2:
		case DUP2:
		case DUP2_X1:
		case DUP2_X2:
		
		case SWAP:
			// swap operand-stack values
			// category 1
		
		case IADD:
		case LADD:
		case FADD:
		case DADD:
		
		case ISUB:
		case LSUB:
		case FSUB:
		case DSUB:
		
		case IMUL:
		case LMUL:
		case FMUL:
		case DMUL:
		 
		case IDIV:
		case LDIV:
		case FDIV:
		case DDIV:
		 
		case IREM:
			// returns remainder
		case LREM:
		case FREM:
		case DREM:
		 
		case INEG:
		case LNEG:
		case FNEG:
		case DNEG:
		 
		case ISHL:
			// shift left
		case LSHL:
		case ISHR:
		case LSHR:
			// shift right
		case IUSHR:
			// shift unsigned right
		case LUSHR:
		 
		case IAND:
		case LAND:
		 
		case IOR:
		case LOR:
		 
		case IXOR:
		case LXOR:
		 
		case IINC:
		 
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
		case FCMPL:
		case FCMPG:
		case DCMPL:
		case DCMPG:
		 
		case IFEQ:
		case IFNE:
		case IFLT:
		case IFGE:
		case IFGT:
		case IFLE:
		case IF_ICMPEQ:
		case IF_ICMPNE:
		case IF_ICMPLT:
		case IF_ICMPGE:
		case IF_ICMPGT:
		case IF_ICMPLE:
		case IF_ACMPEQ:
		case IF_ACMPNE:
		 
		case GOTO:
		case JSR:
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
		case PUTFIELD:
		 
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
		case GOTO_W:
		case JSR_W:

		// Reserved: (should not be loaded in classFile)
		case BREAKPOINT:
		//(NO NAME) = 0xCB - 0xFD,
		case IMPDEP1:
		case IMPDEP2:
			break;

		}

	}
}
