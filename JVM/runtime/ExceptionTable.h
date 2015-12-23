#pragma once
#include "../utils/HashMap.h"
#include "../utils/Macros.h"
#include "../utils/Utf8String.h"


struct Exception
{
	int start_pc;
	int end_pc;
	int handler_pc;
	int catch_type;
	Exception(int s, int e, int h, int c)
	{
		start_pc = s;
		end_pc = e;
		handler_pc = h;
		catch_type = c;
	}
};

class ExceptionTable
{
visibility:
	HashMap<Utf8String,Exception*> hashmap;


public:
	ExceptionTable();

	void addException(Utf8String name, int s, int e, int h, int c);
	Exception* getException(const Utf8String & name);
	
	~ExceptionTable();
};

