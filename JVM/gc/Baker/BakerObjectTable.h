#pragma once
#include "../ObjectTable.h"
class BakerObjectTable : public ObjectTable
{
protected:
	enum MemoryLocation
	{
		YOUNG_SPACE,
		EDEN_SPACE,
		PERMANENT_SPACE
	};
	enum Color
	{
		WHITE,
		GREY,
		BLACK
	};
	struct MemoryHeader
	{
		MemoryLocation location;
		size_t accessCounter;
		Color color;
	};

public:
	BakerObjectTable();
	~BakerObjectTable();
};
