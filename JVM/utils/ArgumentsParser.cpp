#include <string>
#include "ArgumentsParser.h"
#include "../runtime/Runtime.h"
#include "../natives/java/lang/String.h"
#include "../natives/java/lang/Array.h"

ArgumentsParser::ArgumentsParser(Runtime* runtime, int argc, const char** argv)
{
	this->argc = argc;
	this->argv = argv;
	this->runtime = runtime;
	this->argsIndex = this->argc - 1;
}

const char* ArgumentsParser::getClassFile()
{
	for (int i = 0; i < argc; i++)
	{
		if (strstr(argv[i], ".class") != NULL)
		{
			classFile = argv[i];
			argsIndex = i + 1;
			return classFile;
		}
	}

	throw "Missing class file!";
}

word ArgumentsParser::getArgumentsArray()
{
	int countArguments = this->argc - this->argsIndex;

	byte* memory = this->runtime->heap->allocate(ArrayObject<Object*>::getMemorySize(countArguments));
	ArrayObject<Object*> * arrayObject = new(memory) ArrayObject<Object*>(countArguments, nullptr, java::lang::Array::initialize(NULL), NULL);

	size_t arrayIndex = this->runtime->objectTable->insert(arrayObject);

	for (int i = 0; i < countArguments; i++)
	{
		byte* strMemory = this->runtime->heap->allocate(java::lang::String::String::getMemorySize(strlen(this->argv[i])));
		java::lang::String::String* str = new(strMemory) java::lang::String::String(argv[this->argsIndex + i], true);

		size_t strIndex = this->runtime->objectTable->insert(str);
		(*arrayObject)[i] = makeReferenceAddress(strIndex);
	}

	return makeReferenceAddress(arrayIndex);
}

void ArgumentsParser::setParameters()
{
	this->runtime->parameters.PrintExecutedInstructions;

	for (int i = 0; i < argsIndex; i++)
	{
		if (strstr(argv[i], "--verbose")) {
			this->runtime->parameters.PrintExecutedInstructions = true;
		}
	}
}
