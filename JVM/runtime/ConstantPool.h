#include <iostream>
#include <cstdlib>

#pragma once
class ConstantPool
{
private:
	int constant_pool_count;
	unsigned char** constPool;//[constant_pool_count]([0] - type)[1-9] info; if type =1 info is longer,said by [1-2]]
public:
	ConstantPool();
	ConstantPool(int size);
	//ConstantPool(const ConstantPool & CP);
	void print();
	int add(int pos, unsigned char type, int length, unsigned char * data);
	int GetSize();
	unsigned char * getElem(int pos, int & length);
	unsigned char * getElem(int pos);
	~ConstantPool();
};
