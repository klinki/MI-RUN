#include "Marker.h"
#include "../interfaces/GarbageCollectableInterface.h"
#include "../../types/ConversionFunctions.h"
#include "../../utils/Macros.h"
#include "../MemoryCell.h"

Marker::Marker() {};

Marker::Marker(ObjectTable * objectTable)
{
	this->objectTable = objectTable;
}

Marker::~Marker()
{
}

void Marker::visit(MethodFrame* methodFrame)
{
}

void Marker::visit(ObjectHeader* header)
{
}

void Marker::visit(Object* object)
{
}

void Marker::visit(word address)
{
	if (isReferenceAddress(address))
	{
		int refAddress = getReferenceAddress((unsigned int)address);

		if (this->visitedObjects.count(refAddress) != 0)
		{
			return; // already visited object
		}

		this->visitedObjects.insert(refAddress);

		try
		{
			void * pointer = this->objectTable->get(refAddress);

			GarbageCollectableInterface* visitable = (GarbageCollectableInterface*)pointer;

			if (visitable->preallocated())
			{
				return; // not allocated by GC
			}

			MemoryHeader* header = MemoryHeader::getHeader((char*)pointer);

			if (header->isTenured())
			{
				header->setColor(Color::BLACK);
			}

			visitable->accept(*this);
		}
		catch (...)
		{

		}
	}
}

void Marker::mark(word root)
{
	this->visit(root);
	this->visitedObjects.clear();
}
