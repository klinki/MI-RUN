#pragma once
#include "../utils/HashMap.h"
#include "../utils/Macros.h"
#include "../utils/Utf8String.h"
#include "../utils/Array.h"

class Class;

struct Exception
{
	int start_pc;
	int end_pc;
	int handler_pc;
	int catch_type;
	Class* classPtr;

	Exception() {};

	Exception(int s, int e, int h, int c, Class* classPtr)
	{
		start_pc = s;
		end_pc = e;
		handler_pc = h;
		catch_type = c;
		this->classPtr = classPtr;
	}
};

class ExceptionTable : public Array<Exception>
{
public:
	ExceptionTable(size_t size);

	void addException(const Exception & exc);
	
	size_t getSize() const
	{
		return this->allocatedSize;
	}

	~ExceptionTable();
};
