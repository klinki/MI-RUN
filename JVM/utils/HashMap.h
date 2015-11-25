#pragma once
#include <unordered_map>
template <class Key, class Value>
class HashMap
{
protected:
	std::unordered_multimap<Key, Value> multimap;
public:
	HashMap()
	{
	}
	~HashMap();

	public void insert(Key & k, Value & v)
	{
		this->multimap.emplace(k, v);
	}


};
