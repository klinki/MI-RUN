#pragma once
class HeapInterface
{
public:
	virtual ~HeapInterface() {}
	virtual unsigned char* allocate(size_t size) = 0;
};
