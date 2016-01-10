#include "Sweeper.h"
#include "../PermSpaceHeap.h"

Sweeper::Sweeper(BakerGc* baker)
{
	this->objectTable = baker;
	this->baker = baker;
	this->heap = this->baker->permanentSpace;
}

Sweeper::~Sweeper()
{
}

void Sweeper::sweep(void* address)
{
	this->heap->freeList = nullptr;

	char* ptr = (char*)address;
	char* endPtr = (char*)address + this->heap->allocatedBytes;

	while (ptr < endPtr)
	{
		MemoryHeader * header = (MemoryHeader*) ptr;
		size_t size = header->size;
		ptr += sizeof(MemoryHeader);

		if (header->getColor() != Color::BLACK)
		{
			if (header->getColor() != Color::FREE_REGION) 
			{
				GarbageCollectableInterface* objPtr = (GarbageCollectableInterface*)ptr;
				// finalize object
				if (objPtr->requiresFinalization())
				{
					this->baker->finalize(objPtr);
				}

				DEBUG_PRINT("Removing key: %d from table\n", header->key);

				this->objectTable->remove(header->key);
			}

			this->heap->addToFreeList(header);
		}
		else
		{
			header->setColor(Color::WHITE);
		}

		ptr += size;

		int rem = size % BakerGc::MEMORY_ALIGNMENT;

		if (rem != 0)
		{
			ptr += BakerGc::MEMORY_ALIGNMENT - rem;
		}
	}


	this->heap->lastInserted = nullptr;
}

void Sweeper::addToFreeList(void* address)
{

}
