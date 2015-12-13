#pragma once

struct MemoryCell
{
	MemoryCell * left;
	MemoryCell * right;
	size_t size;
	unsigned char data[1];
};
