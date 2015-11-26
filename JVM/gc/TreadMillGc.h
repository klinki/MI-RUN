#pragma once
class TreadMillGc
{
	struct MemoryCell
	{
		MemoryCell * left;
		MemoryCell * right;
		size_t size;
		unsigned char data[1];
	};

	const int PAGE_SIZE = 4096;
	const int SMALLEST_SEGMENT_SIZE = 64;
	const int LARGEST_SEGMENT_SIZE = 131072;
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
