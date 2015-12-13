#pragma once
#include <stdlib.h>
class Heap
{
	const int DEFAULT_HEAP_SIZE = 64 * 1024; // 64kB

protected:
	unsigned int allocatedBytes;
	unsigned int usedBytes;
	unsigned char * data;
	unsigned char * freeMemory;

	void resize();
public:
	Heap();
	~Heap();

	unsigned char* allocate(size_t size);
};
