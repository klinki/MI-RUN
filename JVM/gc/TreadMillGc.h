#pragma once
#include "MemoryCell.h"

class TreadMillGc
{
	const int PAGE_SIZE = 4096;
	const int SMALLEST_SEGMENT_SIZE = 64;
	const int LARGEST_SEGMENT_SIZE = 128 * 1024; // 128kB
	const static int NUMBER_OF_GROUPS = 12;

protected:
	unsigned long long totalAllocatedMemory;
	unsigned char* memory;
	MemoryCell * freeList[NUMBER_OF_GROUPS];
	MemoryCell * usedList[NUMBER_OF_GROUPS];

public:
	TreadMillGc() : TreadMillGc(PAGE_SIZE * NUMBER_OF_GROUPS * 2) {}
	TreadMillGc(unsigned long long memorySize);
	~TreadMillGc();
};
