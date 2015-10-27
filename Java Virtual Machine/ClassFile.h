#pragma once
#include "TypeInfo.h"

struct ClassFile
{
	u4             magic;
	u2             minor_version;
	u2             major_version;
	u2             constant_pool_count;
	ConstantPoolItem constant_pool[1]; // actual: constant_pool_count - 1
	u2             access_flags;
	u2             this_class;
	u2             super_class;
	u2             interfaces_count;
	u2             interfaces[1]; // actual - interfaces_count
	u2             fields_count;
	field_info     fields[1]; // actual - fields_count
	u2             methods_count;
	method_info    methods[1]; // actual - methods_count
	u2             attributes_count;
	attribute_info attributes[1]; // actual - attributes_count
};
