#pragma once
#include "Declarations.h"
#include "../runtime/MethodFrame.h"
#include "../runtime/Method.h"
#include "../types/Descriptors.h"

using namespace TypeDescriptors;

inline Method* getNativeMethod(std::string name, std::string descriptor, NativeMethodPtr nativeMethod)
{
	Method * method = new Method();
	method->name = Utf8String("clone");
	method->descriptor = Utf8String("()Ljava/lang/Object;");
	method->byteCode = NULL;
	method->byteCodeLength = 0;
	method->localVariablesArraySize = 0;
	method->operandStackSize = 0;
	method->nativeMethod = nativeMethod;

	return method;
}

inline Method* getNativeMethod(std::string name, NativeMethodPtr nativeMethod, JavaType returnType, JavaType args...)
{
	return getNativeMethod(name, getMethodDescriptor(name, returnType, args), nativeMethod);
}

inline Method* getNativeMethod(std::string name, NativeMethodPtr nativeMethod, JavaType returnType, JavaType * args)
{
	return getNativeMethod(name, getMethodDescriptor(name, returnType, args), nativeMethod);
}

inline Method* getNativeMethod(std::string name, NativeMethodPtr nativeMethod, JavaType returnType)
{
	return getNativeMethod(name, getMethodDescriptor(name, returnType), nativeMethod);
}

inline Method* getNativeMethod(std::string name, NativeMethodPtr nativeMethod)
{
	return getNativeMethod(name, getMethodDescriptor(name), nativeMethod);
}
