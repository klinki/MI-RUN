#include "ClassMap.h"



ClassMap::ClassMap()
{
}


ClassMap::~ClassMap()
{
}

Class* ClassMap::getClass(const Utf8String & name)
{
	auto iterator = this->hashmap.getIterator(name);

	if (this->hashmap.count(name) > 1)
	{
		for ( ; iterator != this->hashmap.endIterator(); ++iterator)
		{
			Class* value = (Class*)iterator->second;
			if (value->fullyQualifiedName.equals(name))
			{
				return value;
			}
		}
	}
	else
	{
		Class* value = (Class*)iterator->second;
		return value;
	}

	return nullptr;
}


void ClassMap::addClass(Class* classRef)
{

}
