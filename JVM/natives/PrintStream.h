#pragma once
#include <iostream>
#include "../runtime/Class.h"
#include "../runtime/MethodFrame.h"

class PrintStream
{
	std::ostream output;
public:
	PrintStream(std::ostream & stream);
	~PrintStream();

	void close(::Object *, MethodFrame *);
	void flush(::Object *, MethodFrame *);
	void write(::Object *, MethodFrame *);
	void writeWithOffset(::Object *, MethodFrame *);
	void writeSingleByte(::Object *, MethodFrame *);
	void println(::Object *, MethodFrame *);
};
