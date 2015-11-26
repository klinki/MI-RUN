#include "Class.h"


Class::~Class()
{
}
Class::Class()
{
}

unsigned int Class::getCountFields() const
{
	return 0;
}

bool Class::isFlagSet(FLAG flag) const
{
	return (this->flags & flag) == flag;
}

void  Class::setConstantPool(ConstantPool * CP)
{
	//this->constantPool = CP;
}
void  Class::setName(Utf8String * name) {}
