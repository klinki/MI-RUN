#pragma once
#include <cstring>
#include <set>
#include "../ObjectTable.h"
#include "../MS/Color.h"
#include "../interfaces/ObjectVisitorInterface.h"
#include "../interfaces/HeapInterface.h"
#include "../Heap.h"
#include "../MemoryCell.h"

class ExecutionEngine;
class Runtime;
class PermSpaceHeap;
class Marker;
class Sweeper;

class BakerGc : public ObjectTable, public ObjectVisitorInterface, public HeapInterface
{
visibility:
	static const int MEMORY_ALIGNMENT = 16;
	static const int TENURATION_THRESHOLD = 50;
	static const int TENURATION_MASK = 0xfffff;
	static const int EDEN_SPACE_LIMIT = 1 * 1024;

	enum MemoryLocation
	{
		YOUNG_SPACE,
		EDEN_SPACE,
		PERMANENT_SPACE
	};

	Heap* memorySlots[2];
	
	PermSpaceHeap* permanentSpace;
	Marker* marker;
	Sweeper* sweeper;

	size_t activeSlot;

	Runtime * runtime;
	ExecutionEngine * engine;

	std::set<size_t> visitedObjects;

	void updateAddress(size_t index, void* newAddress);
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

	void collect();
	void fullCollect();

	virtual size_t insert(void * ptr);
	virtual size_t insert(void * ptr, bool systemObject);

	static MemoryHeader * getHeader(void* memoryPtr)
	{
		return MemoryHeader::getHeader(memoryPtr);
	}

	void finalize(GarbageCollectableInterface * objPtr);

	friend class PermSpaceHeap;
};
