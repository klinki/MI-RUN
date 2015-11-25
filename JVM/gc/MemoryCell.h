#pragma once

struct MemoryCellStruct
{
	MemoryCellStruct * left;
	MemoryCellStruct * right;
	size_t size;
	unsigned char data[0];
};
