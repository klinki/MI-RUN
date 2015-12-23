#pragma once

#include <fstream>
#include <iostream>
#include <cstdlib>
#include "../runtime/ConstantPool.h"
#include "../runtime/Class.h"
#include "../runtime/ClassMap.h"
#include "../utils/Utf8String.h"


class ClassLoader
{
private:


	ConstantPool * constantPool;
	ClassMap * classMap;
	unsigned char * data;

	std::ifstream myfile;
	Class * thisClass;

public:
	ClassLoader(ClassMap * cm);
	ClassLoader();
	//bool load(char * filename);
	Class* load(char * filename);
	int loadMinVersion();
	int loadMajVersion();
	int loadConstPool();
	unsigned short loadFlags();
	int loadThisClass();
	int loadSuperClass();
	int loadInterfaces();
	int loadFields();
	int loadMethods();
	int loadAttributes();
	int reader(int nob); // reads data from file to array data
	void resolvePool();
	void resolveClassPointer(int i);
	~ClassLoader();
};
