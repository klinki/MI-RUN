#include "ClassMap.h"



ClassMap::ClassMap()
{
}


ClassMap::~ClassMap()
{
}

Class* ClassMap::getClass(const Utf8String & name)
{
	try
	{
		auto iterator = this->hashmap.getIterator(name);

		if (this->hashmap.count(name) > 1)
		{
			for (; iterator != this->hashmap.endIterator(); ++iterator)
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
	catch (const ItemNotFoundException&)
	{
		return nullptr;
	}
	
}


void ClassMap::addClass(Class* classRef)
{

	Utf8String name = classRef->fullyQualifiedName;
	hashmap.insert(name, classRef);
}
