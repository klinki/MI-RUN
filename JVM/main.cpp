#include <iostream>
#include "classfile\ClassLoader.h"

class ClassWithArray
{
public:
	int arrayLength = 0;
	char array[1];
	int intArray[1];
};

struct StructWithArray
{
public:
	int arrayLength = 0;
	char array[1];
	int intArray[1];
};


int main(int argc, const char argv[])
{
	ClassLoader classLoader;
	classLoader.load("Arithmetics.class");

	const char * string = "this is just sample string";

	ClassWithArray * classPtr;

	std::cout << " sizeof string: " << sizeof(string) << std::endl;

	StructWithArray * structPtr = (StructWithArray *)malloc(sizeof(StructWithArray) + strlen(string) * sizeof(string) + 1 + sizeof(int) * 16);
	structPtr->arrayLength = strlen(string);

	for (int i = 0; i < 16; i++)
	{
		structPtr->intArray[i] = 0;
	}

	structPtr->intArray[0] = 1;
	structPtr->intArray[3] = 10;
	structPtr->intArray[15] = 1;

	strcpy_s((char*)structPtr->array, strlen(string) + 1, string);

	printf("%s", structPtr->array);
	std::cout << sizeof(structPtr) << std::endl;

	for (int i = 0; i < 16; i++)
	{
		std::cout << structPtr->intArray[i] << std::endl;
	}

	/*
		Structure:
			1) Init class loader, init internal state
			2) Read .jar file and load classes
			3) find main method and load it to memory (stackframe)
			4) run while loop with instructions switch
	*/

	return 0;
}
