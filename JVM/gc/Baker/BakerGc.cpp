#include "BakerGc.h"
#include "../../runtime/MethodFrame.h"
#include "../../runtime/ExecutionEngine.h"
#include "../debug/DebugVisitor.h"
#include "../../runtime/Runtime.h"
#include "../PermSpaceHeap.h"
#include "../MS/Marker.h"
#include "../MS/Sweeper.h"

BakerGc::BakerGc() : BakerGc(10 * 1024 , 50 * 1024 * 1024) {};

BakerGc::BakerGc(Runtime* runtime, size_t memorySize, size_t permSize)
{
	this->runtime = runtime;

	this->memorySlots[0] = new Heap(memorySize);
	this->memorySlots[1] = new Heap(memorySize);

	this->permanentSpace = new PermSpaceHeap(permSize);
	this->marker = new Marker(this);
	this->sweeper = new Sweeper(this);

	this->activeSlot = 0;
}

BakerGc::BakerGc(size_t memorySize, size_t permSize): BakerGc(NULL, memorySize, permSize)
{
}

BakerGc::~BakerGc()
{
	delete this->memorySlots[0];
	delete this->memorySlots[1];
	delete this->permanentSpace;
}

void BakerGc::visit(MethodFrame* methodFrame)
{
	int key = this->getHeader(methodFrame)->key;
	return this->visit((word)makeReferenceAddress(key));
}

void BakerGc::visit(Object* object)
{
}

void BakerGc::visit(size_t address)
{
}

void BakerGc::switchMemorySlot()
{
	this->activeSlot = this->activeSlot == 0 ? 1 : 0;
}

void BakerGc::visit(word address)
{
	if (isReferenceAddress(address))
	{
		int refAddress = getReferenceAddress((unsigned int)address);

		if (this->visitedObjects.count(refAddress) > 0)
		{
			return; // already visited object
		}

		this->visitedObjects.insert(refAddress);

		try
		{
			void * pointer = this->get(refAddress);

			GarbageCollectableInterface* visitable = (GarbageCollectableInterface*)pointer;

			if (visitable->preallocated()) 
			{
				return; // not allocated by GC
			}

			MemoryHeader* header = this->getHeader((char*)pointer);

			size_t dataSize = this->getHeader(pointer)->size;

			unsigned char* memory;

			if (! header->isTenured())
			{
				if (this->getHeader(pointer)->accessCounter >= TENURATION_THRESHOLD)
				{
					memory = this->allocateOnPermanentSpace(dataSize);
					this->getHeader((char*)memory)->tenure();
				}
				else
				{
					memory = this->allocate(dataSize);
					this->getHeader(memory)->incrementAccessCounter();
				}

				visitable->copyTo(memory);

				this->updateAddress(refAddress, memory);
				this->getHeader(pointer)->setColor(Color::BAKER_MOVED);
			}
				
			visitable->accept(*this);
		}
		catch (...)
		{

		}
	}
}

void BakerGc::visit(ObjectHeader* header)
{

}

size_t BakerGc::countAllocatedBlockSize(size_t size)
{
	int totalAllocated = size + sizeof(MemoryHeader);

	int slots = totalAllocated / MEMORY_ALIGNMENT;

	if (totalAllocated % MEMORY_ALIGNMENT != 0)
	{
		slots++;
	}

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

	if (bytesAllocated >= EDEN_SPACE_LIMIT)
	{
		return this->allocateOnPermanentSpace(size);
	}
	else
	{
		return this->allocateOnEdenSpace(size);
	}
}

unsigned char * BakerGc::allocateOnEdenSpace(size_t size)
{
	if (size == 0)
	{
		return NULL; // TODO: Throw exception
	}
	
	size_t bytesAllocated = this->countAllocatedBlockSize(size);
	DEBUG_BLOCK(std::cerr << "Allocating object of size: " << size << " to 16 aligned size: " << bytesAllocated << " on EDEN space" << std::endl );

	if ((this->memorySlots[this->activeSlot]->usedBytes + bytesAllocated) >= this->memorySlots[this->activeSlot]->allocatedBytes)
	{
		DEBUG_PRINT("Allocation cannot proceed, garbage collection needed\n");
		// Time for garbage collection man!!
		this->collect();		
	}

	void* allocatedAddress = this->memorySlots[this->activeSlot]->allocate(bytesAllocated);
	MemoryHeader* memory = (MemoryHeader*) new(allocatedAddress) MemoryHeader(size);

	DEBUG_PRINT("Allocated memory with address: %p, data start at address: %p\n", (void*) allocatedAddress, (void*) memory->data);

	return (unsigned char*)memory->data;
}

unsigned char * BakerGc::allocateOnPermanentSpace(size_t size)
{
	if (size == 0)
	{
		return NULL; // TODO: Throw exception
	}

	size_t bytesAllocated = this->countAllocatedBlockSize(size);

	DEBUG_BLOCK(std::cerr << "Allocating object of size: " << size << " to 16 aligned size: " << bytesAllocated << " on TENURED space" << std::endl);


	if ((this->permanentSpace->usedBytes + bytesAllocated) >= this->permanentSpace->allocatedBytes)
	{
		// Thats bad - time for FULL old space garbage collection!!
		this->fullCollect();
	}

	MemoryHeader* memory = (MemoryHeader*) new(this->permanentSpace->allocate(bytesAllocated)) MemoryHeader(size);
	memory->tenure(); // automatically tenured - do not move to eden space...
	return (unsigned char*)memory->data;
}

void BakerGc::updateAddress(size_t index, void * newAddress)
{
	this->hashMap[index] = newAddress;
}

void BakerGc::collect()
{
	DEBUG_PRINT("Garbage collection starts...\n");

	word frameIndex = this->runtime->executionEngine->callStack->top();

	Heap* oldSlot = this->memorySlots[this->activeSlot];
	this->switchMemorySlot();

	if ((int)frameIndex != 0) 
	{
#ifdef _DEBUG
		DebugVisitor visitor(this);
//		visitor.visit(frameIndex);
#endif

		this->visit(frameIndex);
	}

	this->finalize(oldSlot);
	oldSlot->clear();
	this->visitedObjects.clear();
}

size_t BakerGc::insert(void * ptr)
{
	size_t index = ObjectTable::insert(ptr);
	this->getHeader(ptr)->setKey(index);
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
//	return; // TODO: THERE IS BUG IN FINALIZATION, REMOVE WHEN FIXED

	DEBUG_PRINT("Finalization\n");

	unsigned char* ptr = (unsigned char*)slot->data;
	unsigned char* endPtr = ptr + slot->usedBytes;

	while (ptr != endPtr)
	{
		ptr += sizeof(MemoryHeader);
		int size = this->getHeader(ptr)->size;
		GarbageCollectableInterface* objPtr = (GarbageCollectableInterface*)ptr;

		if (this->getHeader(ptr)->accessCounter != Color::BAKER_MOVED)
		{
			// finalize object
			this->finalize(objPtr);

			DEBUG_PRINT("Removing key: %d from table\n", this->getHeader(ptr)->key);

			this->remove(this->getHeader(ptr)->key);
		}

		ptr += size;

		int rem = size % BakerGc::MEMORY_ALIGNMENT;

		if (rem != 0)
		{
			ptr += BakerGc::MEMORY_ALIGNMENT - rem;
		}
	}
}

void BakerGc::finalize(GarbageCollectableInterface * objPtr)
{
	if (objPtr->requiresFinalization())
	{
		Method* method = objPtr->getFinalizationMethod();

		if (method->isNative())
		{
			method->nativeMethod((Object*)objPtr, engine);
		}
		else
		{
			unsigned char* frameMemory = this->allocate(MethodFrame::getMemorySize(method->operandStackSize, method->localVariablesArraySize));
			MethodFrame * frame = new(frameMemory) MethodFrame(method->operandStackSize, method->localVariablesArraySize,
			this->runtime->executionEngine->getCurrentMethodFrame(), method->classPtr->constantPool, method, NULL);

			this->runtime->executionEngine->execute(frame);
		}
	}
}

void BakerGc::fullCollect()
{
	word frameIndex = this->runtime->executionEngine->callStack->top();
	this->marker->mark(frameIndex);
	this->sweeper->sweep(this->permanentSpace->data);
}
