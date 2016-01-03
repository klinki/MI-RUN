#include <iostream>
#include <string>
#include <iostream>
#include "runtime/Runtime.h"
#include "natives/java/lang/Throwable.h"
#include "exceptions/RuntimeExceptions.h"
#include "natives/java//lang/String.h"

using namespace std;

int main(int argc, const char * argv[])
{
    int statusCode = 0;
	Runtime * runtime = new Runtime(argc, argv);
	
	try
	{
		runtime->run();
	}
	catch (java::lang::Throwable::Throwable* exc)
	{
		size_t messageIndex = exc->fields->get(0);

		cerr << "Unhandled exception: " << exc->objectClass->fullyQualifiedName.toAsciiString();
		
		if (messageIndex != 0) {
			java::lang::String::String * str = (java::lang::String::String *)runtime->objectTable->get(messageIndex);
			cerr << " message: " << str->toAsciiString();
		}

		cerr << endl;
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
