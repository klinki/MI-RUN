#pragma once
#include <string>
class Utf8String
{
protected:
	unsigned char* data;
	unsigned int dataLength;
	unsigned int stringLength;
public:
	Utf8String();
	Utf8String(const char* bytes, int length);
	~Utf8String();

	std::string toAsciiString();
	unsigned int length() const;
	unsigned int bytes() const;
};
