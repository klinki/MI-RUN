#include "TreadMillGc.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

TreadMillGc::TreadMillGc(unsigned long long memorySize)
{
	if (memorySize % 64 != 0)
		throw "Must be multiple of 64";

	this->totalAllocatedMemory = memorySize;

	this->memory = (unsigned char*)operator new(memorySize);
	// allocate at least one page of each size

	unsigned char* lastAddress = this->memory + memorySize - 1;

	for (unsigned char* address = this->memory; address < lastAddress; )
	{
		MemoryCell* cell = (MemoryCell*)address;
		cell->size = 64 - sizeof(MemoryCell*) * 2 - sizeof(unsigned int);
		cell->left = (MemoryCell*)(address - 64);
		cell->right = (MemoryCell*)(address + 64);
		memcpy(cell->data, "This is sample string to add into data area. Longer", cell->size);
//		memset(cell->data, 0, cell->size);
		address += 64; // or 8?
		//A * aPtr = (A*) new(memory) A(10, "Hello World", (long long)(INT_MAX)+1, 1.25);
	}

	MemoryCell* first = (MemoryCell*)this->memory;
	first->left = (MemoryCell*)(lastAddress - 63);
}


TreadMillGc::~TreadMillGc()
{
	MemoryCell* lastAddress = (MemoryCell*)(this->memory + this->totalAllocatedMemory - 1);

	for (MemoryCell* address = (MemoryCell*)this->memory; address < lastAddress; )
	{
		MemoryCell* cell = (MemoryCell*)address;
		address += 64;

		std::cout << cell->left << " " << cell->right << " " << cell->size << " " << cell->data << std::endl;

		//A * aPtr = (A*) new(memory) A(10, "Hello World", (long long)(INT_MAX)+1, 1.25);
	}

	std::cout << "GOING RIGHT" << std::endl;


	for (MemoryCell* address = (MemoryCell*)this->memory; address < lastAddress; address = address->right )
	{
		MemoryCell* cell = (MemoryCell*)address;
		std::cout << cell->left << " " << cell->right << " " << cell->size << " " << cell->data << std::endl;

		//A * aPtr = (A*) new(memory) A(10, "Hello World", (long long)(INT_MAX)+1, 1.25);
	}

	std::cout << "GOING LEFT" << std::endl;

	for (MemoryCell* address = ((MemoryCell*)this->memory)->left; address >(MemoryCell*)this->memory; address = address->left)
	{
		MemoryCell* cell = (MemoryCell*)address;
		std::cout << cell->left << " " << cell->right << " " << cell->size << " " << cell->data << std::endl;

		//A * aPtr = (A*) new(memory) A(10, "Hello World", (long long)(INT_MAX)+1, 1.25);
	}
}
