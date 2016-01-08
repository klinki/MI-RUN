#pragma once
#include <stdlib.h>
#include "Heap.h"
#include "Baker\BakerGc.h"
#include "MemoryCell.h"

class Marker;
class Sweeper;

class PermSpaceHeap : public Heap
{
	struct FreeListHeader
	{
		FreeListHeader * left = nullptr;
		FreeListHeader * right = nullptr;
		MemoryHeader * header = nullptr;
		char* PADDING = nullptr; // pading for 16B memory alignment

		FreeListHeader() {};

		FreeListHeader(size_t size)
		{
			this->header = new(&this->header + 1) MemoryHeader(size + sizeof(FreeListHeader));
			this->left = this;
			this->right = this;
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
	virtual void clear();

	void addToFreeList(FreeListHeader * header);

	friend class BakerGc;
	friend class Marker;
	friend class Sweeper;
};
