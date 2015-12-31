#pragma once

#ifdef _DEBUG
	#define visibility public
	#define DEBUG_PRINT(...) fprintf(stderr, __VA_ARGS__)
#else
	#define visibility public
	#define DEBUG_PRINT(arguments)
#endif
