#pragma once
#include <string>
class Utf8String
{
protected:
	unsigned char* data;
	size_t dataLength;
	size_t stringLength;
	size_t hash;

	size_t calculateHash();

public:
	Utf8String();
	Utf8String(const char* string);
	Utf8String(const char* bytes, size_t length);
	Utf8String(const unsigned char* bytes, size_t length);
	Utf8String(const std::string & string);
	Utf8String& operator=(const Utf8String & u);
	~Utf8String();

	std::string toAsciiString();
	
	size_t length() const
	{
		return this->stringLength;
	}

	size_t bytes() const;

	bool equals(const Utf8String & b) const;

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
