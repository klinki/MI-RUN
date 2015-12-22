#include "Object.h"



Object::Object(size_t fields, Class * objectClass, byte * address): objectClass(objectClass), fields(fields, address + sizeof(objectClass)) 
{
	
}

Object::Object(size_t fields, Class * objectClass): objectClass(objectClass), fields(fields)
{
}

Object::Object()
{
}


Object::~Object()
{
}

size_t Object::getMemorySize()
{
	return sizeof(Object);
}

size_t Object::getMemorySize(size_t fields)
{
	return sizeof(Object) + LocalVariablesArray::getMemorySize(fields) - sizeof(LocalVariablesArray); // already included in size;
}

void Object::accept(ObjectVisitorInterface * visitor)
{
	for (int i = 0; i < this->fields.allocatedSize; i++)
	{
		visitor->visit(this->fields[i]);
	}
}

void Object::accept(ObjectVisitorInterface & visitor)
{
	this->accept(&visitor);
}
