#include "MethodArea.h"



MethodArea::MethodArea()
{
}


MethodArea::~MethodArea()
{
}

Method* MethodArea::getMethod(const Utf8String & name, const Utf8String & descriptor)
{
	auto iterator = this->hashmap.getIterator(name);

	if (this->hashmap.count(name) > 1)
	{
		for (; iterator != this->hashmap.endIterator(); ++iterator)
		{
			Method* value = (Method*)iterator->second;
			if (value->descriptor == descriptor && value->name.equals(name))
			{
				return value;
			}
		}
	}
	else
	{
		Method* value = (Method*)iterator->second;

		if (value->descriptor == descriptor)
		{
			return value;
		}
	}

	return nullptr;
}


void MethodArea::addMethod(Method* method)
{}
