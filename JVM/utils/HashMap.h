#pragma once
#include <unordered_map>

class ItemNotFoundException {};

template <class Key, class Value>
class HashMap
{
	/*
	struct Iterator
	{
		std::unordered_multimap<Key, Value> iterator;
		std::unordered_multimap<Key, Value> end;

	public:
		Iterator(std::unordered_multimap<Key, Value> first, std::unordered_multimap<Key, Value> last) : iterator(first), end(last)
		{
			iterator.begin();
		}

		bool hasNext() const
		{
			return iterator != end;
		}
		
		Value & const next()
		{
			return iterator->second;
		}
	};
	*/

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

	auto endIterator() const
	{
		return this->multimap.cend();
	}
};
