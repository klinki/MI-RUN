#pragma once
#include "../utils/HashMap.h"
#include "../utils/Macros.h"
#include "../utils/Utf8String.h"
#include "ClassMember.h"

class ClassMemberMap
{
visibility:
	HashMap<Utf8String, ClassMember*> hashmap;
public:
	ClassMemberMap() {}
	~ClassMemberMap() {}

	ClassMember* get(const Utf8String & name, const Utf8String & descriptor)
	{
		auto iterator = this->hashmap.getIterator(name);

		if (this->hashmap.count(name) > 1)
		{
			for ( ; iterator != this->hashmap.endIterator(); ++iterator)
			{
				ClassMember* value = (ClassMember*)iterator->second;
				if (value->descriptor == descriptor && value->name.equals(name))
				{
					return value;
				}
			}
		}
		else
		{
			ClassMember* value = (ClassMember*)iterator->second;

			if (value->descriptor == descriptor)
			{
				return value;
			}
		}
	}

	void add(ClassMember* classMember)
	{
		this->hashmap.insert(classMember->name, classMember);
	}
};
