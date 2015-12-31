#include <iostream>
#include <string>
#include <iostream>
#include "runtime/Runtime.h"
#include "natives/java/lang/Throwable.h"
#include "exceptions/RuntimeExceptions.h"

using namespace std;

int main(int argc, const char * argv[])
{
    int statusCode = 0;
	Runtime * runtime = new Runtime();
	runtime->run(argc, argv);

	try
	{
//		runtime->run(argc, argv);
	}
	catch (java::lang::Throwable::Throwable* exc)
	{
		cerr << "Unhandled exception: " << exc->objectClass->fullyQualifiedName.toAsciiString() << endl;
		exc->printStackTrace();
                
		statusCode = -1;
	}
	catch (Exceptions::Throwable e)
	{
		const char* message = e.getMessage();
		if (message == NULL)
		{
			message = "";
		}

		cerr << "Unhandled exception: " <<  e.what() << ": " << message << endl;
		statusCode = -1;
	}

	/*
		Structure:
			1) Init class loader, init internal state
			2) Read .jar file and load classes
			3) find main method and load it to memory (stackframe)
			4) run while loop with instructions switch
	*/

    delete runtime;
	return statusCode;
}
