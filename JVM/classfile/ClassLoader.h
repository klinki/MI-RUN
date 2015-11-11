#include <fstream>
#include <iostream>
#include <cstdlib>


#pragma once
class ClassLoader
{
public:
	ClassLoader();
	bool load(char * filename);
	~ClassLoader();
};


