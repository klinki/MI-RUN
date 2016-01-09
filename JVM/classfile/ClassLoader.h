#pragma once
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <algorithm>
#include "../runtime/ConstantPool.h"
#include "../runtime/Class.h"
#include "../runtime/ClassMap.h"
#include "../utils/Utf8String.h"

class Runtime;

class ClassLoader
{
protected:
	struct NamespaceStructure
	{
		size_t levels;
		std::string * namespaces;
		std::string filePath;
		std::string directory;

		NamespaceStructure(std::string className)
		{
			this->levels = 0;

			int lastDelimiter = className.find_last_of('/');
			std::string directory = className.substr(0, lastDelimiter);
			this->filePath = className.substr(lastDelimiter + 1);

			int size = std::count(className.begin(), className.end(), '/');;

			this->namespaces = new std::string[size];
			char* classNameSTr = (char*)className.c_str();

			char* token = NULL;

			for (int i = 0; i < size; i++) {
#ifdef _MSC_VER
				token = strtok_s(classNameSTr, "/", &classNameSTr);
#else
				token = strtok(classNameSTr, "/");
#endif
				this->namespaces[i] = std::string(token);
			}
		}
	};

	NamespaceStructure * rootNamespace;

private:
	ConstantPool * constantPool;
	ClassMap * classMap;
	char * data;
	
	Runtime* runtime;

	std::ifstream * myfile;
	
	char* defaultNamespace = NULL;

	std::string currentDir;
	std::string currentNamespace;

public:
	ClassLoader(Runtime * runtime);
    ~ClassLoader();
   
	void init(const char * activeFile);
	std::string getNamespaceFromClass(const char * className);

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
	void resolvePool(Class * thisClass,int nameptr);
	void resolveClassPointer(Class * thisClass,int i, int nameptr);
};
