#pragma once

#include <fstream>
#include <iostream>
#include <cstdlib>
#include "../runtime/ConstantPool.h"
#include "../runtime/Class.h"
#include "../utils/Utf8String.h"


class ClassLoader
{
private:
	int minor_version;
	int major_version;
	int constant_pool_count;
	//ConstantPool * CPool;
	ConstantPool * constantPool;
	unsigned char * data;
	int interfaces_count;
	int fields_count;
	int methods_count;
	int attributes_count;
	unsigned short access_flags;
	unsigned char * thisClassName;
	unsigned char * superClassName;
	std::ifstream myfile;
	Class * thisClass;

public:
	ClassLoader();
	//bool load(char * filename);
	int load(char * filename);
	int loadMinVersion();
	int loadMajVersion();
	int loadConstPool();
	int loadFlags();
	int loadThisClass();
	int loadSuperClass();
	int loadInterfaces();
	int loadFields();
	int loadMethods();
	int loadAttributes();
	int reader(int nob); // reads data from file to array data
	~ClassLoader();
};
