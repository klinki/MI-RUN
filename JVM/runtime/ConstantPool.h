#pragma once
#include <iostream>
#include <cstdlib>
#include "../jvm_structures/JavaConstantPool.h"

class Runtime;

class ConstantPool
{
protected:
	int constant_pool_count;
	ConstantPoolItem * constantPool;
	Runtime* runtime;
public:
	ConstantPool();
	ConstantPool(int size, Runtime* runtime = NULL);
	void print();

	int add(int pos, int type, int length, char * data);

	int GetSize();
	void add(int pos, ConstantPoolItem * item);

	ConstantPoolItem * get(int index);
	void resolveStringRef();
	void setClassPtr(int index,Class * c);
	void setFieldPtr(int index, Field * f);
	void setMethodPtr(int index, Method * m);
	~ConstantPool();
};
