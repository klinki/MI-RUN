#pragma once
#include <string>
#include "AccessFlags.h"
typedef const unsigned char TypePrefix;

class Field
{


protected:
	FLAG flags;
	std::string name;
	std::string descriptor;

	// attributes - constant value 

public:
	Field(FLAG f) : flags(f) {};
	~Field();
};

