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

class Runtime
{
visibility:
	HeapInterface * heap;
	ClassMap * classTable;
	ExecutionEngine * executionEngine;
	ClassLoader * classLoader;
	ObjectTable * objectTable;

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

	void run(const char* filePath)
	{
		initializeNatives(this);
		Class* mainClass = this->classLoader->load(filePath);
		Method* mainMethod = mainClass->getMethod("main", "([Ljava/lang/String;)V");
		mainMethod->classPtr = mainClass;
		this->executionEngine->execute(mainMethod);
	}

	~Runtime()
	{
		delete this->heap;
		delete this->classTable;
		delete this->classLoader;
		delete this->executionEngine;
	}
};
