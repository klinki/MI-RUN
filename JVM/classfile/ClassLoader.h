#pragma once

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "../runtime/ConstantPool.h"
#include "../runtime/Class.h"
#include "../runtime/ClassMap.h"
#include "../utils/Utf8String.h"

using std::runtime_error;

class Runtime;

class ClassLoader
{
private:
	ConstantPool * constantPool;
	ClassMap * classMap;
	char * data;
	
	Runtime* runtime;

	std::ifstream myfile;

public:
	ClassLoader(Runtime * runtime);

	//bool load(char * filename);
	Class* load(const char * filename);
	int loadMinVersion();
	int loadMajVersion();
	int loadConstPool();
	unsigned short loadFlags();
	int loadThisClass(Class * thisClass);
	int loadSuperClass(Class * thisClass);
	int loadInterfaces(Class * thisClass);
	int loadFields(Class * thisClass);
	int loadMethods(Class * thisClass);
	int loadAttributes(Class * thisClass);
	int reader(int nob); // reads data from file to array data
	void resolvePool(Class * thisClass);
	void resolveClassPointer(Class * thisClass,int i);
	~ClassLoader();
};


class FileNotFoundException : public runtime_error
{
public:
	FileNotFoundException() : runtime_error("failed to open file" ) {}
};
