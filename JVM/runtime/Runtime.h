#pragma once
#include "ConstantPool.h"
#include "ClassMap.h"
#include "ExecutionEngine.h"
#include "Class.h"
#include "../gc/Heap.h"
#include "../gc/Baker/BakerGc.h"
#include "../utils/Macros.h"
#include "../classfile/ClassLoader.h"
#include "../natives/natives.h"
#include "../utils/ArgumentsParser.h"
#include "../utils/Parameters.h"
#include "../classfile/ClassLoader.h"

class Runtime
{
visibility:
	HeapInterface * heap;
	ClassMap * classTable;
	ExecutionEngine * executionEngine;
	ClassLoader * classLoader;
	ObjectTable * objectTable;

	Parameters parameters;

	const char* filePath;
	int argsIndex = 0;

public:
	Runtime()
	{
		BakerGc * baker = new BakerGc();
		this->heap = baker;
		this->objectTable = baker;
		this->classTable = new ClassMap();
		this->classLoader = new ClassLoader(this);
		this->executionEngine = new ExecutionEngine(this);
	}

	void run(int argc, const char** argv)
	{
		ArgumentsParser parser(this, argc, argv);
		parser.setParameters();

		initializeNatives(this);
		
		Class* mainClass = this->classLoader->load(parser.getClassFile());
		Method* mainMethod = mainClass->getMethod("main", "([Ljava/lang/String;)V");
		mainMethod->classPtr = mainClass;

		MethodFrame* frame = this->prepareFrame(mainMethod, parser.getArgumentsArray());
		this->executionEngine->execute(frame);
	}

	MethodFrame * prepareFrame(Method* mainMethod, word argsIndex)
	{
		unsigned char* memory = this->heap->allocate(MethodFrame::getMemorySize(mainMethod->operandStackSize, mainMethod->localVariablesArraySize));
		MethodFrame * frame = new (memory) MethodFrame(
			mainMethod->operandStackSize,
			mainMethod->localVariablesArraySize,
			NULL,
			mainMethod->classPtr->constantPool,
			mainMethod,
			NULL
			);

		frame->localVariables->set(0, argsIndex);
		return frame;
	}

	~Runtime()
	{
		delete this->heap;
		delete this->classTable;
		delete this->classLoader;
		delete this->executionEngine;
	}
};
