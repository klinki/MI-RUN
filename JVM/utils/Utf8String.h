#pragma once
#include <string>
class Utf8String
{
protected:
	std::string value;
	unsigned char* data;
	size_t dataLength;
	size_t stringLength;
	size_t hash;

public:
	Utf8String();
	Utf8String(const char* bytes, size_t length);
	Utf8String(std::string string);
	~Utf8String();

	std::string toAsciiString();
	size_t length() const;
	size_t bytes() const;

	bool equals(const Utf8String & b) const;

	friend std::hash<Utf8String>;
	friend bool operator==(const Utf8String & a, const Utf8String & b);
};

namespace std 
{
	template <> struct hash<Utf8String>
	{
		size_t operator()(const Utf8String & x) const;
	};
}

bool operator==(const Utf8String & a, const Utf8String & b);
bool operator!=(const Utf8String & a, const Utf8String & b);
