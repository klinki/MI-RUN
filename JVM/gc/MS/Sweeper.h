#pragma once
#include "../interfaces/ObjectVisitorInterface.h"
#include "../PermSpaceHeap.h"

class Sweeper
{
	PermSpaceHeap * heap;
	BakerGc * baker;
	ObjectTable * objectTable;

	virtual void sweep(void* address);
	virtual void addToFreeList(void* address);
};
