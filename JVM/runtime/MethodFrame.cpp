#include "MethodFrame.h"



MethodFrame::MethodFrame()
{
}

MethodFrame::MethodFrame(size_t stackSize, size_t localVariablesSize)
{
	this->operandStack = new OperandStack(stackSize);
	this->localVariables = new LocalVariablesArray(localVariablesSize);
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


size_t MethodFrame::getMemorySize()
{
	return sizeof(MethodFrame);
}

size_t MethodFrame::getMemorySize(size_t stackSize, size_t localVariblesSize)
{
	return sizeof(MethodFrame)
		+ LocalVariablesArray::getMemorySize(localVariblesSize)
		+ OperandStack::getMemorySize(stackSize);
	// already included in size;
}

void MethodFrame::accept(ObjectVisitorInterface * visitor)
{
	for (size_t i = 0; i < this->operandStack->index; i++)
	{
		visitor->visit((*this->operandStack)[i]);
	}

	for (size_t i = 0; i < this->localVariables->index; i++)
	{
		visitor->visit((*this->localVariables)[i]);
	}

	if (this->parentFrame != NULL)
	{
		this->parentFrame->accept(visitor);
	}
}

void MethodFrame::accept(ObjectVisitorInterface & visitor)
{
	this->accept(&visitor);
}
