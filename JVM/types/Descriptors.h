#pragma once
#include <string>
#include "types.h"
#include "Aliases.h"

namespace TypeDescriptors
{
	std::string getClassDescriptor(const std::string & name);
	std::string getArrayDescriptor(JavaType type, int dimensions = 1);
	std::string getSimpleDescriptor(JavaType type);
	std::string getTypeDescriptor(JavaType type);

	std::string getMethodDescriptor(JavaType returnType, JavaType parameters...);
	std::string getMethodDescriptor(JavaType returnType, JavaType * parameters, size_t countParameters);

	std::string getMethodDescriptor(JavaType returnType);

	std::string getMethodDescriptor();
}
