#include "MethodArea.h"



MethodArea::MethodArea()
{
}


MethodArea::~MethodArea()
{
	auto iterator = this->hashmap.startIterator();
	
	while (iterator != this->hashmap.endIterator())
	{
		Method* classPtr =  (Method*)iterator->second;
		delete classPtr;
		++iterator;
	}
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
	//fprintf(stderr,"add method \n");

	this->hashmap.insert(method->name,method);

}
