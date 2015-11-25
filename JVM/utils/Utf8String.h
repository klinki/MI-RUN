#pragma once
#include <string>
class Utf8String
{
protected:
	std::string value;
	unsigned char* data;
	unsigned int dataLength;
	unsigned int stringLength;
	unsigned int hash;

public:
	Utf8String();
	Utf8String(const char* bytes, int length);
	~Utf8String();

	std::string toAsciiString();
	unsigned int length() const;
	unsigned int bytes() const;


	friend std::hash<Utf8String>;
};

namespace std 
{
	template <> struct hash<Utf8String>
	{
		size_t operator()(const Utf8String & x) const;
	};
}
