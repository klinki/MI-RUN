#include "Descriptors.h"

namespace TypeDescriptors
{
	static const char* BYTE = "B";
	static const char* CHAR = "C";
	static const char* DOUBLE = "D";
	static const char* FLOAT = "F";
	static const char* INT = "I";
	static const char* LONG = "J";
	static const char* SHORT = "S";
	static const char* BOOLEAN = "Z";
	static const char* ARRAY = "[";

	inline std::string getClassDescriptor(const std::string & name)
	{
		std::string result;
		result.append("L");
		result.append(name);
		result.append(";");

		return result;
	}

	inline std::string getArrayDescriptor(JavaType type, int dimensions)
	{
		std::string result;

		while (dimensions-- > 0)
		{
			result.append("[");
		}

		result.append(getSimpleDescriptor(type));

		return result;
	}

	inline std::string getSimpleDescriptor(JavaType type)
	{
		switch (type.tag)
		{
		case TypeTag::JAVA_VOID:
			return "";
			break;
		case TypeTag::BOOL:
			return BOOLEAN;
			break;
		case TypeTag::BYTE:
			return BYTE;
			break;
		case TypeTag::CHAR:
			return CHAR;
			break;
		case TypeTag::DOUBLE:
			return DOUBLE;
			break;
		case TypeTag::FLOAT:
			return FLOAT;
			break;
		case TypeTag::INT:
			return INT;
			break;
		case TypeTag::LONG:
			return LONG;
			break;
		case TypeTag::SHORT:
			return SHORT;
			break;
		case TypeTag::REFERENCE:
			return getClassDescriptor(type.className);
			break;
		}
	}

	inline std::string getTypeDescriptor(JavaType type)
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

	inline std::string getMethodDescriptor(JavaType returnType, JavaType parameters...)
	{
		return "";
	}

	inline std::string getMethodDescriptor(JavaType returnType, JavaType * parameters, size_t countParameters)
	{
		std::string result = "(";

		for (int i = 0; i < countParameters; i++)
		{
			result.append(getTypeDescriptor(parameters[i]));
		}

		result.append(")");
		result.append(getTypeDescriptor(returnType));

		return result;
	}

	inline std::string getMethodDescriptor(JavaType returnType)
	{
		std::string result = "()";
		result.append(getTypeDescriptor(returnType));
		return result;
	}

	inline const char* getMethodDescriptor()
	{
		return "()";
	}

}
