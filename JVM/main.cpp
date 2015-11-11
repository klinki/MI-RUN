#include <iostream>
#include "classfile\ClassLoader.h"

int main(int argc, const char argv[])
{
	ClassLoader classLoader;
	classLoader.load("Arithmetics.class");

	/*
		Structure:
			1) Init class loader, init internal state
			2) Read .jar file and load classes
			3) find main method and load it to memory (stackframe)
			4) run while loop with instructions switch
	*/

	return 0;
}
