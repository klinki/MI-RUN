#pragma once
#include <unordered_map>

class ItemNotFoundException {};

template <class Key, class Value>
class HashMap
{
protected:
	std::unordered_multimap<Key, Value> multimap;
public:
	HashMap()
	{
	}
	
	~HashMap()
	{
		
	}

	void insert(const Key & k, const Value & v)
	{
		this->multimap.emplace(k, v);
	}

	void contains(const Key & k)
	{
		this->multimap.count(k) > 0;
	}

	auto getIterator(const Key & k)
	{
		
			auto iterator = this->multimap.find(k);

			if (iterator == this->multimap.end())
			{
				throw ItemNotFoundException();
			}

			return iterator;

		
	}

	int count(const Key & k)
	{
		return this->multimap.count(k);
	}

	auto endIterator() const
	{
		return this->multimap.cend();
	}
};
