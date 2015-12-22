#pragma once
#include <iostream>
#include "../runtime/Class.h"
#include "../runtime/MethodFrame.h"
#include "../runtime/ArrayObject.h"

class PrintStream
{
	std::ostream * output;
public:
	PrintStream(std::ostream * stream);
	~PrintStream();

	void close();
	void flush();
	void println();
	void println(Utf8String);
	void write(java_byte);
	void write(ArrayObject<java_byte> * arr);
	void write(ArrayObject<java_byte> * arr, size_t offset, size_t length);
};
