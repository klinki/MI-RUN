#pragma once

#ifdef _DEBUG
	#define visibility public
#else
	#define visibility protected
#endif

#define NATIVE_METHOD_HEADER(name) void name (::Object * object, MethodFrame * frame)
