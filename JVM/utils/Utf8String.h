#pragma once
#include <string>
class Utf8String
{
protected:
	size_t dataLength;
	size_t stringLength;
	size_t hash;

	char* data;

	size_t calculateHash();

public:
	Utf8String();
	Utf8String(size_t length, bool preallocated)
	{
		this->dataLength = length;
		this->data = (char*)(&this->data + 1);
	}

	Utf8String(const char* string);
	Utf8String(const char* string, bool preallocated);
	Utf8String(const char* string, size_t length, bool preallocated);
	Utf8String(const char* bytes, size_t length);
	Utf8String(const unsigned char* bytes, size_t length);
	Utf8String(const std::string & string);
	Utf8String(const Utf8String &);
	Utf8String& operator=(const Utf8String & u);
	~Utf8String();

	const char* toAsciiString() const;
	
	size_t length() const
	{
		return this->stringLength;
	}

	size_t bytes() const
	{
		return this->dataLength;
	}

	size_t getHash() const
	{
		return this->hash;
	}

	bool equals(const Utf8String & b) const;

	size_t getMemorySize()
	{
		return getMemorySize(this->dataLength);
	}

	static size_t getMemorySize(size_t items)
	{
		return sizeof(Utf8String) + items * sizeof(char);
	}

	friend std::hash<Utf8String>;
	friend inline bool operator==(const Utf8String & a, const Utf8String & b);	
};

namespace std
{
	template <> struct hash<Utf8String>
	{
		inline size_t std::hash<Utf8String>::operator()(const Utf8String & x) const
		{
			return x.hash;
		}
	};
}

inline bool operator==(const Utf8String & a, const Utf8String & b)
{
	return a.length() == b.length() && a.hash == b.hash;
}

inline bool operator!=(const Utf8String & a, const Utf8String & b)
{
	return !(a == b);
}
