#pragma once
#include <string>
#include "../types/types.h"

class Object;
class MethodFrame;
class Method;
class ExecutionEngine;

#define NATIVE_METHOD_HEADER(name) void name (::Object * object, ExecutionEngine * engine)

typedef void(*NativeMethodPtr)(Object *, ExecutionEngine *);

//Method* getNativeMethod(const std::string & name, const std::string & descriptor, NativeMethodPtr nativeMethod);
Method* getNativeMethod(const std::string & name, const std::string & descriptor, void* nativeMethod);

/*
Method* getNativeMethod(const std::string & name, NativeMethodPtr nativeMethod, JavaType returnType, JavaType args...);
Method* getNativeMethod(const std::string & name, NativeMethodPtr nativeMethod, JavaType returnType, JavaType * args, size_t countArgs);
Method* getNativeMethod(const std::string & name, NativeMethodPtr nativeMethod, JavaType returnType);
*/
//Method* getNativeMethod(const std::string & name, NativeMethodPtr nativeMethod);
// Method* getNativeMethod(const std::string & name, void* nativeMethod);
