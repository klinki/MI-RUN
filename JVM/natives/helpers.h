#pragma once
#include "Declarations.h"

class Method;

Method* getNativeMethod(const char* name, const char* descriptor, NativeMethodPtr nativeMethod);
Method* getNativeMethod(const char* name, NativeMethodPtr nativeMethod);
