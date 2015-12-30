#include "BakerGc.h"
#include "../../runtime/MethodFrame.h"
#include "../../runtime/ExecutionEngine.h"

BakerGc::BakerGc() : BakerGc(10 * 1024 * 1024, 50 * 1024 * 1024) {};

BakerGc::BakerGc(size_t memorySize, size_t permSize)
{
	this->memorySlots[0] = new Heap(memorySize);
	this->memorySlots[1] = new Heap(memorySize);

	this->permanentSpace = new Heap(permSize);

	this->activeSlot = 0;
}

BakerGc::~BakerGc()
{
	delete this->memorySlots[0];
	delete this->memorySlots[1];
	delete this->permanentSpace;
}

void BakerGc::visit(MethodFrame* methodFrame)
{
}

void BakerGc::visit(Object* object)
{
}

void BakerGc::visit(size_t address)
{
}

void BakerGc::switchMemorySlot()
{
	Heap* oldSlot = this->memorySlots[this->activeSlot];
	this->activeSlot = this->activeSlot == 0 ? 1 : 0;
	this->finalize(oldSlot);
	this->memorySlots[this->activeSlot]->clear();
}

void BakerGc::setGCRoot(word currentFrame)
{
	this->edenSpaceRoot = currentFrame;
}

void BakerGc::visit(word address)
{
	if (isReferenceAddress(address))
	{
		int refAddress = getReferenceAddress((unsigned int)address);

		try 
		{
			GarbageCollectableInterface* pointer = this->get(refAddress);

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

size_t BakerGc::countAllocatedBlockSize(size_t size)
{
	int totalAllocated = size + sizeof(MemoryHeader);

	int slots = totalAllocated / MEMORY_ALIGNMENT + 1;
	size_t bytesAllocated = slots * MEMORY_ALIGNMENT;

	return bytesAllocated;
}

unsigned char * BakerGc::allocate(size_t size)
{
	if (size == 0)
	{
		return NULL; // TODO: Throw exception
	}

	size_t bytesAllocated = this->countAllocatedBlockSize(size);
	
	if ((this->memorySlots[this->activeSlot]->usedBytes + bytesAllocated) >= this->memorySlots[this->activeSlot]->allocatedBytes)
	{
		// Time for garbage collection man!!
		this->collect();		
	}

	MemoryHeader* memory = (MemoryHeader*) new(this->memorySlots[this->activeSlot]->allocate(bytesAllocated)) MemoryHeader(size);
	return (unsigned char*)memory->data;
}

unsigned char * BakerGc::allocateOnPermanentSpace(size_t size)
{
	if (size == 0)
	{
		return NULL; // TODO: Throw exception
	}

	size_t bytesAllocated = this->countAllocatedBlockSize(size);

	if ((this->permanentSpace->usedBytes + bytesAllocated) >= this->permanentSpace->allocatedBytes)
	{
		// Thats bad - time for FULL old space garbage collection!!
	}

	MemoryHeader* memory = (MemoryHeader*) new(this->permanentSpace->allocate(bytesAllocated)) MemoryHeader(size);
	return (unsigned char*)memory->data;
}

void BakerGc::updateAddress(size_t index, void * newAddress)
{
	this->hashMap[index] = newAddress;
}

void BakerGc::collect()
{
	this->switchMemorySlot();

	if ((int)this->edenSpaceRoot != NULL) 
	{
		this->visit(this->edenSpaceRoot);
	}
}

size_t BakerGc::insert(void * ptr)
{
	size_t index = ObjectTable::insert(ptr);
	this->setKey(ptr, index);
	return index;
}

size_t BakerGc::insert(void * ptr, bool systemObject)
{
	if (!systemObject)
	{
		this->insert(ptr);
	}
	else
	{
		return ObjectTable::insert(ptr);
	}
}

void BakerGc::finalize(Heap* slot)
{
	unsigned char* ptr = (unsigned char*)slot->data;
	unsigned char* endPtr = ptr + slot->usedBytes;

	while (ptr != endPtr)
	{
		ptr += sizeof(MemoryHeader);
		int size = this->getDataSize(ptr);
		GarbageCollectableInterface* objPtr = (GarbageCollectableInterface*)ptr;

		if (this->getColor(ptr) != Color::BAKER_MOVED)
		{
			// finalize object
			if (objPtr->requiresFinalization())
			{
				Method* method = objPtr->getFinalizationMethod(); // objectClass->getMethod("finalize", "()V");
				unsigned char* frameMemory = this->allocate(MethodFrame::getMemorySize(method->operandStackSize, method->localVariablesArraySize));
				MethodFrame * frame = new(frameMemory) MethodFrame(method->operandStackSize, method->localVariablesArraySize, NULL, NULL, method, NULL);
			
				if (method->isNative())
				{
					method->nativeMethod((Object*)objPtr, engine);
				}
				else
				{
					this->engine->execute(frame);
				}
			}
			// TODO: Finalize object

			this->hashMap.erase(this->getKey(ptr));

			ptr += size;
			ptr += MEMORY_ALIGNMENT - (size % MEMORY_ALIGNMENT);
		}
	}
}
