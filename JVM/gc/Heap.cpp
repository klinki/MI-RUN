#include "Heap.h"
#include "../exceptions/RuntimeExceptions.h"
#include <sstream>

Heap::Heap(): Heap(Heap::DEFAULT_HEAP_SIZE)
{

}

Heap::Heap(size_t size)
{
	this->allocatedBytes = size;
	this->data = (unsigned char*)malloc(this->allocatedBytes);
	this->usedBytes = 0;
	this->freeMemory = this->data;
}

Heap::~Heap()
{
	free(this->data);
}

void Heap::resize()
{
	this->allocatedBytes *= 2;
	this->data = (unsigned char*)realloc(this->data, this->allocatedBytes);
}

unsigned char* Heap::allocate(size_t bytes)
{
	if ((bytes + this->usedBytes) > this->allocatedBytes)
	{
		std::ostringstream message;
		message << "Tried to allocate: ";
		message << bytes;
		message << " bytes, but only ";
		message << (this->allocatedBytes - this->usedBytes);
		message << " free";
		throw Errors::OutOfMemoryError(message.str().c_str());
	}

	unsigned char* data = this->freeMemory;
	this->freeMemory += bytes;
	this->usedBytes += bytes;

	return data;
}

void Heap::clear()
{
	this->usedBytes = 0;
	this->freeMemory = this->data;
}
