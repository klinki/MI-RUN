#include "ClassMap.h"



ClassMap::ClassMap()
{
}


ClassMap::~ClassMap()
{
    auto iterator = this->hashmap.startIterator();
    
    while (iterator != this->hashmap.endIterator())
    {
        Class* classPtr =  (Class*)iterator->second;
        delete classPtr;
        ++iterator;
    }
}

Class* ClassMap::getClass(const Utf8String & name)
{
	try
	{
		if (name.toAsciiString()[0] == '[')
		{
			return this->getClass("java/lang/Object");
		}

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
