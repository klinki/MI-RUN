#pragma once
#include <cstring>
#include "../ObjectTable.h"
#include "../MS/Color.h"
#include "../interfaces/ObjectVisitorInterface.h"
#include "../interfaces/HeapInterface.h"
#include "../Heap.h"

class ExecutionEngine;
class Runtime;

class BakerGc : public ObjectTable, public ObjectVisitorInterface, public HeapInterface
{
	const int MEMORY_ALIGNMENT = 16;
	const int TENURATION_THRESHOLD = 50;
	static const int TENURATION_MASK = 0xfffff;
	static const int EDEN_SPACE_LIMIT = 1 * 1024;
visibility:
	enum MemoryLocation
	{
		YOUNG_SPACE,
		EDEN_SPACE,
		PERMANENT_SPACE
	};

	struct MemoryHeader
	{
		size_t size;
		size_t accessCounter; // or color for perm. generation
		size_t key;
		unsigned char * data; 

		MemoryHeader(size_t size)
		{
			this->size = size;
			this->accessCounter = 0;
			this->key = 0;
			this->data = (unsigned char*)(&this->data + 1);

#ifdef _DEBUG
			memset(this->data, 0, size);
#endif
		}

		bool isTenured() const
		{
			return (this->accessCounter & TENURATION_MASK) == TENURATION_MASK;
		}

		void tenure()
		{
			this->accessCounter |= TENURATION_MASK;
		}
	};

	Heap* memorySlots[2];
	Heap* permanentSpace;

	size_t activeSlot;

	word edenSpaceRoot;
	word permanentSpaceRoot;

	Runtime * runtime;
	ExecutionEngine * engine;


	void updateAddress(size_t index, void* newAddress);

	static void incrementAccessCounter(void* memory, size_t value = 1)
	{
		MemoryHeader * header = getHeader((char*)memory);
		header->accessCounter += value;
	}

	static void setColor(void* memory, Color color)
	{
		MemoryHeader * header = getHeader((char*)memory);
		header->accessCounter = color; 
	}

	static void setKey(void* memory, size_t key)
	{
		MemoryHeader * header = getHeader((char*)memory);
		header->key = key; 
	}

	void finalize(Heap* slot);

	size_t countAllocatedBlockSize(size_t size);

public:
	BakerGc();
	BakerGc(size_t memorySize, size_t permSize);
	BakerGc(Runtime* runtime, size_t memorySize, size_t permSize);
	~BakerGc();

	virtual void visit(MethodFrame* methodFrame);
	virtual void visit(Object* object);
	virtual void visit(ObjectHeader* object);
	virtual void visit(size_t address);
	virtual void visit(word address);

	virtual unsigned char* allocate(size_t size);
	unsigned char* allocateOnEdenSpace(size_t size);
	virtual unsigned char* allocateOnSystemMemory(size_t size)
	{
		return this->allocateOnPermanentSpace(size);
	}

	unsigned char* allocateOnPermanentSpace(size_t size);

	void switchMemorySlot();

	void setGCRoot(word currentFrame);

	void collect();

	virtual size_t insert(void * ptr);
	virtual size_t insert(void * ptr, bool systemObject);

	static MemoryHeader * getHeader(char* memory)
	{
		memory -= sizeof(MemoryHeader);
		return (MemoryHeader*)memory;
	}

	static int getAccessCounter(void * memory)
	{
		MemoryHeader* memHeader = getHeader((char*)memory);
		return memHeader->accessCounter;
	}

	static Color getColor(void* memory)
	{
		return (Color)getAccessCounter(memory);
	}

	static size_t getDataSize(void * memory)
	{
		MemoryHeader* memHeader = getHeader((char*)memory);
		return memHeader->size;
	}

	static int getKey(void * memory)
	{
		MemoryHeader* memHeader = getHeader((char*)memory);
		return memHeader->key;
	}
};
