#include "MethodArea.h"



MethodArea::MethodArea()
{
}


MethodArea::~MethodArea()
{
}

Method* MethodArea::getMethod(const Utf8String & name, const Utf8String & descriptor)
{
	
	try
	{
		auto iterator = this->hashmap.getIterator(name);

		if (this->hashmap.count(name) > 1)
		{
			for (; iterator != this->hashmap.endIterator(); ++iterator)
			{
				Method* value = iterator->second;
				if (value->descriptor == descriptor && value->name.equals(name))
				{
					return value;
				}
			}
		}
		else
		{
			Method* value = iterator->second;

			if (value->descriptor == descriptor)
			{
				return value;
			}
		}
	}
	catch (const ItemNotFoundException &e)
	{
		return nullptr;
	}
	return nullptr;
}


void MethodArea::addMethod(Method* method)
{
	printf("add method\n");
	this->hashmap.insert(method->name,method);

}
