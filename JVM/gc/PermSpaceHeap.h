#pragma once
#include <stdlib.h>
#include "Heap.h"
#include "Baker/BakerGc.h"
#include "MemoryCell.h"

class Marker;
class Sweeper;

class PermSpaceHeap : public Heap
{
	struct FreeListHeader : MemoryHeader
	{
		FreeListHeader * left = nullptr;
		FreeListHeader * right = nullptr;
		
		FreeListHeader(): FreeListHeader(0)
		{
		};

		FreeListHeader(size_t size): MemoryHeader(size - sizeof(FreeListHeader) - sizeof(MemoryHeader))
		{
			this->size = size;
			this->left = this;
			this->right = this;
			this->accessCounter = Color::FREE_REGION;
		}

		void updateLeft(void* address)
		{
			if (this->left != nullptr)
			{
				this->left->right = (FreeListHeader*)address;
			}
		}

		void updateRight(void* address)
		{
			if (this->right != nullptr)
			{
				this->right->left = (FreeListHeader*)address;
			}
		}

		void insertAfter(void* address)
		{
			FreeListHeader* header = (FreeListHeader*)address;
			header->left = this;
			header->right = this->right;

			this->updateRight(address);
			this->right = header;
		}

		void insertBefore(void* address)
		{
			FreeListHeader* header = (FreeListHeader*)address;
			header->left = this->left;
			header->right = this;

			this->updateLeft(address);
			this->left = header;
		}
	};

protected:
	FreeListHeader * freeList;
	FreeListHeader * lastInserted;

public:
	PermSpaceHeap();
	PermSpaceHeap(size_t size);
	virtual ~PermSpaceHeap() {}

	size_t countAllocatedBlockSize(size_t size)
	{
		int totalAllocated = size + sizeof(MemoryHeader);
		int slots = totalAllocated / BakerGc::MEMORY_ALIGNMENT + 1;
		size_t bytesAllocated = slots * BakerGc::MEMORY_ALIGNMENT;
		return bytesAllocated;
	}

	virtual unsigned char* allocate(size_t size);

	void addToFreeList(MemoryHeader * header);
	void addToFreeList(FreeListHeader * header);

	friend class BakerGc;
	friend class Marker;
	friend class Sweeper;
};
