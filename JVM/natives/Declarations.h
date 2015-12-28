#pragma once
#include <string>

class Object;
class MethodFrame;
class Method;
class ExecutionEngine;

#define NATIVE_METHOD_HEADER(name) void name (::Object * object, ExecutionEngine * engine)

typedef void(*NativeMethodPtr)(Object *, ExecutionEngine *);
