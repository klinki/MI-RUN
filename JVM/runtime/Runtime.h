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

	ArgumentsParser * parser;

	const char* filePath;
	int argsIndex = 0;

public:
	Runtime(int argc, const char** argv)
	{
		this->parser = new ArgumentsParser (this, argc, argv);
		this->parser->setParameters();

		BakerGc * baker = new BakerGc(this, this->parameters.EdenSpaceSize, this->parameters.PermSpaceSize);
		this->heap = baker;
		this->objectTable = baker;
		this->classTable = new ClassMap();
		this->classLoader = new ClassLoader(this);
		this->executionEngine = new ExecutionEngine(this);
	}

	void run()
	{
		initializeNatives(this);
		
		this->classLoader->init(this->parser->getClassFile());
		Class* mainClass = this->classLoader->load(this->parser->getClassFile());
		Method* mainMethod = mainClass->getMethod("main", "([Ljava/lang/String;)V");

		if (mainMethod == NULL)
		{
			throw Errors::NoSuchMethodError("No main method");
		}

		mainMethod->classPtr = mainClass;

		MethodFrame* frame = this->prepareFrame(mainMethod, parser->getArgumentsArray());
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
		delete this->parser;
	}
};
