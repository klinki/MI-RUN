#include "Descriptors.h"

namespace TypeDescriptors
{
	std::string getClassDescriptor(const std::string & name)
	{
		std::string result;
		result.append("L");
		result.append(name);
		result.append(";");

		return result;
	}

	std::string getArrayDescriptor(JavaType type, int dimensions)
	{
		std::string result;

		while (dimensions-- > 0)
		{
			result.append("[");
		}

		result.append(getSimpleDescriptor(type));

		return result;
	}

	std::string getSimpleDescriptor(JavaType type)
	{
		switch (type.tag)
		{
		case TypeTag::REFERENCE:
			return getClassDescriptor(type.className);
			break;
		}

		return std::string(1, (char)type.tag);
	}

	std::string getTypeDescriptor(JavaType type)
	{
		if (type.dimensions > 0)
		{
			return getArrayDescriptor(type);
		}
		else
		{
			return getSimpleDescriptor(type);
		}
	}

	std::string getMethodDescriptor(JavaType returnType, JavaType parameters...)
	{
		std::string result = "(";


		return result;
	}

	std::string getMethodDescriptor(JavaType returnType, JavaType * parameters, size_t countParameters)
	{
		std::string result = "(";

		for (size_t i = 0; i < countParameters; i++)
		{
			result.append(getTypeDescriptor(parameters[i]));
		}

		result.append(")");
		result.append(getTypeDescriptor(returnType));

		return result;
	}

	std::string getMethodDescriptor(JavaType returnType)
	{
		std::string result = "()";
		result.append(getTypeDescriptor(returnType));
		return result;
	}

	std::string getMethodDescriptor()
	{
		return "()V";
	}

}
