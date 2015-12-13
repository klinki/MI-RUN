#include "Heap.h"

Heap::Heap()
{
	this->allocatedBytes = DEFAULT_HEAP_SIZE;
	this->data = (unsigned char*)malloc(this->allocatedBytes);
	this->usedBytes = 0;
	this->freeMemory = this->data;
}


Heap::~Heap()
{
}


void Heap::resize()
{
	this->allocatedBytes *= 2;
	this->data = (unsigned char*)realloc(this->data, this->allocatedBytes);
}

unsigned char* Heap::allocate(size_t bytes)
{
	unsigned char* data = this->freeMemory;
	this->freeMemory = this->freeMemory + bytes;
	this->usedBytes += bytes;

	return data;
}
