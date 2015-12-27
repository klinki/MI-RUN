#include <iostream>
#include <string>
#include <iostream>
#include "gc/experiments.h"
#include "classfile/ClassLoader.h"
#include "natives/natives.h"
#include "runtime/Runtime.h"

using namespace std;

int main(int argc, const char argv[])
{
	ClassMap * classMap = new ClassMap();

	InitializeNatives(classMap);

	ClassLoader classLoader(classMap);
	Class* aClass = classLoader.load("Arithmetics.class");

	Runtime * runtime = new Runtime();
	runtime->heap = new Heap(100 * 1024);
	runtime->classTable = classMap;
	runtime->executionEngine = new ExecutionEngine();
	runtime->executionEngine->classMap = classMap;
	runtime->executionEngine->heap = runtime->heap;
	runtime->executionEngine->objectTable = new ObjectTable();

	Method* method = aClass->methodArea.getMethod("main", "()V");

	unsigned char* memory = runtime->heap->allocate(MethodFrame::getMemorySize(method->operandStackSize + 2, method->localVariablesArraySize));
	MethodFrame * frame = new (memory) MethodFrame(
		method->operandStackSize + 2,
		method->localVariablesArraySize,
		NULL,
		aClass->constantPool,
		method,
		NULL
		);

	try
	{
		runtime->executionEngine->execute(frame);
	}
	catch (Exception e)
	{
		cerr << "Unhandled exception: " << endl;
		return -1;
	}

	/*
		Structure:
			1) Init class loader, init internal state
			2) Read .jar file and load classes
			3) find main method and load it to memory (stackframe)
			4) run while loop with instructions switch
	*/

	experiments();

	return 0;
}
