#pragma once
#include <iostream>
#include <cstdlib>
#include "../jvm_structures/JavaConstantPool.h"



class ConstantPool
{
private:
	int constant_pool_count;
	//unsigned char** constPool;//[constant_pool_count]([0] - type)[1-9] info; if type =1 info is longer,said by [1-2]]
	ConstantPoolItem * constantPool;
public:
	ConstantPool();
	ConstantPool(int size);
	void print();
	int add(int pos, int type, int length, unsigned char * data);
	//int add(int pos, unsigned char type, int length, unsigned char * data);
	int GetSize();
	//unsigned char * getElem(int pos, int & length);
	//unsigned char * getElem(int pos);

	ConstantPoolItem * get(int index);

	~ConstantPool();
};
