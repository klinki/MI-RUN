#pragma once

struct MemoryCellStruct
{
	MemoryCellStruct * left;
	MemoryCellStruct * right;
	unsigned int size;
	unsigned char data[0];
};
