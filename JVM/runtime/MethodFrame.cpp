#include "MethodFrame.h"
#include "Class.h"


MethodFrame::MethodFrame()
{
}

MethodFrame::MethodFrame(size_t stackSize, size_t localVariablesSize)
{
	this->operandStack = new OperandStack(stackSize);
	this->localVariables = new LocalVariablesArray(localVariablesSize);
	this->pc = 0;
	this->sp = 0;
}

MethodFrame::MethodFrame(Method * method, MethodFrame * parent): 
	MethodFrame(method->operandStackSize, method->localVariablesArraySize, parent, 
		method->classPtr->constantPool, method, NULL)
{
}

MethodFrame::MethodFrame(size_t stackSize, size_t localVariablesSize, MethodFrame * parent, ConstantPool * constantPool, Method * method, byte * address)
{
	this->pc = 0;
	this->sp = 0;
	this->method = method;
	this->constantPool = constantPool;
	this->parentFrame = parent;
	this->childFrame = NULL;

	this->localVariables = new(&this->operandStack + 1) LocalVariablesArray(stackSize, (byte*)&this->operandStack + 1);
	this->operandStack = new((byte*)(&this->operandStack) + sizeof(this->operandStack) + LocalVariablesArray::getMemorySize(localVariablesSize)) OperandStack(stackSize, (byte*)(&this->operandStack + LocalVariablesArray::getMemorySize(localVariablesSize)));
}

MethodFrame::~MethodFrame()
{
}

size_t MethodFrame::getMemorySize(size_t stackSize, size_t localVariblesSize)
{
	return sizeof(MethodFrame)
		+ LocalVariablesArray::getMemorySize(localVariblesSize)
		+ OperandStack::getMemorySize(stackSize);
}

void MethodFrame::accept(ObjectVisitorInterface * visitor)
{
	for (size_t i = 0; i < this->operandStack->index; i++)
	{
		visitor->visit((*this->operandStack)[i]);
	}

	for (size_t i = 0; i < this->localVariables->allocatedSize; i++)
	{
		visitor->visit((*this->localVariables)[i]);
	}

	if (this->parentFrame != NULL)
	{
		visitor->visit(this->parentFrame);
	}
}

void MethodFrame::accept(ObjectVisitorInterface & visitor)
{
	this->accept(&visitor);
}

bool MethodFrame::requiresFinalization()
{
	return false;
}
