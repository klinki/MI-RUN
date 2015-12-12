#include "Class.h"


Class::~Class()
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
/*
void  Class::setConstantPool(ConstantPool CP)
{
	this->constantPool = CP;
}
void  Class::setName(Utf8String name) {
	fullyQualifiedName = name;
}
*/


Method * Class::getMethod(const Utf8String & methodName, Utf8String & descriptor)
{
	Class* lookupClass = this;
	Method* method = nullptr;

	while (lookupClass != nullptr)
	{
		// method = lookupClass->methodArea.getMethod(methodName);

		if (method != nullptr)
		{
			break;
		}
		else
		{
			lookupClass = lookupClass->parentClass;
		}
	}

	return method;
}
