#include "helpers.h"
#include "Declarations.h"
#include "../runtime/Method.h"
#include "../runtime/Object.h"
#include "../utils/Utf8String.h"

Method* getNativeMethod(const char* name, const char* descriptor, NativeMethodPtr nativeMethod)
{
	Method * method = new Method();
	method->name = Utf8String(name);
	method->setDescriptor(Utf8String(descriptor));
	method->byteCode = NULL;
	method->byteCodeLength = 0;
	method->localVariablesArraySize = 0;
	method->operandStackSize = 0;
	method->nativeMethod = (NativeMethodPtr)nativeMethod;

	return method;
}

Method* getNativeMethod(const char* name, NativeMethodPtr nativeMethod)
{
	return getNativeMethod(name, "()V", nativeMethod);
}
