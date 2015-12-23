#pragma once
#include "../ObjectTable.h"
#include "../MS/Color.h"
#include "../ObjectVisitorInterface.h"
#include "../interfaces/HeapInterface.h"
#include "../Heap.h"

class BakerObjectTable : public ObjectTable, public ObjectVisitorInterface, public HeapInterface
{
	const int MEMORY_ALIGNMENT = 16;
	const int TENURATION_THRESHOLD = 50;
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
		unsigned char data[8]; // minimal size is 8 to keep 16B alignment
	};

	Heap* memorySlots[2];
	Heap* permanentSpace;

	size_t activeSlot;

	word edenSpaceRoot;
	word permanentSpaceRoot;

	void updateAddress(size_t index, void* newAddress);

	static void setDataSize(void * memory, size_t size)
	{
		int* intPtr = (int*)memory;
		intPtr--;
		*intPtr = 0; // int table
		intPtr--;
		*intPtr = 0; // accesses
		intPtr--;
		*intPtr = size;
	}

	static void incrementAccessCounter(void* memory, size_t value = 1)
	{
		int* intPtr = (int*)memory;
		intPtr -= 2;
		(*intPtr) += value; // accesses
	}

	static void setColor(void* memory, Color color)
	{
		int* intPtr = (int*)memory;
		intPtr -= 2;
		(*intPtr) = color; // color
	}

	static void setKey(void* memory, size_t key)
	{
		int* intPtr = (int*)memory;
		intPtr--;
		*intPtr = key;
	}

	void finalize();

public:
	BakerObjectTable();
	BakerObjectTable(size_t memorySize, size_t permSize);
	~BakerObjectTable();

	virtual void visit(MethodFrame* methodFrame);
	virtual void visit(Object* object);
	virtual void visit(size_t address);
	virtual void visit(word address);

	virtual unsigned char* allocate(size_t size);
	unsigned char* allocateOnPermanentSpace(size_t size);

	void switchMemorySlot();

	void setGCRoot(word currentFrame);

	void collect();

	virtual size_t insert(void * ptr);

	static int getAccessCounter(void * memory)
	{
		int* intPtr = (int*)memory;
		intPtr -= 2;
		return *intPtr;
	}

	static Color getColor(void* memory)
	{
		return (Color)getAccessCounter(memory);
	}

	static size_t getDataSize(void * memory)
	{
		int* intPtr = (int*)memory;
		intPtr -= 3;
		return *intPtr;
	}

	static int getKey(void * memory)
	{
		int* intPtr = (int*)memory;
		intPtr--;
		return *intPtr;
	}
};
