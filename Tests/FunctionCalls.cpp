#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/ConstantPool.h"
#include "../JVM/runtime/Runtime.h"
#include "../JVM/gc/Baker/BakerGc.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(FunctionCalls)
	{
	protected:
		ExecutionEngine * engine;
		BakerGc * gc;

	public:
		TEST_METHOD_INITIALIZE(initTest)
		{
			gc = new BakerGc(1 * 1024, 10 * 1024);

			engine = new ExecutionEngine();
			engine->classMap = new ClassMap();
			engine->objectTable = gc;
			engine->heap = gc;

			gc->engine = engine;
		}

		Method* getMethod(char* name, char* descriptor, Class* classPtr, int & pos)
		{
			Method* method = new Method();
			method->nativeMethod = nullptr;
			method->name = name;
			method->descriptor = descriptor;
			method->localVariablesArraySize = 3;
			method->operandStackSize = 4;

			ConstantPoolItem * item = new ConstantPoolItem(ConstantPoolTag::CONSTANT_Methodref);
			item->methodInfo.classPtr = classPtr;
			item->methodInfo.methodPtr = method;
			item->methodInfo.name_and_type_index = pos + 1;
			item->methodInfo.class_index = 1;

			classPtr->constantPool->add(pos++, item);

			ConstantPoolItem * nameAndType = new ConstantPoolItem(ConstantPoolTag::CONSTANT_NameAndType);
			nameAndType->nameAndTypeInfo.name_index = pos + 1;
			nameAndType->nameAndTypeInfo.descriptor_index = pos + 2;

			classPtr->constantPool->add(pos++, nameAndType);

			ConstantPoolItem * nameItem = new ConstantPoolItem(ConstantPoolTag::CONSTANT_Utf8);
			nameAndType->utf8Info.string = new Utf8String(name);

			classPtr->constantPool->add(pos++, nameItem);

			ConstantPoolItem * descriptorItem = new ConstantPoolItem(ConstantPoolTag::CONSTANT_Utf8);
			nameAndType->utf8Info.string = new Utf8String(method->descriptor);

			classPtr->constantPool->add(pos++, descriptorItem);

			method->initInputArgs();

			return method;
		}

		Method* getReturnConstMethod(char* name, Class* classPtr, int & pos)
		{
			Method* method = this->getMethod(name, "()I", classPtr, pos);
			method->byteCode = new Instruction[2];
			method->byteCode[0] = (Instruction)InstructionSet::ICONST_3;
			method->byteCode[1] = InstructionSet::IRETURN;
			method->byteCodeLength = 2;

			return method;
		}

		Method* getReturnParamMethod(char* name, Class* classPtr, int & pos)
		{
			Method* method = this->getMethod(name, "(I)I", classPtr, pos);
			method->descriptor = "(I)I";
			method->byteCode = new Instruction[2];
			method->byteCode[0] = (Instruction)InstructionSet::ILOAD_0;
			method->byteCode[1] = InstructionSet::IRETURN;
			method->byteCodeLength = 2;

			return method;
		}

		Method* getReturnSumMethod(char* name, Class* classPtr, int & pos)
		{
			Method* method = this->getMethod(name, "(II)I", classPtr, pos);
			method->byteCode = new Instruction[2];
			method->byteCode[0] = InstructionSet::ILOAD_0;
			method->byteCode[1] = InstructionSet::ILOAD_1;
			method->byteCode[2] = InstructionSet::IADD;
			method->byteCode[3] = InstructionSet::IRETURN;
			method->byteCodeLength = 4;

			return method;
		}

		Class* getClass()
		{
			Class* newClass = new Class(0);
			newClass->fullyQualifiedName = "java.lang.Test";
			newClass->constantPool = new ConstantPool(32);

			int pos = 1;

			ConstantPoolItem * item = new ConstantPoolItem(ConstantPoolTag::CONSTANT_Class);
			item->classInfo.classPtr = newClass;
			item->classInfo.name_index = pos + 1;

			newClass->constantPool->add(pos++, item);

			ConstantPoolItem * className = new ConstantPoolItem(ConstantPoolTag::CONSTANT_Utf8);
			className->utf8Info.string = new Utf8String(newClass->fullyQualifiedName);
			
			newClass->constantPool->add(pos++, className);

			this->getReturnConstMethod("getConstNormal", newClass, pos);
			this->getReturnParamMethod("getArgNormal", newClass, pos);
			this->getReturnSumMethod("getSumNormal", newClass, pos);

			this->getReturnConstMethod("getConstNormal", newClass, pos);
			this->getReturnParamMethod("getArgNormal", newClass, pos);
			this->getReturnSumMethod("getSumNormal", newClass, pos);

			return newClass;
		}

		MethodFrame * invoke(int methodIndex, Instruction instruction = InstructionSet::INVOKEVIRTUAL)
		{
			Method * a = new Method();
			a->byteCode = new Instruction[3];
			a->byteCode[0] = instruction;
			a->byteCode[1] = 0;
			a->byteCode[2] = methodIndex;
			a->byteCodeLength = 3;

			MethodFrame * frm = new MethodFrame(4, 4);
			frm->pc = 0;
			frm->method = a;

			engine->classMap->addClass(this->getClass());

			return frm;
		}

		TEST_METHOD(constReturningFunction)
		{
			MethodFrame * frm = this->invoke(3);

			Class* classPtr = this->getClass();

			Object* obj = new (engine->heap->allocate(Object::getMemorySize(0))) Object(0, classPtr);
			int ref = engine->objectTable->insert(obj);

			frm->constantPool = classPtr->constantPool;
			
			frm->operandStack->push(ref);
			engine->execute(frm);
			
			int result = frm->operandStack->pop();

			int expected = 3;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(argReturningFunction)
		{
			int expected = 123;
			MethodFrame * frm = this->invoke(7);

			Class* classPtr = this->getClass();

			Object* obj = new (engine->heap->allocate(Object::getMemorySize(0))) Object(0, classPtr);
			int ref = engine->objectTable->insert(obj);

			frm->constantPool = classPtr->constantPool;

			frm->operandStack->push(ref);
			frm->operandStack->push(expected);
			engine->execute(frm);

			int result = frm->operandStack->pop();
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(argSumReturningFunction)
		{
			int a = 100;
			int b = 200;
			int expected = a + b;
			MethodFrame * frm = this->invoke(11);

			Class* classPtr = this->getClass();

			Object* obj = new (engine->heap->allocate(Object::getMemorySize(0))) Object(0, classPtr);
			int ref = engine->objectTable->insert(obj);

			frm->constantPool = classPtr->constantPool;

			frm->operandStack->push(ref);
			frm->operandStack->push(a);
			frm->operandStack->push(b);
			engine->execute(frm);

			int result = frm->operandStack->pop();
			Assert::AreEqual(expected, result);
		}
	};
}
