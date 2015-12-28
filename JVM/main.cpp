#include <iostream>
#include <string>
#include <iostream>
#include "runtime/Runtime.h"

using namespace std;

int main(int argc, const char * argv[])
{
	Runtime * runtime = new Runtime();

	try
	{
		runtime->run(argv[1]);
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
