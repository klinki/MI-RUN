#include "Class.h"
#include "MethodArea.h"

Class::~Class()
{

}

unsigned int Class::getCountFields() const
{
	return countNonStaticFields;
}

bool Class::isFlagSet(FLAG flag) const
{
	return (this->flags & flag) == flag;
}

Method * Class::getMethod(const Utf8String & methodName, const Utf8String & descriptor)
{
	Method* method = nullptr;

	method = (Method*)this->methodArea.getMethod(methodName, descriptor);

	// 1. if it is in current class, return right away
	if (method != nullptr)
	{
		return method;
	}

	// 2. otherwise recursively scan parent classes 
	if (this->parentClass != nullptr)
	{
		method = this->parentClass->getMethod(methodName, descriptor);
	}

	// 3. at last, scan interfaces
	for (int i = 0; i < this->countInterfaces; i++)
	{
		method = (Method*)this->implementedInterfaces[i]->methodArea.getMethod(methodName, descriptor);

		if (method != nullptr)
		{
			return method;
		}
	}

	return method;
}

Field * Class::getField(const Utf8String & name, const Utf8String & descriptor)
{
	Field* field = nullptr;

	field = (Field*)this->fieldsMap.get(name, descriptor);

	// 1. if it is in current class, return right away
	if (field != nullptr)
	{
		return field;
	}

	// otherwise scan interfaces first
	for (int i = 0; i < this->countInterfaces; i++)
	{
		field = (Field*)this->implementedInterfaces[i]->fieldsMap.get(name, descriptor);

		if (field != nullptr)
		{
			return field;
		}
	}

	// and then recursively scan parent classes 
	if (this->parentClass != nullptr)
	{
		field = this->parentClass->getField(name, descriptor);
	}

	return field;
}

void Class::addField(Field * field)
{
	if (!field->isStatic())
	{
		this->countNonStaticFields++;
	}

	this->fieldsMap.add(field);
}
