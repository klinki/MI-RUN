#include "Sweeper.h"
#include "../PermSpaceHeap.h"

Sweeper::Sweeper(BakerGc* baker)
{
	this->objectTable = baker;
	this->baker = baker;
}

Sweeper::~Sweeper()
{
}

void Sweeper::sweep(void* address)
{
	char* ptr = (char*)address;
	char* endPtr = NULL;

	while (ptr != endPtr)
	{
		ptr += sizeof(MemoryHeader);
		MemoryHeader * header = MemoryHeader::getHeader(ptr);
		size_t size = header->size;
		GarbageCollectableInterface* objPtr = (GarbageCollectableInterface*)ptr;

		if (header->getColor() != Color::BLACK)
		{
			// finalize object
			if (objPtr->requiresFinalization())
			{
				this->baker->finalize(objPtr);
			}

			DEBUG_PRINT("Removing key: %d from table\n", header->key);

			this->objectTable->remove(header->key);

			PermSpaceHeap::FreeListHeader * freeListHeader = new(header) PermSpaceHeap::FreeListHeader(size + sizeof(MemoryHeader));


		}
		else
		{
			header->setColor(Color::WHITE);
		}

		ptr += size;
		ptr += BakerGc::MEMORY_ALIGNMENT - (size % BakerGc::MEMORY_ALIGNMENT);
	}


	this->heap->lastInserted = nullptr;
}

void Sweeper::addToFreeList(void* address)
{

}
