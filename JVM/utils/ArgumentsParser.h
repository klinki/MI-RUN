#pragma once
#include "../types/types.h"

class Runtime;

class ArgumentsParser
{
protected:
	int argc;
	const char** argv;

	const char* classFile;
	int argsIndex;

	Runtime* runtime;

public:
	ArgumentsParser(Runtime* runtime, int argc, const char** argv);

	const char* getClassFile();
	word getArgumentsArray();
	void setParameters();
};
