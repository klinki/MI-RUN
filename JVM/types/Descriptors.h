#pragma once
#include <string>
#include "types.h"
#include "Aliases.h"

namespace TypeDescriptors
{
	inline std::string getClassDescriptor(const std::string & name);
	inline std::string getArrayDescriptor(JavaType type, int dimensions = 1);
	inline std::string getSimpleDescriptor(JavaType type);
	inline std::string getTypeDescriptor(JavaType type);

	inline std::string getMethodDescriptor(JavaType returnType, JavaType parameters...);
	inline std::string getMethodDescriptor(JavaType returnType, JavaType * parameters, size_t countParameters);

	inline std::string getMethodDescriptor(JavaType returnType);

	inline const char* getMethodDescriptor();
}
