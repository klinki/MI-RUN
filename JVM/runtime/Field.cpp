#include "Field.h"

void Field::setAttribute(int pos, int ref) 
{
	attributes[pos] = ref;
}


Field::~Field()
{
	delete[] attributes;
}
