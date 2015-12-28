#include <iostream>
#include <string>
#include <iostream>
#include <windows.h>
#include "TreadMillGc.h"
#include "../utils/Array.h"
#include "../runtime/Object.h"

class Test2 { int arr[5]; public: static int wtf; };

class A
{
private:
	int value;
	std::string str;
	long long longVal;
	double doubleVal;

public:
	A() {}
	A(int val, std::string str, long long lon, double dl)
	{
		this->value = val;
		this->str = str;
		this->longVal = lon;
		this->doubleVal = dl;
	}

	friend std::ostream & operator<<(std::ostream &os, const A& a);



};

std::ostream & operator<< (std::ostream &os, const A& a)
{
	return os << a.value << " " << a.str << " " << a.longVal << " " << a.doubleVal << std::endl;
}

void experiments()
{
	char* memory = (char*)operator new(sizeof(A) * 2);
	A * aPtr = (A*) new(memory) A(10, "Hello World", (long long)(INT_MAX)+1, 1.25);
	A * bPtr = (A*) new(memory + sizeof(A)) A(22, "Testing It", 2500L, 3.14);

	//	*bPtr = 

	std::cout << "Address of ptr is: " << (void*)memory << std::endl;
	std::cout << "Address of object A is: " << aPtr << std::endl;
	std::cout << "Address of object A is: " << bPtr << std::endl;

	std::cout << "Size of object A is: " << sizeof(*aPtr) << std::endl;

	std::cout << *aPtr << std::endl;
	std::cout << *bPtr << std::endl;


	/*
	Structure:
	1) Init class loader, init internal state
	2) Read .jar file and load classes
	3) find main method and load it to memory (stackframe)
	4) run while loop with instructions switch
	*/

	SYSTEM_INFO si;
	GetSystemInfo(&si);

	printf("The page size for this system is %u bytes.\n", si.dwPageSize);

	TreadMillGc*  gc = new TreadMillGc(64 * 64);
	delete gc;


	size_t sizeofArray = sizeof(Array<Object*>);
	size_t sizeofItems = 10 * sizeof(Object*);

	unsigned char * test = (unsigned char*)operator new(sizeofArray + sizeofItems);

	Array<Object*> * arrayPtr = (Array<Object*> *) new(test) Array<Object*>(10, test);

	for (int i = 0; i < 10; i++)
	{
		(*arrayPtr)[i] = (Object*)i;
	}

	for (int i = 0; i < 10; i++)
	{
		std::cout << (*arrayPtr)[i] << std::endl;
	}


	unsigned char * objPtr = (unsigned char*)operator new(Object::getMemorySize(10));

	unsigned char *lastAddress = objPtr + Object::getMemorySize(10);


	Object * obj = (Object*) new(objPtr) Object(10, NULL, objPtr);

	for (int i = 0; i < 10; i++)
	{
		obj->fields[i] = i;
	}

	for (int i = 0; i < 10; i++)
	{
		int field = (*obj->fields)[i];
		std::cout << field << std::endl;
	}


	return;
}
