#include "BakerObjectTable.h"
#include "../../runtime/MethodFrame.h"

BakerObjectTable::BakerObjectTable() : BakerObjectTable(10 * 1024 * 1024, 50 * 1024 * 1024) {};

BakerObjectTable::BakerObjectTable(size_t memorySize, size_t permSize)
{
	this->memorySlots[0] = new Heap(memorySize);
	this->memorySlots[1] = new Heap(memorySize);

	this->permanentSpace = new Heap(permSize);

	this->activeSlot = 0;
}

BakerObjectTable::~BakerObjectTable()
{
	delete this->memorySlots[0];
	delete this->memorySlots[1];
	delete this->permanentSpace;
}

void BakerObjectTable::visit(MethodFrame* methodFrame)
{
}

void BakerObjectTable::visit(Object* object)
{
}

void BakerObjectTable::visit(size_t address)
{
}

void BakerObjectTable::switchMemorySlot()
{
	this->activeSlot = this->activeSlot == 0 ? 1 : 0;
	this->finalize();
	this->memorySlots[this->activeSlot]->clear();
}

void BakerObjectTable::setGCRoot(word currentFrame)
{
	this->edenSpaceRoot = currentFrame;
}

void BakerObjectTable::visit(word address)
{
	if (isReferenceAddress(address))
	{
		int refAddress = getReferenceAddress((unsigned int)address);

		try 
		{
			VisitableInterface* pointer = this->get(refAddress);

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

			pointer->accept(*this);
		}
		catch (...)
		{

		}
	}
}

unsigned char * BakerObjectTable::allocate(size_t size)
{
	if (size == 0)
	{
		return NULL; // TODO: Throw exception
	}

	int slots = size / MEMORY_ALIGNMENT + 1;
	size_t bytesAllocated = slots * MEMORY_ALIGNMENT;
	
	if ((this->memorySlots[this->activeSlot]->usedBytes + bytesAllocated) >= this->memorySlots[this->activeSlot]->allocatedBytes)
	{
		// Time for garbage collection man!!
		this->collect();		
	}

	MemoryHeader* memory = (MemoryHeader*) new(this->memorySlots[this->activeSlot]->allocate(bytesAllocated)) MemoryHeader(size);
	return (unsigned char*)memory->data;
}

unsigned char * BakerObjectTable::allocateOnPermanentSpace(size_t size)
{
	if (size == 0)
	{
		return NULL; // TODO: Throw exception
	}

	int slots = size / MEMORY_ALIGNMENT + 1;
	size_t bytesAllocated = slots * MEMORY_ALIGNMENT;

	if ((this->permanentSpace->usedBytes + bytesAllocated) >= this->permanentSpace->allocatedBytes)
	{
		// Thats bad - time for FULL old space garbage collection!!
	}

	MemoryHeader* memory = (MemoryHeader*) new(this->permanentSpace->allocate(bytesAllocated)) MemoryHeader(size);
	return (unsigned char*)memory->data;
}

void BakerObjectTable::updateAddress(size_t index, void * newAddress)
{
	this->objectArray.allocatedArray[index] = (Object*)newAddress;
}

void BakerObjectTable::collect()
{
	this->switchMemorySlot();

	if ((int)this->edenSpaceRoot != NULL) 
	{
		this->visit(this->edenSpaceRoot);
	}
}

size_t BakerObjectTable::insert(void * ptr)
{
	size_t index = ObjectTable::insert(ptr);
	this->setKey(ptr, index);
	return index;
}

void BakerObjectTable::finalize()
{
	int* ptr = (int*)this->memorySlots[this->activeSlot]->data;
	int*endPtr = ptr + this->memorySlots[this->activeSlot]->allocatedBytes / sizeof(int);

	while (ptr != endPtr)
	{
		ptr += 3;
		int size = this->getDataSize(ptr);
		Object* objPtr = (Object*)ptr;

		if (this->getColor(ptr) != Color::BAKER_MOVED)
		{
			// finalize object
			if (objPtr->objectClass != NULL)
			{
				Method* method = objPtr->objectClass->methodArea.getMethod("finalize", "()");
			}
			// TODO: Finalize object

			this->hashMap.erase(this->getKey(ptr));

			ptr += size / sizeof(int);
		}
	}
}
