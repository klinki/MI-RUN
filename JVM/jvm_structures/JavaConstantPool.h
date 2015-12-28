#pragma once
#include "Reference.h"
#include "../types/ConversionFunctions.h"
#include "../utils/Utf8String.h"

typedef unsigned short ConstantPoolAddress;

class Class;
class Field;
class Method;
class Utf8String;

enum ConstantPoolTag
{
	CONSTANT_Class = 7,
	CONSTANT_Fieldref = 9,
	CONSTANT_Methodref = 10,
	CONSTANT_InterfaceMethodref = 11,
	CONSTANT_String = 8,
	CONSTANT_Integer = 3,
	CONSTANT_Float = 4,
	CONSTANT_Long = 5,
	CONSTANT_Double = 6,
	CONSTANT_NameAndType = 12,
	CONSTANT_Utf8 = 1,
	CONSTANT_MethodHandle = 15,
	CONSTANT_MethodType = 16,
	CONSTANT_InvokeDynamic = 18,
};

struct CONSTANT_Class_info
{
	ConstantPoolAddress name_index;

	Class* classPtr; // TODO: Add this

	CONSTANT_Class_info(unsigned short index)
	{
		name_index = index;
		classPtr = nullptr;
	}
};

struct CONSTANT_Fieldref_info
{
	ConstantPoolAddress class_index;
	ConstantPoolAddress name_and_type_index;

	Class* classPtr; // TODO: Add this
	Field* fieldPtr;

	CONSTANT_Fieldref_info(unsigned short ci, unsigned short nati)
	{
		class_index = ci;
		name_and_type_index = nati;
		classPtr = nullptr;
		fieldPtr = nullptr;
	}
};

struct CONSTANT_Methodref_info
{
	ConstantPoolAddress class_index;
	ConstantPoolAddress name_and_type_index;

	Class* classPtr; // TODO: Add this
	Method* methodPtr; // TODO: Add this

	CONSTANT_Methodref_info(unsigned short ci, unsigned short nati)
	{
		class_index = ci;
		name_and_type_index = nati;
		classPtr = nullptr;
		methodPtr = nullptr;
	}
};

struct CONSTANT_InterfaceMethodref_info
{
	ConstantPoolAddress class_index;
	ConstantPoolAddress name_and_type_index;

	Class* classPtr; // TODO: Add this
	Method* methodPtr; // TODO: Add this

	CONSTANT_InterfaceMethodref_info(unsigned short ci, unsigned short nati)
	{
		class_index = ci;
		name_and_type_index = nati;
		classPtr = nullptr;
		methodPtr = nullptr;
	}
};

struct CONSTANT_String_info
{
	ConstantPoolAddress string_index;

	Utf8String * value; // TODO: Add this
	//java::lang::String::String * stringObject;

	CONSTANT_String_info(unsigned short index)
	{
		string_index = index;
	}
};

struct CONSTANT_Integer_info
{
	int value;

	CONSTANT_Integer_info(int v)
	{
		value = v;
	}
};

struct CONSTANT_Float_info
{
	float value;

	CONSTANT_Float_info(float v)
	{
		value = v;
	}
};

struct CONSTANT_Long_info
{
	unsigned int high_bytes;
	unsigned int low_bytes;

	long long value;


	CONSTANT_Long_info(unsigned int hb, unsigned int lb)
	{
		high_bytes = hb;
		low_bytes = lb;

		value = longFromStack(hb, lb);
	}
};

struct CONSTANT_Double_info
{
	unsigned int high_bytes;
	unsigned int low_bytes;

	double value;

	CONSTANT_Double_info(unsigned int hb, unsigned int lb)
	{
		high_bytes = hb;
		low_bytes = lb;

		value = doubleFromStack(hb, lb);
	}
};

struct CONSTANT_NameAndType_info
{
	ConstantPoolAddress name_index;
	ConstantPoolAddress descriptor_index;

	CONSTANT_NameAndType_info(unsigned short ni, unsigned short di)
	{
		name_index = ni;
		descriptor_index = di;
	}
};

struct CONSTANT_Utf8_info
{
	unsigned short length;
	unsigned char * bytes; // actual: length

	Utf8String * string;

	CONSTANT_Utf8_info(unsigned short l, char * d)
	{
		length = l;
		bytes = new unsigned char[length+1];
		for (unsigned short i = 0; i < length; i++)
		{
			bytes[i] = (unsigned char)d[i];
		}
		bytes[length] = '\0';
		string = new Utf8String(bytes, length);

	}
};

struct CONSTANT_MethodHandle_info
{
	ReferenceType reference_kind;
	ConstantPoolAddress reference_index;

	CONSTANT_MethodHandle_info(ReferenceType rk, unsigned short ri)
	{
		reference_kind = rk;
		reference_index = ri;
	}

};

struct CONSTANT_MethodType_info
{
	ConstantPoolAddress descriptor_index;
	CONSTANT_MethodType_info(unsigned short index)
	{

		descriptor_index = index;
	}
};

struct CONSTANT_InvokeDynamic_info
{
	ConstantPoolAddress bootstrap_method_attr_index;
	ConstantPoolAddress name_and_type_index;

	CONSTANT_InvokeDynamic_info(unsigned short bmai, unsigned short nati)
	{

		bootstrap_method_attr_index = bmai;
		name_and_type_index = nati;
	}
};


struct ConstantPoolItem
{
	ConstantPoolTag tag;
	union {
		CONSTANT_Class_info classInfo;
		CONSTANT_Fieldref_info fieldInfo;
		CONSTANT_Methodref_info methodInfo;
		CONSTANT_InterfaceMethodref_info interfaceMethodInfo;
		CONSTANT_String_info stringInfo;
		CONSTANT_Integer_info integerInfo;
		CONSTANT_Float_info floatInfo;
		CONSTANT_Long_info longInfo;
		CONSTANT_Double_info doubleInfo;
		CONSTANT_NameAndType_info nameAndTypeInfo;
		CONSTANT_Utf8_info utf8Info;
		CONSTANT_MethodHandle_info methodHandleInfo;
		CONSTANT_MethodType_info methodTypeInfo;
		CONSTANT_InvokeDynamic_info invokeDynamicInfo;
	};
	ConstantPoolItem(ConstantPoolTag t)
	{
		tag = t;
	}
	ConstantPoolItem()
	{
	}
};
