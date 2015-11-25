#pragma once
#include <string>

class Utf16String
{
protected:
	std::u16string value;
public:
	Utf16String();
	~Utf16String();

	const std::u16string & getValue() const;
};
