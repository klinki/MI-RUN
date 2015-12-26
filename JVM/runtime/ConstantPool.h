#pragma once
#include <iostream>
#include <cstdlib>
#include "../jvm_structures/JavaConstantPool.h"



class ConstantPool
{
private:
	int constant_pool_count;
	ConstantPoolItem * constantPool;
public:
	ConstantPool();
	ConstantPool(int size);
	void print();

	int add(int pos, int type, int length, unsigned char * data);
	int GetSize();
	void add(int pos, ConstantPoolItem * item);

	ConstantPoolItem * get(int index);
	void resolveStringRef();
	void setClassPtr(int index,Class * c);
	void setFieldPtr(int index, Field * f);
	void setMethodPtr(int index, Method * m);
	~ConstantPool();
};
