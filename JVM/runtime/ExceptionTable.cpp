#include "ExceptionTable.h"

ExceptionTable::ExceptionTable(size_t size): Array<Exception>(size)
{
	
}

void ExceptionTable::addException(const Exception & exc)
{
	this->allocatedArray[this->index++] = exc;
}

ExceptionTable::~ExceptionTable()
{
}
