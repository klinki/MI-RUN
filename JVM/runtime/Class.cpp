#include "Class.h"
#include "MethodArea.h"

Class::~Class()
{

}

Class::Class(FLAG flag): flags(flag) 
{
    this->classLoader = NULL;
    this->constantPool = NULL;
    this->countInterfaces = 0;
    this->countNonStaticFields = 0;
    this->countStaticFields = 0;
    this->parentClass = NULL;
    this->implementedInterfaces = NULL;
    this->staticVariablesValues = NULL;
};

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
	int size = 1;

	if (field->type == TypeTag::DOUBLE || field->type == TypeTag::LONG)
	{
		size = 2;
	}

	if (!field->isStatic())
	{
		field->fieldIndex = this->countNonStaticFields;
		this->countNonStaticFields += size;
		this->hierarchicalCountNonStaticFields += size;
	}
	else
	{
		field->fieldIndex = this->countStaticFields;
		this->countStaticFields += size;
	}

	this->fieldsMap.add(field);
}

bool Class::isSubclassOf(Class* parent)
{
	if (this->parentClass == NULL)
	{
		return false;
	}
	else
	{
		return this->parentClass->fullyQualifiedName == parent->fullyQualifiedName || this->parentClass->isSubclassOf(parent);
	}
}

bool Class::implementsInterface(Class* parentInterface)
{
	for (int i = 0; i < this->countInterfaces; i++)
	{
		if (this->implementedInterfaces[i]->fullyQualifiedName == parentInterface->fullyQualifiedName || this->implementedInterfaces[i]->isSubclassOf(parentInterface))
		{
			return true;
		}
	}

	return false;
}

size_t Class::getHierarchicalCountNonStaticFields()
{
	if (this->hierarchicalCountNonStaticFields == -1)
	{
		Class* currentClass = this;

		this->hierarchicalCountNonStaticFields = 0;

		while (currentClass != nullptr)
		{
			this->hierarchicalCountNonStaticFields += currentClass->countNonStaticFields; 
			currentClass = currentClass->parentClass;
		}
	}

	return this->hierarchicalCountNonStaticFields;
}

void Class::setParent(Class* parent)
{
	this->hierarchicalCountNonStaticFields = -1;
	this->parentClass = parent;
	
	int index = this->getHierarchicalCountNonStaticFields() - this->countNonStaticFields;

	auto fieldIterator = this->fieldsMap.hashmap.startIterator();

	while (fieldIterator != this->fieldsMap.hashmap.endIterator())
	{
		Field* field = (Field*)fieldIterator->second;
		field->fieldIndex = index;

		if (field->isDoubleWord())
		{
			index += 2;
		}
		else
		{
			index++;
		}

		++fieldIterator;
	}

}
