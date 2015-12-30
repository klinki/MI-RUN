#include "ExecutionEngine.h"
#include "../jvm_structures/JavaConstantPool.h"
#include "../runtime/TypeDescriptors.h"
#include "Runtime.h"
#include "../natives/java/lang/Throwable.h"

#ifdef _DEBUG
	#include "../utils/debug.h"
	#include <iomanip>
#endif

ExecutionEngine::ExecutionEngine()
{
	this->callStack = new OperandStack(1024);
	this->objectTable = new ObjectTable();
        this->frame = NULL;
        this->heap = NULL;
        this->classMap = NULL;
        this->runtime = NULL;
}

ExecutionEngine::ExecutionEngine(Runtime * runtime)
{
	this->runtime = runtime;
	this->objectTable = runtime->objectTable;
	this->heap = runtime->heap;
	this->classMap = runtime->classTable;
        this->frame = NULL;
        
	this->callStack = new OperandStack(1024);
}

ExecutionEngine::~ExecutionEngine()
{
	delete this->callStack;
}

bool ExecutionEngine::handleException(java::lang::Throwable::Throwable* e)
{
	size_t exceptionIndex = this->getCurrentMethodFrame()->operandStack->top();

	e->addStackTrace(this->getCurrentMethodFrame()->method);

	ProgramCounter & pc = this->getCurrentMethodFrame()->pc;

	ExceptionTable * table = this->getCurrentMethodFrame()->method->exceptionTable;
	size_t countExceptions = table->getSize();

	for (size_t i = 0; i < countExceptions; i++)
	{
		Exception & exception = (*table)[i];

		if (pc >= exception.start_pc && pc <= exception.end_pc)
		{
			// NULL objectClass is for finally block
			if (exception.classPtr == NULL || e->objectClass == exception.classPtr || e->objectClass->isSubclassOf(exception.classPtr))
			{
				pc = exception.handler_pc;
				this->getCurrentMethodFrame()->operandStack->clear();
				this->getCurrentMethodFrame()->operandStack->push(exceptionIndex);
				return true;
			}
		}
	}

	return false;
}

void ExecutionEngine::execute(Method* method)
{
	unsigned char* memory = this->runtime->heap->allocate(MethodFrame::getMemorySize(method->operandStackSize, method->localVariablesArraySize));
	MethodFrame * frame = new (memory) MethodFrame(
		method->operandStackSize,
		method->localVariablesArraySize,
		NULL,
		method->classPtr->constantPool,
		method,
		NULL
		);
	this->execute(frame);
}

int ExecutionEngine::execute(MethodFrame * frame)
{
	word index = this->objectTable->insert(frame);
	this->callStack->push(index);

	Instruction * instructions = (Instruction*)frame->method->getBytecode();
	unsigned int length = frame->method->getByteCodeLength();

	ProgramCounter & pc = frame->pc;
	
	while (pc < length)
	{
		try
		{
			Instruction currentInstruction = instructions[pc++];

#ifdef _DEBUG
			if (this->runtime->parameters.PrintExecutedInstructions) {
				std::cerr << std::endl;
				std::cerr << std::string(this->callStack->index - 1, '\t').c_str();
				std::cerr << std::setw(20) << std::left << namedInstructions[currentInstruction] << "\t\tSTACK BEFORE: " << frame->operandStack->index;
			}
#endif
			switch (currentInstruction)
			{
			case ACONST_NULL:
				frame->operandStack->pushReference(NULL);
				break;

				// FALL THROUGH:
			case ICONST_M1:
			case ICONST_0:
			case ICONST_1:
			case ICONST_2:
			case ICONST_3:
			case ICONST_4:
			case ICONST_5:
				frame->operandStack->push(currentInstruction - ICONST_0);
				break;

				// FALL THROUGH:
			case LCONST_0:
			case LCONST_1:
				frame->operandStack->push2((long long)(currentInstruction - LCONST_0));
				break;

				// FALL THROUGH:
			case FCONST_0:
			case FCONST_1:
			case FCONST_2:
				frame->operandStack->push((float)(currentInstruction - FCONST_0));
				break;

				// FALL THROUGH:
			case DCONST_0:
			case DCONST_1:
				frame->operandStack->push2((double)(currentInstruction - DCONST_0));
				break;

			case BIPUSH:
			{
				// push byte
				word byte = instructions[pc++];
				frame->operandStack->push(byte);
			}
			break;

			case SIPUSH:
			{
				// push short
				// byte 1
				// byte 2
				unsigned short index = getShort();
				frame->operandStack->push(index);
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
				this->arrayLoad<int>();
				break;

			case LALOAD:
				this->arrayLoad2<java_long>();
				break;

			case FALOAD:
				this->arrayLoad<float>();
				break;

			case DALOAD:
				this->arrayLoad2<java_double>();
				break;

			case AALOAD:
				this->arrayLoad<int>();
				break;

			case BALOAD:
				this->arrayLoad<bool>();
				break;

			case CALOAD:
				this->arrayLoad<java_char>();
				break;

			case SALOAD:
				this->arrayLoad<java_short>();
				break;

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
				this->arrayStore<int>();
				break;

			case FASTORE:
				this->arrayStore<float>();
				break;

			case AASTORE:
				this->arrayStore<int>();
				break;

			case BASTORE:
				this->arrayStore<bool>();
				break;

			case CASTORE:
				this->arrayStore<java_char>();
				break;

			case SASTORE:
				this->arrayStore<short>();
				break;

			case LASTORE:
				this->arrayStore2<java_long>();
				break;

			case DASTORE:
				this->arrayStore2<double>();
				break;

			case POP:
				// pop value from stack
				frame->operandStack->pop();
				break;

			case POP2:
				frame->operandStack->pop();
				frame->operandStack->pop();
				break;

			case DUP:
			{
				// value
				// value, value
				word value = frame->operandStack->pop();
				frame->operandStack->push(value);
				frame->operandStack->push(value);
			}
			break;

			case DUP_X1:
			{
				// value2, value1
				// value1, value2, value1
				word a = frame->operandStack->pop();
				word b = frame->operandStack->pop();
				frame->operandStack->push(a);
				frame->operandStack->push(b);
				frame->operandStack->push(a);
			}
			break;

			case DUP_X2:
			{
				// value3, value2, value1
				// value1, value3, value2, value1
				word a = frame->operandStack->pop();
				word b = frame->operandStack->pop();
				word c = frame->operandStack->pop();

				frame->operandStack->push(a);
				frame->operandStack->push(c);
				frame->operandStack->push(b);
				frame->operandStack->push(a);
			};
			break;

			case DUP2:
			{
				word a = frame->operandStack->pop();
				word b = frame->operandStack->pop();
				frame->operandStack->push(b);
				frame->operandStack->push(a);
				frame->operandStack->push(b);
				frame->operandStack->push(a);
			}
			break;

			case DUP2_X1:
			{
				// value3, value2, value1
				// value2, value1, value3, value2, value1
				word a = frame->operandStack->pop();
				word b = frame->operandStack->pop();
				word c = frame->operandStack->pop();

				frame->operandStack->push(b);
				frame->operandStack->push(a);
				frame->operandStack->push(c);
				frame->operandStack->push(b);
				frame->operandStack->push(a);
			}
			break;

			case DUP2_X2:
			{
				// value4, value3, value2, value1
				// value2, value1, value4, value3, value2, value1
				word a = frame->operandStack->pop();
				word b = frame->operandStack->pop();
				word c = frame->operandStack->pop();
				word d = frame->operandStack->pop();

				frame->operandStack->push(b);
				frame->operandStack->push(a);
				frame->operandStack->push(d);
				frame->operandStack->push(c);
				frame->operandStack->push(b);
				frame->operandStack->push(a);
			}
			break;

			case SWAP:
			{
				// swap operand-stack values
				// category 1
				word low = frame->operandStack->pop();
				word high = frame->operandStack->pop();
				frame->operandStack->push(low);
				frame->operandStack->push(high);
			}
			break;

			case IADD:
			{
				SINGLE_WORD_OPERATION(int, +);
			}
			break;

			case LADD:
			{
				DOUBLE_WORD_OPERATION(long long, +);
			}
			break;

			case FADD:
			{
				SINGLE_WORD_OPERATION(float, +);
			}
			break;

			case DADD:
			{
				DOUBLE_WORD_OPERATION(double, +);
			}
			break;

			case ISUB:
			{
				SINGLE_WORD_OPERATION(int, -);
			}
			break;

			case LSUB:
			{
				DOUBLE_WORD_OPERATION(long long, -);
			}
			break;

			case FSUB:
			{
				SINGLE_WORD_OPERATION(float, -);
			}
			break;

			case DSUB:
			{
				DOUBLE_WORD_OPERATION(double, -);
			}
			break;

			case IMUL:
			{
				SINGLE_WORD_OPERATION(int, *);
			}
			break;


			case LMUL:
			{
				DOUBLE_WORD_OPERATION(long long, *);
			}
			break;

			case FMUL:
			{
				SINGLE_WORD_OPERATION(float, *);
			}
			break;

			case DMUL:
			{
				DOUBLE_WORD_OPERATION(double, *);
			}
			break;

			case IDIV:
			{
				int b = frame->operandStack->pop();
				int a = frame->operandStack->pop();

				if (b == 0)
				{
					// exception! 
					throw Exceptions::Runtime::ArithmeticException();
				}

				frame->operandStack->push(a / b);
			}
			break;


			case LDIV:
			{
				long long b = frame->operandStack->pop2();
				long long a = frame->operandStack->pop2();

				if (b == 0)
				{
					// exception! 
					throw Exceptions::Runtime::ArithmeticException();
				}

				frame->operandStack->push2(a / b);
			}
			break;

			case FDIV:
			{
				SINGLE_WORD_OPERATION(float, / );
			}
			break;

			case DDIV:
			{
				DOUBLE_WORD_OPERATION(double, / );
			}
			break;

			case IREM:
			{
				// returns remainder
				int b = frame->operandStack->pop();
				int a = frame->operandStack->pop();

				if (b == 0)
				{
					// exception!
					throw Exceptions::Runtime::ArithmeticException();
				}

				frame->operandStack->push(a % b);
			}
			break;

			case LREM:
			{
				long long b = frame->operandStack->pop2();
				long long a = frame->operandStack->pop2();

				if (b == 0)
				{
					// exception!
					throw Exceptions::Runtime::ArithmeticException();
				}

				frame->operandStack->push2(a % b);
			}
			break;

			case FREM:
			{
				float b = frame->operandStack->pop();
				float a = frame->operandStack->pop();
				frame->operandStack->push(fmodf(a, b));
			}
			break;

			case DREM:
			{
				double b = frame->operandStack->pop2();
				double a = frame->operandStack->pop2();
				frame->operandStack->push2(fmod(a, b));
			}
			break;

			case INEG:
			{
				int a = frame->operandStack->pop();
				frame->operandStack->push(-a);
			}
			break;

			case LNEG:
			{
				long long a = frame->operandStack->pop2();
				frame->operandStack->push2(-a);
			}
			break;

			case FNEG:
			{
				float a = frame->operandStack->pop();
				frame->operandStack->push(-a);
			}
			break;

			case DNEG:
			{
				double a = frame->operandStack->pop2();
				frame->operandStack->push2(-a);
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
				int b = frame->operandStack->pop();
				long long a = frame->operandStack->pop2();
				frame->operandStack->push2(a << b);
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
				int b = frame->operandStack->pop();
				long long a = frame->operandStack->pop2();
				frame->operandStack->push2(a >> b);
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
				unsigned long long a = (unsigned long long)(long long)frame->operandStack->pop2();
				unsigned int b = frame->operandStack->pop();
				frame->operandStack->push2((long long)(a >> b));
				break;
			}

			case IAND:
			{
				SINGLE_WORD_OPERATION(int, &);
			}
			break;

			case LAND:
			{
				DOUBLE_WORD_OPERATION(long long, &);
			}
			break;

			case IOR:
			{
				SINGLE_WORD_OPERATION(int, | );
			}
			break;

			case LOR:
			{
				DOUBLE_WORD_OPERATION(long long, | );
			}
			break;

			case IXOR:
			{
				SINGLE_WORD_OPERATION(int, ^);
			}
			break;

			case LXOR:
			{
				DOUBLE_WORD_OPERATION(long long, ^);
			}
			break;

			case IINC:
			{
				unsigned char index = instructions[pc++];
				int value = (char)instructions[pc++];
				this->iinc(index, value);
			}
			break;

			case I2L:
			{
				long long val = (long long)(int) frame->operandStack->pop();
				frame->operandStack->push2(val);
			}
			break;

			case I2F:
			{
				float val = (float)(int) frame->operandStack->pop();
				frame->operandStack->push(val);
			}
			break;

			case I2D:
			{
				double val = (double)(int) frame->operandStack->pop();
				frame->operandStack->push2(val);
			}
			break;

			case L2I:
			{
				int val = (int)(long long)frame->operandStack->pop2();
				frame->operandStack->push(val);
			}
			break;

			case L2F:
			{
				float val = (float)(long long)frame->operandStack->pop2();
				frame->operandStack->push(val);
			}
			break;

			case L2D:
			{
				double val = (double)(long long)frame->operandStack->pop2();
				frame->operandStack->push2(val);
			}
			break;

			case F2I:
			{
				int val = (int)(float)frame->operandStack->pop();
				frame->operandStack->push(val);
			}
			break;

			case F2L:
			{
				long long val = (long long)(float)frame->operandStack->pop();
				frame->operandStack->push2(val);
			}
			break;

			case F2D:
			{
				double val = (double)(float) frame->operandStack->pop();
				frame->operandStack->push2(val);
			}
			break;

			case D2I:
			{
				int val = (int)(double)frame->operandStack->pop2();
				frame->operandStack->push(val);
			}
			break;

			case D2L:
			{
				long long val = (long long)((double)frame->operandStack->pop2());
				frame->operandStack->push2(val);
			}
			break;

			case D2F:
			{
				float val = (float)(double)frame->operandStack->pop2();
				frame->operandStack->push(val);
			}
			break;

			case I2B:
			{
				int val = (char)(int)frame->operandStack->pop();
				frame->operandStack->push(val);
			}
			break;

			case I2C:
			{
				int val = (java_char)(int)frame->operandStack->pop();
				frame->operandStack->push(val);
			}
			break;

			case I2S:
			{
				int val = (short)(int)frame->operandStack->pop();
				frame->operandStack->push(val);
			}
			break;


			case LCMP:
			{
				long long a = frame->operandStack->pop2();
				long long b = frame->operandStack->pop2();

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

				frame->operandStack->push(res);
			}
			break;

			case FCMPL:
			case FCMPG:
			{
				float a = frame->operandStack->pop();
				float b = frame->operandStack->pop();

				this->fdcmp<float>(a, b, currentInstruction);
			}
			break;



			case DCMPL:
			case DCMPG:
			{
				double a = frame->operandStack->pop2();
				double b = frame->operandStack->pop2();

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
				int value = frame->operandStack->pop();
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
				int b = frame->operandStack->pop();
				int a = frame->operandStack->pop();

				int res = a - b;
				this->jumpIfEq(currentInstruction - (IF_ICMPEQ - IFEQ), res);
			}
			break;


			// references eq - FALL-THROUGH
			case IF_ACMPEQ:
			case IF_ACMPNE:
			{
				short offset = this->getShort();
				unsigned short b = frame->operandStack->pop();
				unsigned short a = frame->operandStack->pop();

				if ((a == b && currentInstruction == IF_ACMPEQ) || (a != b && currentInstruction == IF_ACMPNE))
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
				unsigned short ref = frame->operandStack->pop();

				if ((ref == NULL && currentInstruction == IFNULL) || (ref != NULL && currentInstruction == IFNONNULL) )
				{
					this->jumpWithOffset(offset);
				}
			}
			break;

			case GOTO:
			{
				short offset = this->getShort() - 2; // 2 bytes for current offset
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
			{
				short offset = this->getShort();
				frame->operandStack->push(pc);
				this->jumpWithOffset(offset);
			}
			break;

			case JSR_W:
			{
				int offset = (int)this->getInt();
				frame->operandStack->push(pc);
				this->jumpWithOffset(offset);
			}
			break;


			case RET:
			{
				unsigned char index = instructions[pc];
				int restoredPc = frame->localVariables->operator[](index);
				pc = restoredPc;
			}
			break;

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

				int index = frame->operandStack->pop();

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

				int key = frame->operandStack->pop();
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
				word reference = frame->operandStack->pop();
				frame->parentFrame->operandStack->push(reference);
				this->dropCurrentFrame();
				return 0;
			}
			break;


			case LRETURN:
			case DRETURN:
			{
				doubleWord word = frame->operandStack->pop2();
				frame->parentFrame->operandStack->push2(word);
				this->dropCurrentFrame();
				return 0;
			};
			break;

			case RETURN:
			{
				this->dropCurrentFrame();
				return 0;
			};
			break;

			case GETSTATIC:
			{
				int index = this->getShort();
				
				Class* classPtr = this->resolveClass(index);
				Field* field = this->resolveField(index);
				
				switch (field->type)
				{
				case TypeTag::DOUBLE:
				case TypeTag::LONG:
					frame->operandStack->push2(classPtr->staticVariablesValues->get2(field->fieldIndex));
					break;
				default:
					frame->operandStack->push(classPtr->staticVariablesValues->get(field->fieldIndex));
					break;
				}
			};
			break;

			case PUTSTATIC:
			{
				int index = this->getShort();

				Class* classPtr = this->resolveClass(index);
				Field* field = this->resolveField(index);

				switch (field->type)
				{
				case TypeTag::DOUBLE:
				case TypeTag::LONG:
					classPtr->staticVariablesValues->set2(field->fieldIndex, frame->operandStack->pop2());
					break;
				default:
					classPtr->staticVariablesValues->set(field->fieldIndex, frame->operandStack->pop());
					break;
				}
			};
			break;

			case GETFIELD:
			{
				unsigned short index = this->getShort();
				Object* reference = (Object*)this->objectTable->get(frame->operandStack->popReference());

				if (reference == NULL)
				{
					throw Exceptions::Runtime::NullPointerException();
				}

				Class* classPtr = this->resolveClass(index);
				Field* field = this->resolveField(index);

				switch (field->type)
				{
				case TypeTag::DOUBLE:
				case TypeTag::LONG:
					frame->operandStack->push2(reference->fields->get2(field->fieldIndex));
					break;
				default:
					frame->operandStack->push(reference->fields->get(field->fieldIndex));
					break;
				}
			}
			break;

			case PUTFIELD:
			{
				unsigned short index = this->getShort();

				Class* classPtr = this->resolveClass(index);
				Field* field = this->resolveField(index);

				switch (field->type)
				{
				case TypeTag::DOUBLE:
				case TypeTag::LONG:
					{
						doubleWord data = frame->operandStack->pop2();
						Object* reference = (Object*)this->objectTable->get(frame->operandStack->popReference());

						if (reference == NULL)
						{
							throw Exceptions::Runtime::NullPointerException();
						}

						reference->fields->set2(field->fieldIndex, data);
					}
					break;
				default:
					{
						word data = frame->operandStack->pop();
						Object* reference = (Object*)this->objectTable->get(frame->operandStack->popReference());

						if (reference == NULL)
						{
							throw Exceptions::Runtime::NullPointerException();
						}

						reference->fields->set(field->fieldIndex, data);
					}
					break;
				}
			}
			break;

			// TODO: Invokes!
			case INVOKEVIRTUAL:
			case INVOKESPECIAL: // TODO: Should have its own handler			
			case INVOKESTATIC: // TODO: Add another handler for static methods
			{
				unsigned short index = this->getShort();
				Object* reference = NULL;

				Method* methodPtr = this->resolveMethod(index);
				Class* classPtr = methodPtr->classPtr;

				if (methodPtr->nativeMethod != nullptr)
				{
					methodPtr->nativeMethod(reference, this);
				}
				else
				{
					MethodFrame* newFrame = this->createMethodFrame(methodPtr, classPtr, currentInstruction == INVOKESTATIC);
					newFrame->parentFrame = frame;
					frame->childFrame = newFrame;
					this->execute(newFrame);
				}
			}
			break;
	
			case INVOKEINTERFACE:
			{
				size_t index = this->getShort();
				size_t count = instructions[pc++]; // information about parameters, could be determined from const pool
				pc++; // Reserved 0

				// TODO: Implement
			}
			break;

			case INVOKEDYNAMIC:
			{
				// NOT IMPLEMENTED
			}
			break;

			case NEW:
			{
				int index = this->getShort();
				// TODO: Class resolution and object allocation
				ConstantPoolItem * item = frame->constantPool->get(index);

				Class* classPtr = item->classInfo.classPtr;
				int classIndex = item->classInfo.name_index;
				ConstantPoolItem * name = frame->constantPool->get(item->classInfo.name_index);

				word idx = this->objectTable->insert(classPtr);
				frame->operandStack->pushReference(idx);
			};
			break;

			case NEWARRAY:
			{
				ArrayType type = (ArrayType)instructions[pc++];
				int size = frame->operandStack->pop();

				if (size < 0)
				{
					throw Exceptions::Runtime::NegativeArraySizeException();
				}

				unsigned char* ptr = nullptr;
				void * object = nullptr;
				Class* arrayClass = this->runtime->classTable->getClass("java/lang/Object");

				switch (type) 
				{
				case ArrayType::T_BOOLEAN:
					ptr = this->heap->allocate(ArrayObject<bool>::getMemorySize(size));
					object = new (ptr) ArrayObject<bool>(size, false, arrayClass, ptr);
					break;
				case ArrayType::T_BYTE:
					ptr = this->heap->allocate(ArrayObject<java_byte>::getMemorySize(size));
					object = new (ptr) ArrayObject<java_byte>(size, 0, arrayClass, ptr);
					break;
				case ArrayType::T_CHAR:
					ptr = this->heap->allocate(ArrayObject<java_char>::getMemorySize(size));
					object = new (ptr) ArrayObject<java_char>(size, '\u0000', arrayClass, ptr);
					break;
				case ArrayType::T_DOUBLE:
					ptr = this->heap->allocate(ArrayObject<java_double>::getMemorySize(size));
					object = new (ptr) ArrayObject<double>(size, +0.0, arrayClass, ptr);
					break;
				case ArrayType::T_FLOAT:
					ptr = this->heap->allocate(ArrayObject<java_float>::getMemorySize(size));
					object = new (ptr) ArrayObject<float>(size, +0.0, arrayClass, ptr);
					break;
				case ArrayType::T_INT:
					ptr = this->heap->allocate(ArrayObject<java_int>::getMemorySize(size));
					object = new (ptr) ArrayObject<int>(size, 0, arrayClass, ptr);
					break;
				case ArrayType::T_LONG:
					ptr = this->heap->allocate(ArrayObject<java_long>::getMemorySize(size));
					object = new (ptr) ArrayObject<long long>(size, 0, arrayClass, ptr);
					break;
				case ArrayType::T_SHORT:
					ptr = this->heap->allocate(ArrayObject<java_short>::getMemorySize(size));
					object = new (ptr) ArrayObject<short>(size, 0, arrayClass, ptr);
					break;
				}

				int objectIndex = this->objectTable->insert((Object*)object);

				frame->operandStack->pushReference(objectIndex);
			}
			break;


			case ANEWARRAY:
			{
				short index = this->getShort();
				int size = frame->operandStack->pop();

				if (size < 0)
				{
					throw Exceptions::Runtime::NegativeArraySizeException();
				}

				// TODO: Resolve class!


				unsigned char* ptr = nullptr;
				void * object = new (ptr) ArrayObject<Object*>(size, 0, NULL, ptr);

				int objectIndex = this->objectTable->insert((Object*)object);

				frame->operandStack->push(objectIndex);
			}
			break;

			case MULTIANEWARRAY:
			{
				// TODO: Check class
				int index = this->getShort();
				int dimensions = (int)instructions[pc++];

				if (dimensions < 1) 
				{
					// throw exception
				}

				int arrayDimensions[255];

				for (int i = 0; i < dimensions; i++)
				{
					arrayDimensions[i] = frame->operandStack->pop();
				}

				int object = (int)this->recursiveAllocateArray(dimensions, arrayDimensions);
			
				frame->operandStack->push(object);
			}
			break;

			case ARRAYLENGTH:
			{
				int index = frame->operandStack->popReference();
			
				if (index == 0) 
				{
					throw Exceptions::Runtime::NullPointerException();
				}

				ArrayObject<int>* object = (ArrayObject<int>*)this->objectTable->get(index);
			
				if (object == NULL)
				{
					throw Exceptions::Runtime::NullPointerException();
				}

				frame->operandStack->push(object->getSize());
			}
			break;

			case ATHROW:
			{
				// TODO: Exceptions!
				java::lang::Throwable::Throwable* ref = (java::lang::Throwable::Throwable*)this->objectTable->get(getReferenceAddress(frame->operandStack->top()));
				throw ref;
			}
			break;

			case CHECKCAST:
			{
				Object* ref = frame->operandStack->top();
				size_t index = this->getShort();

				if (ref != NULL)
				{
					Class* classPtr = this->resolveClass(index);
					if (! this->isInstanceOf(ref->objectClass, classPtr))
					{
						throw Exceptions::Runtime::RuntimeException();
					}
				}
			};
			break;

			case INSTANCEOF:
			{
				Object* ref = frame->operandStack->pop();
				size_t index = this->getShort();

				if (ref != NULL)
				{
					Class* classPtr = this->resolveClass(index);

					bool result = this->isInstanceOf(ref->objectClass, classPtr);				
					frame->operandStack->push((int)result);
				}
				else
				{
					frame->operandStack->push(0);
				}

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
					this->dload(index);
					break;
				case LLOAD:
					this->lload(index);
					break;
				case ISTORE:
				case FSTORE:
				case ASTORE:
					this->singleWordStore(index);
					break;
				case DSTORE:
					this->dstore(index);
					break;
				case LSTORE:
					this->lstore(index);
					break;
				case RET: 
					{
						int restoredPc = frame->localVariables->operator[](index);
						pc = restoredPc;
					}
					break;
				case IINC:
					{
						word value = this->getShort();
						this->iinc(index, value);
					}
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
		
#ifdef _DEBUG
			if (this->runtime->parameters.PrintExecutedInstructions) {
				std::cerr << "\tSTACK AFTER: " << frame->operandStack->index << std::endl;
			}
#endif

		}
		catch (java::lang::Throwable::Throwable* e) // user defined exceptions
		{
			if (!this->handleException(e))
			{
				size_t exceptionIndex = this->getCurrentMethodFrame()->operandStack->top();
				MethodFrame* parentFrame = this->getCurrentMethodFrame()->parentFrame;

				if (parentFrame != NULL)
				{
					parentFrame->operandStack->push(exceptionIndex);
					this->dropCurrentFrame();
				}

				throw; // rethrow exception to parent frame
			}

		}
		catch (Exceptions::Exception e) // runtime exceptions
		{
			Class* classPtr = this->classMap->getClass(e.what());

			byte* memory = this->heap->allocate(java::lang::Throwable::Throwable::getMemorySize());
			java::lang::Throwable::Throwable* throwable = new(memory) java::lang::Throwable::Throwable(classPtr);

			if (!this->handleException(throwable))
			{
				size_t exceptionIndex = this->getCurrentMethodFrame()->operandStack->top();
				MethodFrame* parentFrame = this->getCurrentMethodFrame()->parentFrame;

				if (parentFrame != NULL)
				{
					parentFrame->operandStack->push(exceptionIndex);
					this->dropCurrentFrame();
				}

				throw throwable; // rethrow exception to parent frame as java type exception
			}
		}
	}

	this->dropCurrentFrame();
	return 0;
}
