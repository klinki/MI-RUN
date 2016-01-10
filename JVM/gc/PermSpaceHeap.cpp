#include "PermSpaceHeap.h"
#include "../exceptions/RuntimeExceptions.h"

PermSpaceHeap::PermSpaceHeap(): PermSpaceHeap(0)
{}

PermSpaceHeap::PermSpaceHeap(size_t size): Heap(size)
{
	this->freeList = new(this->data) FreeListHeader(this->allocatedBytes);
	this->freeList->left = this->freeList;
	this->freeList->right = this->freeList;
}

unsigned char* PermSpaceHeap::allocate(size_t size)
{
	if (this->freeList == nullptr)
	{
		throw Errors::OutOfMemoryError("TENURED SPACE OUT OF MEMORY");
	}

	FreeListHeader * header = this->freeList;
	size_t requiredSize = size;

	FreeListHeader * selectedHeader = nullptr;

	do
	{
		// size here is including sizeof FreeListHeader
		if (header->size >= requiredSize)
		{
			selectedHeader = header;
			break;
		}
		else
		{
			header = header->right;
		}
	} while (header != nullptr || header != this->freeList);

		
	if (selectedHeader == nullptr)
	{
		throw Errors::OutOfMemoryError("TENURED SPACE OUT OF MEMORY");
	}

	bool updateFreeListPointer = false;
	if (selectedHeader == this->freeList)
	{
		updateFreeListPointer = true;
	}

	size_t previousFreeSize = selectedHeader->size;

	if ((previousFreeSize - requiredSize) < (sizeof(FreeListHeader) + sizeof(MemoryHeader)))
	{
		// TODO: remove from free list
		// selectedHeader->updateLeft(selectedHeader->right);
		// selectedHeader->updateRight(selectedHeader->left);

		this->freeList = NULL;
	}
	else
	{
		char* newFreeListAddress = (char*)selectedHeader + requiredSize;

		selectedHeader->updateLeft(newFreeListAddress);
		selectedHeader->updateRight(newFreeListAddress);


		FreeListHeader * newHeader = new(newFreeListAddress) FreeListHeader(previousFreeSize - requiredSize);

		if (updateFreeListPointer)
		{
			this->freeList = newHeader;
		}
	}

	this->usedBytes += requiredSize;

	return (unsigned char*)selectedHeader;
}

void PermSpaceHeap::addToFreeList(MemoryHeader* header)
{
	FreeListHeader * freeListHeader = nullptr;

	if (header->getColor() != Color::FREE_REGION)
	{
		size_t size = header->size;
		freeListHeader = new(header) PermSpaceHeap::FreeListHeader(header->size);

		int rem = size % BakerGc::MEMORY_ALIGNMENT;

		if (rem != 0)
		{
			freeListHeader->size += BakerGc::MEMORY_ALIGNMENT - rem;
		}

		freeListHeader->size += sizeof(MemoryHeader);


		this->usedBytes -= freeListHeader->size;
	}
	else
	{
		freeListHeader = (FreeListHeader*)header;
	}

	this->addToFreeList(freeListHeader);
}

void PermSpaceHeap::addToFreeList(FreeListHeader * header)
{
	if (this->freeList == nullptr)
	{
		this->freeList = header;
		this->lastInserted = header;
	}
	else
	{
		if (this->lastInserted == nullptr)
		{
			this->lastInserted = header;
			this->freeList->insertAfter(header);
		}
		else
		{
			size_t size = this->lastInserted->size;
			char* lastInsertedNext = (char*) this->lastInserted + size;

			size_t diff = (char*)header - lastInsertedNext;

			// inserted directly after last inserted, concat
			/*
				//////////////////////////////////////////////////////
				// FREE_LIST HEADER| MEMORY HEADER | DATA | PADDING //
				//////////////////////////////////////////////////////

				+ 

				//////////////////////////////////////////////////////
				// FREE_LIST HEADER| MEMORY HEADER | DATA | PADDING //
				//////////////////////////////////////////////////////

				=

				//////////////////////////////////////////////////////////////////////////////////////////////////////////
				// FREE_LIST HEADER| MEMORY HEADER | DATA + (free_list_header | memory header| data| padding) | PADDING //
				//////////////////////////////////////////////////////////////////////////////////////////////////////////
			*/
			

			if (diff <= BakerGc::MEMORY_ALIGNMENT)
			{
				this->lastInserted->size += diff + header->size; // free list header size is already included in header size
			}
			else
			{
				this->lastInserted->insertAfter(header);
			}
		}	
	}
}
