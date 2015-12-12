#pragma once
#include <string>
#include "../types/types.h"

class Object;
class MethodFrame;
class Method;

typedef void(*NativeMethodPtr)(Object *, MethodFrame*);
inline Method* getNativeMethod(std::string name, std::string descriptor, NativeMethodPtr nativeMethod);
inline Method* getNativeMethod(std::string name, NativeMethodPtr nativeMethod, JavaType returnType, JavaType args...);
inline Method* getNativeMethod(std::string name, NativeMethodPtr nativeMethod, JavaType returnType, JavaType * args);
inline Method* getNativeMethod(std::string name, NativeMethodPtr nativeMethod, JavaType returnType);
inline Method* getNativeMethod(std::string name, NativeMethodPtr nativeMethod);
