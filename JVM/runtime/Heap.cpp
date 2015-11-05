#include "Heap.h"

Heap::Heap()
{
	this->allocatedBytes = DEFAULT_HEAP_SIZE;
	this->data = (unsigned char*)malloc(this->allocatedBytes);
	this->usedBytes = 0;
}


Heap::~Heap()
{
}


void Heap::resize()
{
	this->allocatedBytes *= 2;
	realloc(this->data, this->allocatedBytes);
}
