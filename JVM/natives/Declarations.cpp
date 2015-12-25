#pragma once
#include "Declarations.h"
#include "../runtime/MethodFrame.h"
#include "../runtime/Method.h"
#include "../types/Descriptors.h"
#include "../runtime/Object.h"

using namespace TypeDescriptors;

Method* getNativeMethod(const std::string & name, const std::string & descriptor, void* nativeMethod)
{
	Method * method = new Method();
	method->name = Utf8String("clone");
	method->descriptor = Utf8String("()Ljava/lang/Object;");
	method->byteCode = NULL;
	method->byteCodeLength = 0;
	method->localVariablesArraySize = 0;
	method->operandStackSize = 0;
	method->nativeMethod = (NativeMethodPtr)nativeMethod;

	return method;
}

/*
Method* getNativeMethod(const std::string & name, const std::string & descriptor, NativeMethodPtr nativeMethod)
{
	return getNativeMethod(name, descriptor, (void*)nativeMethod);
}

Method* getNativeMethod(const std::string & name, NativeMethodPtr nativeMethod, JavaType returnType, JavaType args...)
{
	return getNativeMethod(name, getMethodDescriptor(returnType, args), nativeMethod);
}

Method* getNativeMethod(const std::string & name, NativeMethodPtr nativeMethod, JavaType returnType, JavaType * args, size_t countArgs)
{
	return getNativeMethod(name, getMethodDescriptor(returnType, args, countArgs), nativeMethod);
}

Method* getNativeMethod(const std::string & name, NativeMethodPtr nativeMethod, JavaType returnType)
{
	return getNativeMethod(name, getMethodDescriptor(returnType), nativeMethod);
}

Method* getNativeMethod(const std::string & name, NativeMethodPtr nativeMethod)
{
	return getNativeMethod(name, getMethodDescriptor(), nativeMethod);
}
*/

Method* getNativeMethod(const std::string & name, void* nativeMethod)
{
	return getNativeMethod(name, getMethodDescriptor(), nativeMethod);
}
