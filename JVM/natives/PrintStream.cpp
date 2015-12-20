#include "PrintStream.h"


void close(::Object *, MethodFrame *);
void flush(::Object *, MethodFrame *);
void write(::Object *, MethodFrame *);
void writeWithOffset(::Object *, MethodFrame *);
void writeSingleByte(::Object *, MethodFrame *);
void println(::Object *, MethodFrame *);

PrintStream::PrintStream(std::ostream * stream)
{
	this->output = stream;
}

PrintStream::~PrintStream()
{
}

void PrintStream::close()
{
	delete this->output;
}

void PrintStream::flush()
{
	this->output->flush();
}

void PrintStream::println()
{
	*this->output << std::endl;
}

void PrintStream::println(Utf8String)
{
}

void PrintStream::write(java_byte byte)
{
	*this->output << byte;
}

void PrintStream::write(ArrayObject<java_byte>* arr)
{
	this->write(arr, 0, arr->getSize());
}

void PrintStream::write(ArrayObject<java_byte>* arr, size_t offset, size_t length)
{
	for (int i = offset; i < length; i++)
	{
		*this->output << (*arr)[i];
	}
}
