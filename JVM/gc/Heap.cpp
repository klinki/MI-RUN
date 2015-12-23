#include "Heap.h"



Heap::Heap(): Heap(DEFAULT_HEAP_SIZE)
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

void Heap::clear()
{
	this->usedBytes = 0;
	this->freeMemory = this->data;
}
