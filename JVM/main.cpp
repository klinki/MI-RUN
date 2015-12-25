#include <iostream>
#include <string>
#include <iostream>
#include "gc/experiments.h"
#include "classfile/ClassLoader.h"
#include "natives/natives.h"

int main(int argc, const char argv[])
{
	ClassMap * classMap = new ClassMap();

	InitializeNatives(classMap);
	
	ClassLoader classLoader(classMap);
	classLoader.load("Arithmetics.class");

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
