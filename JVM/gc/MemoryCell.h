#pragma once
#include <cstring>
#include "MS/Color.h"

struct MemoryCell
{
	MemoryCell * left;
	MemoryCell * right;
	size_t flags;
	size_t size;
	unsigned char data[1];
};


struct MemoryHeader
{
	static const int TENURATION_MASK = 0xfffff;
	static const int COLOR_MASK = 0x07;
	size_t size;
	size_t accessCounter; // or color for perm. generation
	size_t key;
	unsigned char * data;

	MemoryHeader(size_t size)
	{
		this->size = size;
		this->accessCounter = 0;
		this->key = -1;
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

	void setKey(size_t key)
	{
		this->key = key;
	}

	void setFlags(int flags)
	{
		this->accessCounter = flags;
	}

	void setColor(Color color)
	{
		this->accessCounter |= color;
	}

	Color getColor()
	{
		return (Color)(this->accessCounter & COLOR_MASK);
	}

	void incrementAccessCounter(size_t value = 1)
	{
		this->accessCounter += value;
	}


	static MemoryHeader * getHeader(void* memoryPtr)
	{
		char* memory = (char*)memoryPtr;
		memory -= sizeof(MemoryHeader);
		return (MemoryHeader*)memory;
	}
};
