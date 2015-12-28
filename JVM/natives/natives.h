#pragma once
#include "../runtime/Class.h"
#include "../runtime/MethodFrame.h"
#include "../runtime/Method.h"
#include "../runtime/MethodArea.h"
#include "../runtime/Object.h"
#include "../runtime/Classmap.h"
#include "../runtime/ExecutionEngine.h"
#include "../types/Descriptors.h"
#include "../exceptions/RuntimeExceptions.h"

class ClassMap;
void InitializeNatives(ClassMap* classMap);
