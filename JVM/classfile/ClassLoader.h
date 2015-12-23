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
	

public:
	ClassLoader(ClassMap * cm);
	ClassLoader();
	//bool load(char * filename);
	Class* load(char * filename);
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
