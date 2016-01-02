#include <iostream>
#include <string>
#include "debug.h"
#include "../runtime/OperandStack.h"
#include "../types/ConversionFunctions.h"
#include "../runtime/MethodFrame.h"

const char* namedInstructions[] = {
	"NOP",

	"ACONST_NULL",

	"ICONST_M1",
	"ICONST_0",
	"ICONST_1",
	"ICONST_2",
	"ICONST_3",
	"ICONST_4",
	"ICONST_5",
	"LCONST_0",
	"LCONST_1",
	"FCONST_0",
	"FCONST_1",
	"FCONST_2",
	"DCONST_0",
	"DCONST_1",

	"BIPUSH",
	"SIPUSH",

	"LDC",
	"LDC_W",
	"LDC2_W",

	"ILOAD",
	"LLOAD",
	"FLOAD",
	"DLOAD",
	"ALOAD",
	"ILOAD_0",
	"ILOAD_1",
	"ILOAD_2",
	"ILOAD_3",
	"LLOAD_0",
	"LLOAD_1",
	"LLOAD_2",
	"LLOAD_3",
	"FLOAD_0",
	"FLOAD_1",
	"FLOAD_2",
	"FLOAD_3",
	"DLOAD_0",
	"DLOAD_1",
	"DLOAD_2",
	"DLOAD_3",
	"ALOAD_0",
	"ALOAD_1",
	"ALOAD_2",
	"ALOAD_3",
	"IALOAD",
	"LALOAD",
	"FALOAD",
	"DALOAD",
	"AALOAD",
	"BALOAD",
	"CALOAD",
	"SALOAD",

	"ISTORE",
	"LSTORE",
	"FSTORE",
	"DSTORE",
	"ASTORE",
	"ISTORE_0",
	"ISTORE_1",
	"ISTORE_2",
	"ISTORE_3",
	"LSTORE_0",
	"LSTORE_1",
	"LSTORE_2",
	"LSTORE_3",
	"FSTORE_0",
	"FSTORE_1",
	"FSTORE_2",
	"FSTORE_3",
	"DSTORE_0",
	"DSTORE_1",
	"DSTORE_2",
	"DSTORE_3",
	"ASTORE_0",
	"ASTORE_1",
	"ASTORE_2",
	"ASTORE_3",
	"IASTORE",
	"LASTORE",
	"FASTORE",
	"DASTORE",
	"AASTORE",
	"BASTORE",
	"CASTORE",
	"SASTORE",

	"POP",
	"POP2",

	"DUP",
	"DUP_X1",
	"DUP_X2",
	"DUP2",
	"DUP2_X1",
	"DUP2_X2",
	"SWAP",

	"IADD",
	"LADD",
	"FADD",
	"DADD",

	"ISUB",
	"LSUB",
	"FSUB",
	"DSUB",

	"IMUL",
	"LMUL",
	"FMUL",
	"DMUL",

	"IDIV",
	"LDIV",
	"FDIV",
	"DDIV",

	"IREM",
	"LREM",
	"FREM",
	"DREM",

	"INEG",
	"LNEG",
	"FNEG",
"DNEG",

"ISHL",
"LSHL",
"ISHR",
"LSHR",
"IUSHR",
"LUSHR",

"IAND",
"LAND",

"IOR",
"LOR",

"IXOR",
"LXOR",

"IINC",

"I2L",
"I2F",
"I2D",
"L2I",
"L2F",
"L2D",
"F2I",
"F2L",
"F2D",
"D2I",
"D2L",
"D2F",
"I2B",
"I2C",
"I2S",
"LCMP",
"FCMPL",
"FCMPG",
"DCMPL",
"DCMPG",

"IFEQ",
"IFNE",
"IFLT",
"IFGE",
"IFGT",
"IFLE",
"IF_ICMPEQ",
"IF_ICMPNE",
"IF_ICMPLT",
"IF_ICMPGE",
"IF_ICMPGT",
"IF_ICMPLE",
"IF_ACMPEQ",
"IF_ACMPNE",

"GOTO",
"JSR",
"RET",
"TABLESWITCH",
"LOOKUPSWITCH",

"IRETURN",
"LRETURN",
"FRETURN",
"DRETURN",
"ARETURN",
"RETURN",

"GETSTATIC",
"PUTSTATIC",
"GETFIELD",
"PUTFIELD",

"INVOKEVIRTUAL",
"INVOKESPECIAL",
"INVOKESTATIC",
"INVOKEINTERFACE",
"INVOKEDYNAMIC",

"NEW",
"NEWARRAY",
"ANEWARRAY",
"ARRAYLENGTH",
"ATHROW",
"CHECKCAST",
"INSTANCEOF",
"MONITORENTER",
"MONITOREXIT",
"WIDE",
"MULTIANEWARRAY",
"IFNULL",
"IFNONNULL",
"GOTO_W",
"JSR_W"
};

const char** getNamedInstructions()
{
	return namedInstructions;
}

void printValue(word value)
{
	std::cerr << (unsigned int)value;

	if (isReferenceAddress(value))
	{
		std::cerr << " reference to index: " << (int)getReferenceAddress(value);
	}

	std::cerr << std::endl;
}

void printValue(doubleWord value, TypeTag type)
{
	if (type == TypeTag::DOUBLE) 
	{
		std::cerr << "Value: " << (double)value << std::endl;
	}
	else if (type == TypeTag::LONG) 
	{
		std::cerr << "Value: " << (long long)value << std::endl;
	}
}

void printOperandStack(OperandStack* stack)
{
	std::cerr << "Printing stack from the top: " << std::endl;

	std::cerr << std::string(10, '-') << std::endl;
	for (int i = stack->index - 1; i >= 0; i--)
	{
		word value = stack->operator[](i);
		printValue(value);
	}

	std::cerr << std::string(10, '-') << std::endl;
}

void printLocalVariables(MethodFrame * frame)
{
	std::cerr << "Printing local variables: " << std::endl;

	std::cerr << std::string(10, '-') << std::endl;

	int size = frame->method->countIntputArgs;

	int index = 0;

	for (int i = 0; i < size; i++)
	{
		TypeTag argType = frame->method->inputArgs[i];

		std::cerr << "Index: " << index << " ";

		switch (argType)
		{
		case TypeTag::LONG:
		case TypeTag::DOUBLE:
			{
				doubleWord doubleWord = frame->localVariables->get2(index);
				printValue(doubleWord, argType);
				index += 2;
			}
			break;
		default:
			{
				word word = frame->localVariables->get(index);
				printValue(word);
				index++;
			}
			break;
		}
	}

	std::cerr << std::string(10, '-') << std::endl;
}
