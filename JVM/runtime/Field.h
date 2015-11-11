#pragma once
#include <string>
#include "AccessFlags.h"
typedef const unsigned char TypePrefix;

class Field
{
	enum class TypePrefix
	{
		BYTE = 'B',
		CHAR = 'C',
		DOUBLE = 'D',
		FLOAT = 'F',
		INTEGER = 'I',
		LONG = 'J',
		REFERENCE = 'L',
		SHORT = 'S',
		BOOLEAN = 'Z',
		ARRAY = '['
	};

protected:
	FLAG flags;
	std::string name;
	std::string descriptor;

	// attributes - constant value 

public:
	Field(FLAG f) : flags(f) {};
	~Field();
};

