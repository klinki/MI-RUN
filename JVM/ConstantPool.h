#pragma once
#include "Reference.h"

typedef unsigned short ConstantPoolAddress;

class ConstantPool;

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

union ConstantPoolItem
{
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

struct CONSTANT_Class_info
{
	ConstantPoolTag tag;
	ConstantPoolAddress name_index;

	CONSTANT_Class_info(unsigned short index)
	{
		tag = ConstantPoolTag::CONSTANT_Class;
		name_index = index;
	}
};

struct CONSTANT_Fieldref_info
{
	ConstantPoolTag tag;
	ConstantPoolAddress class_index;
	ConstantPoolAddress name_and_type_index;
};

struct CONSTANT_Methodref_info
{
	ConstantPoolTag tag;
	ConstantPoolAddress class_index;
	ConstantPoolAddress name_and_type_index;
};

struct CONSTANT_InterfaceMethodref_info
{
	ConstantPoolTag tag;
	ConstantPoolAddress class_index;
	ConstantPoolAddress name_and_type_index;
};

struct CONSTANT_String_info
{
	ConstantPoolTag tag;
	ConstantPoolAddress string_index;
};

struct CONSTANT_Integer_info
{
	ConstantPoolTag tag;
	int value;
};

struct CONSTANT_Float_info
{
	ConstantPoolTag tag;
	float value;
};

struct CONSTANT_Long_info
{
	ConstantPoolTag tag;
	unsigned int high_bytes;
	unsigned int low_bytes;
};

struct CONSTANT_Double_info
{
	ConstantPoolTag tag;
	unsigned int high_bytes;
	unsigned int low_bytes;
};

struct CONSTANT_NameAndType_info
{
	ConstantPoolTag tag;
	ConstantPoolAddress name_index;
	ConstantPoolAddress descriptor_index;
};

struct CONSTANT_Utf8_info
{
	ConstantPoolTag tag;
	unsigned short length;
	const char bytes[1]; // actual: length
};

struct CONSTANT_MethodHandle_info
{
	ConstantPoolTag tag;
	ReferenceType reference_kind;
	ConstantPoolAddress reference_index;
};

struct CONSTANT_MethodType_info
{
	ConstantPoolTag tag;
	ConstantPoolAddress descriptor_index;
};

struct CONSTANT_InvokeDynamic_info
{
	ConstantPoolTag tag;
	ConstantPoolAddress bootstrap_method_attr_index;
	ConstantPoolAddress name_and_type_index;
};
