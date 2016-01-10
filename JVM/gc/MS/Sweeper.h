#pragma once
#include "../interfaces/ObjectVisitorInterface.h"
#include "../PermSpaceHeap.h"

class Sweeper
{
	PermSpaceHeap * heap;
	BakerGc * baker;
	ObjectTable * objectTable;

public:
	Sweeper(BakerGc* baker);
	~Sweeper();

	virtual void sweep(void* address);
};
