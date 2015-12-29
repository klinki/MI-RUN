#include <string>
#include "ArgumentsParser.h"
#include "../runtime/Runtime.h"

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
	ArrayObject<Object*> * arrayObject = new(memory) ArrayObject<Object*>(countArguments, nullptr, NULL, NULL);

	size_t arrayIndex = this->runtime->objectTable->insert(arrayObject);

	for (int i = 0; i < countArguments; i++)
	{
		byte* strMemory = this->runtime->heap->allocate(Utf8String::getMemorySize(strlen(this->argv[i])));
		Utf8String* str = new(strMemory) Utf8String(argv[this->argsIndex + i], true);

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
