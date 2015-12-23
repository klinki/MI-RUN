#include "ExceptionTable.h"


ExceptionTable::ExceptionTable()
{
	
}
Exception* ExceptionTable::getException(const Utf8String & name)
{
	try
	{
		auto iterator = this->hashmap.getIterator(name);

		if (this->hashmap.count(name) > 1)
		{
			for (; iterator != this->hashmap.endIterator(); ++iterator)
			{
				Exception* value = (Exception*)iterator->second;
				//if (value->fullyQualifiedName.equals(name))
				//{
					return value;
				//}
			}
		}
		else
		{
			Exception* value = (Exception*)iterator->second;
			return value;
		}

		return nullptr;
	}
	catch (const ItemNotFoundException&)
	{
		return nullptr;
	}

}
void ExceptionTable::addException(Utf8String name, int s, int e, int h, int c)
{
	Exception * exc = new Exception(s,e,h,c);
	this->hashmap.insert(name,exc);


}
ExceptionTable::~ExceptionTable()
{
}
