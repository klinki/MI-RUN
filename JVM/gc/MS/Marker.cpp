#include "Marker.h"
#include "../interfaces/GarbageCollectableInterface.h"
#include "../../types/ConversionFunctions.h"
#include "../../utils/Macros.h"

Marker::Marker()
{
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
		/*
		try
		{
			void * pointer = this->get(refAddress);
			GarbageCollectableInterface* visitable = (GarbageCollectableInterface*)pointer;

			size_t dataSize = this->getDataSize(pointer);

			unsigned char* memory;

			if (this->getAccessCounter(pointer) >= TENURATION_THRESHOLD)
			{
				memory = this->allocateOnPermanentSpace(dataSize);
				this->permanentSpaceRoot = address;
				this->edenSpaceRoot = NULL; // todo: this is probably wrong
				this->setColor(memory, Color::BLACK);
			}
			else
			{
				memory = this->allocate(dataSize);
				this->incrementAccessCounter(memory, this->getAccessCounter(pointer) + 1);
			}

			memcpy(memory, pointer, dataSize);

			this->updateAddress(refAddress, memory);
			this->setColor(pointer, Color::BAKER_MOVED);

			visitable->accept(*this);
		}
		catch (...)
		{

		}
		*/
	}
}

void Marker::Sweeper::visit(MethodFrame* methodFrame)
{

}

void Marker::Sweeper::visit(ObjectHeader* header)
{

}

void Marker::Sweeper::visit(Object* object)
{

}

void Marker::Sweeper::visit(word address)
{

}
