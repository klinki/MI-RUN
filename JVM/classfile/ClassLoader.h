#include <fstream>
#include <iostream>
#include <cstdlib>
#include "../runtime/ConstantPool.h"


#pragma once
class ClassLoader
{
private:
	int minor_version;
	int major_version;
	int constant_pool_count;
	ConstantPool CPool;
	unsigned char * data;
	int interfaces_count;
	int fields_count;
	int methods_count;
	int attributes_count;
	unsigned int access_flags;
	unsigned char * ThisClass;
	unsigned char * SuperClass;
	std::ifstream myfile;
public:
	ClassLoader();
	//bool load(char * filename);
	int load(char * filename);
	int loadMinVersion();
	int loadMajVersion();
	int loadCostPool();
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
