#pragma once

#ifdef _DEBUG
	#define visibility public
	#define DEBUG_PRINT(...) fprintf(stderr, __VA_ARGS__)
	#define DEBUG_BLOCK(block) block
	#define PRINT_STACK(stack) printOperandStack(stack);
	#define PRINT_LOCAL_VARIABLES(frame) printLocalVariables(frame);
	#define PRINT_OBJECT_TABLE(table) printObjectTable(table)
#else
	#define visibility public
	#define DEBUG_PRINT(...)
	#define DEBUG_BLOCK(block)
	#define PRINT_STACK(stack)
	#define PRINT_LOCAL_VARIABLES(frame) 
	#define PRINT_OBJECT_TABLE(table)
#endif
