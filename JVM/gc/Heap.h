#pragma once
#include <stdlib.h>
#include "interfaces/HeapInterface.h"
class Heap : public HeapInterface
{
	const int DEFAULT_HEAP_SIZE = 64 * 1024; // 64kB

protected:
	size_t allocatedBytes;
	size_t usedBytes;
	unsigned char * data;
	unsigned char * freeMemory;

	void resize();
public:
	Heap();
	Heap(size_t size);
	~Heap();

	virtual unsigned char* allocate(size_t size);
	virtual void clear();

	friend class BakerObjectTable;
};
