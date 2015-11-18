#include "Class.h"


Class::~Class()
{
}

unsigned int Class::getCountFields() const
{
	return 0;
}

bool Class::isFlagSet(FLAG flag) const
{
	return this->flags & flag == flag;
}
