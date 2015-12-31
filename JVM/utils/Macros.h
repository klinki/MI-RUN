#pragma once

#ifdef _DEBUG
	#define visibility public
	#define DEBUG_PRINT(...) fprintf(stderr, __VA_ARGS__)
	#define DEBUG_BLOCK(block) block
#else
	#define visibility public
	#define DEBUG_PRINT(arguments)
	#define DEBUG_BLOCK(block)
#endif
