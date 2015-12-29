#include <iostream>
#include <string>
#include <iostream>
#include "runtime/Runtime.h"
#include "natives/java/lang/Throwable.h"

using namespace std;

int main(int argc, const char * argv[])
{
	Runtime * runtime = new Runtime();

	try
	{

		runtime->run(argc, argv);
	}
	catch (java::lang::Throwable::Throwable* exc)
	{
		cerr << "Unhandled exception: " << exc->objectClass->fullyQualifiedName.toAsciiString() << endl;
		exc->printStackTrace();

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

	return 0;
}
